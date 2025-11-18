import sys
import numpy as np
import random
from collections import defaultdict
from tqdm import tqdm
import time

np.set_printoptions(precision=4, suppress=True)

class Node:
    def __init__(self, idx, is_leaf=False):
        self.idx = idx
        self.is_leaf = is_leaf
        self.vec = None       # np.array([class_mass])
        self.cls = None       # int: assigned class
        self.sep = None      # for internal: which separator (feature row) [0..K-1]
        self.out = []        # [out0, out1]: outgoing node indices (for internal)
        self.incoming = []   # 入力エッジ（DAG用）
        
    def add_outgoing(self, target_idx):
        if target_idx not in self.out:
            self.out.append(target_idx)
    
    def add_incoming(self, source_idx):
        if source_idx not in self.incoming:
            self.incoming.append(source_idx)

def split_gain(vec, prow):
    """分割利得計算"""
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def build_greedy_base(N, M, K, P):
    """基本の貪欲法による初期DAG構築"""
    nodes = {}
    root = Node(0, False)
    root.vec = np.ones(N)
    nodes[0] = root
    next_id = 1
    queue = [root]
    
    # まず基本的な木を構築
    while len(nodes) < min(M + N, 50) and queue:  # 最初は控えめに
        nd = queue.pop(0)
        
        # 情報利得最大の分割軸
        gains = [split_gain(nd.vec, P[i]) for i in range(K)]
        best_i = np.argmax(gains)
        
        # 利得が小さすぎる場合は葉ノード化
        if gains[best_i] < 0.01:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
            continue
            
        nd.sep = best_i
        v1 = nd.vec * np.array(P[best_i])
        v2 = nd.vec * (1 - np.array(P[best_i]))
        
        # 子ノード作成
        left = Node(next_id, False)
        right = Node(next_id + 1, False)
        left.vec = v1.copy()
        right.vec = v2.copy()
        
        nodes[next_id] = left
        nodes[next_id + 1] = right
        
        nd.add_outgoing(next_id)
        nd.add_outgoing(next_id + 1)
        left.add_incoming(nd.idx)
        right.add_incoming(nd.idx)
        
        queue.append(left)
        queue.append(right)
        next_id += 2
    
    # 残りのノードを葉ノード化
    for nd in nodes.values():
        if not nd.out and not nd.is_leaf:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
    
    return nodes, next_id

def find_mergeable_subtrees(nodes, P, K):
    """マージ可能な部分木を発見"""
    # 各ノードの部分木の特徴を抽出
    subtree_features = {}
    
    for node_id, node in nodes.items():
        if node.is_leaf:
            continue
            
        # 部分木の特徴：(分別器, 左の子の特徴, 右の子の特徴)
        if len(node.out) >= 2:
            left_id, right_id = node.out[0], node.out[1]
            left_feature = get_subtree_signature(nodes, left_id)
            right_feature = get_subtree_signature(nodes, right_id)
            
            feature = (node.sep, tuple(sorted([left_feature, right_feature])))
            
            if feature not in subtree_features:
                subtree_features[feature] = []
            subtree_features[feature].append(node_id)
    
    # 同じ特徴を持つ部分木をマージ候補として返す
    merge_candidates = []
    for feature, node_list in subtree_features.items():
        if len(node_list) > 1:
            merge_candidates.append(node_list)
    
    return merge_candidates

def get_subtree_signature(nodes, node_id):
    """部分木のシグネチャを計算"""
    node = nodes[node_id]
    
    if node.is_leaf:
        return f"leaf_{node.cls}"
    
    if len(node.out) >= 2:
        left_sig = get_subtree_signature(nodes, node.out[0])
        right_sig = get_subtree_signature(nodes, node.out[1])
        return f"internal_{node.sep}_{tuple(sorted([left_sig, right_sig]))}"
    
    return f"single_{node.sep}"

def apply_dag_merging(nodes, merge_candidates, node_budget):
    """DAGマージを適用"""
    merged_count = 0
    
    for candidate_group in merge_candidates:
        if len(nodes) >= node_budget:
            break
            
        # 最初のノードをマスターとして、他をマージ
        master_id = candidate_group[0]
        
        for slave_id in candidate_group[1:]:
            if slave_id not in nodes:
                continue
                
            slave_node = nodes[slave_id]
            
            # スレーブノードへの入力を全てマスターノードにリダイレクト
            for parent_id, parent_node in nodes.items():
                if slave_id in parent_node.out:
                    parent_node.out.remove(slave_id)
                    parent_node.add_outgoing(master_id)
                    nodes[master_id].add_incoming(parent_id)
            
            # スレーブノードを削除
            del nodes[slave_id]
            merged_count += 1
            
            print(f"ノード{slave_id}をノード{master_id}にマージ")
    
    return merged_count

def expand_dag_with_budget(nodes, next_id, node_budget, N, M, K, P):
    """残りノード予算でDAGを拡張"""
    print(f"DAG拡張: 現在{len(nodes)}ノード, 予算{node_budget}")
    
    # 性能の悪い葉ノードを特定
    leaf_nodes = [(nid, n) for nid, n in nodes.items() if n.is_leaf]
    
    # 各葉ノードの分類精度を評価
    leaf_performance = []
    for node_id, node in leaf_nodes:
        if node.vec is not None and node.vec.sum() > 0:
            purity = node.vec[node.cls] / node.vec.sum()
            leaf_performance.append((purity, node_id, node))
    
    # 純度の低いノードから拡張
    leaf_performance.sort()
    
    for purity, node_id, node in leaf_performance:
        if len(nodes) >= node_budget:
            break
            
        if purity > 0.8:  # 十分純度が高い場合はスキップ
            continue
            
        # 葉ノードを内部ノードに変換
        print(f"葉ノード{node_id}を拡張 (純度: {purity:.3f})")
        
        node.is_leaf = False
        node.cls = None
        
        # 最適な分別器を選択
        best_i = np.argmax([split_gain(node.vec, P[i]) for i in range(K)])
        node.sep = best_i
        
        # 子ノード作成
        v1 = node.vec * np.array(P[best_i])
        v2 = node.vec * (1 - np.array(P[best_i]))
        
        if len(nodes) + 2 <= node_budget:
            left = Node(next_id, True)
            right = Node(next_id + 1, True)
            left.vec = v1.copy()
            right.vec = v2.copy()
            left.cls = int(np.argmax(left.vec))
            right.cls = int(np.argmax(right.vec))
            
            nodes[next_id] = left
            nodes[next_id + 1] = right
            
            node.add_outgoing(next_id)
            node.add_outgoing(next_id + 1)
            left.add_incoming(node_id)
            right.add_incoming(node_id)
            
            next_id += 2

def build_enhanced_greedy_dag(N, M, K, P):
    """強化版貪欲DAG構築"""
    print("強化版貪欲DAG構築開始...")
    
    # Phase 1: 基本の貪欲法で初期構造を構築
    nodes, next_id = build_greedy_base(N, M, K, P)
    print(f"初期構築完了: {len(nodes)}ノード")
    
    node_budget = M + N
    
    # Phase 2: DAGマージによる構造共有
    merge_candidates = find_mergeable_subtrees(nodes, P, K)
    if merge_candidates:
        merged_count = apply_dag_merging(nodes, merge_candidates, node_budget)
        print(f"DAGマージ完了: {merged_count}ノードをマージ")
    
    # Phase 3: 残り予算でDAG拡張
    expand_dag_with_budget(nodes, next_id, node_budget, N, M, K, P)
    
    print(f"DAG構築完了: {len(nodes)}ノード")
    shared_edges = sum(len(n.incoming) for n in nodes.values()) - (len(nodes) - 1)
    print(f"DAG共有エッジ数: {shared_edges}")
    
    return list(nodes.values())

def topo_sort(nodes):
    """トポロジカルソート"""
    node_map = {nd.idx: nd for nd in nodes}
    indeg = defaultdict(int)
    for nd in nodes:
        for o in nd.out:
            if o in node_map:  # 存在チェック
                indeg[o] += 1
    order = []
    dq = [0] if 0 in node_map else []
    while dq:
        x = dq.pop(0)
        order.append(x)
        nd = node_map[x]
        for o in nd.out:
            if o in node_map:
                indeg[o] -= 1
                if indeg[o] == 0:
                    dq.append(o)
    return order

def propagate(nodes, P):
    """確率伝播計算"""
    node_map = {nd.idx: nd for nd in nodes}
    for nd in nodes:
        nd.vec = np.zeros_like(nodes[0].vec)
    if 0 in node_map:
        node_map[0].vec = np.ones_like(nodes[0].vec)
    
    order = topo_sort(nodes)
    for idx in order:
        if idx not in node_map:
            continue
        nd = node_map[idx]
        if nd.is_leaf:
            nd.cls = int(np.argmax(nd.vec))
            continue
        if nd.sep is None:
            continue
        prow = np.array(P[nd.sep])
        v = nd.vec
        valid_outputs = [o for o in nd.out if o in node_map]
        if len(valid_outputs) >= 2:
            out1, out2 = valid_outputs[0], valid_outputs[1]
            node_map[out1].vec += v * prow
            node_map[out2].vec += v * (1 - prow)
        elif len(valid_outputs) == 1:
            node_map[valid_outputs[0]].vec += v
    
    for nd in nodes:
        if nd.is_leaf and nd.vec is not None:
            nd.cls = int(np.argmax(nd.vec))

def score(nodes):
    """スコア計算"""
    N = nodes[0].vec.shape[0]
    tot = np.zeros(N)
    cor = np.zeros(N)
    for n in nodes:
        if n.is_leaf and n.vec is not None:
            v = n.vec
            tot += v
            if n.cls is not None:
                cor[n.cls] += v[n.cls]
    recall = cor / (tot + 1e-12)
    sigma = np.sum(tot - cor)
    return sigma, recall

def simulate_sigma(nodes, P, num=10000):
    """モンテカルロシミュレーション"""
    N = len(P[0])
    count = np.zeros(N)
    node_map = {n.idx: n for n in nodes}
    
    for c in range(N):
        for _ in range(num):
            idx = 0
            while idx in node_map and not node_map[idx].is_leaf:
                node = node_map[idx]
                if node.sep is None:
                    break
                prob = P[node.sep][c]
                valid_outputs = [o for o in node.out if o in node_map]
                if len(valid_outputs) >= 2:
                    idx = valid_outputs[0] if random.random() < prob else valid_outputs[1]
                elif len(valid_outputs) == 1:
                    idx = valid_outputs[0]
                else:
                    break
            if idx in node_map and node_map[idx].is_leaf and node_map[idx].cls is not None:
                count[c] += int(node_map[idx].cls == c)
    
    recall = count / num
    sigma = N - recall.sum()
    return sigma

def local_optimization(nodes, P, K, steps=1000):
    """局所最適化"""
    print("局所最適化開始...")
    
    best_nodes = [Node(n.idx, n.is_leaf) for n in nodes]
    for i, n in enumerate(nodes):
        best_nodes[i].vec = n.vec.copy() if n.vec is not None else None
        best_nodes[i].cls = n.cls
        best_nodes[i].sep = n.sep
        best_nodes[i].out = list(n.out)
        best_nodes[i].incoming = list(n.incoming)
    
    propagate(best_nodes, P)
    best_sigma, _ = score(best_nodes)
    
    for step in range(steps):
        # 内部ノードの分別器をランダムに変更
        internal_nodes = [n for n in best_nodes if not n.is_leaf]
        if not internal_nodes:
            break
            
        node = random.choice(internal_nodes)
        old_sep = node.sep
        new_sep = random.randrange(K)
        
        if new_sep != old_sep:
            node.sep = new_sep
            propagate(best_nodes, P)
            new_sigma, _ = score(best_nodes)
            
            if new_sigma < best_sigma:
                best_sigma = new_sigma
                if step % 100 == 0:
                    print(f"  Step {step}: σ改善 -> {best_sigma:.4f}")
            else:
                node.sep = old_sep  # 戻す
    
    return best_nodes, best_sigma

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # Phase 1: 強化版貪欲DAG構築
    nodes = build_enhanced_greedy_dag(N, M, K, P)
    
    # Phase 2: 局所最適化
    nodes, best_sigma = local_optimization(nodes, P, K, steps=500)
    
    # Phase 3: 最終評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    
    print("\n強化版貪欲DAG結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
