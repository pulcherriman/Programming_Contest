import sys
import numpy as np
import random
from collections import defaultdict, deque
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
        self.creation_context = None  # ノード作成時のコンテキスト
        
    def add_outgoing(self, target_idx):
        if target_idx not in self.out:
            self.out.append(target_idx)
    
    def add_incoming(self, source_idx):
        if source_idx not in self.incoming:
            self.incoming.append(source_idx)
    
    def signature(self):
        """ノードの特徴シグネチャ"""
        if self.is_leaf:
            return f"leaf_{self.cls}"
        return f"sep_{self.sep}"

def split_gain(vec, prow):
    """分割利得計算"""
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def build_initial_tree(N, M, K, P):
    """初期の木構造を構築"""
    nodes = {}
    root = Node(0, False)
    root.vec = np.ones(N)
    root.creation_context = "root"
    nodes[0] = root
    next_id = 1
    queue = [root]
    
    # 基本的な木を構築（控えめに）
    while len(nodes) < min(30, M//3) and queue:
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
        left.creation_context = f"left_of_{nd.idx}"
        right.creation_context = f"right_of_{nd.idx}"
        
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

def find_similar_nodes(nodes, similarity_threshold=0.8):
    """類似したノードを発見（ベクトル類似性ベース）"""
    node_list = list(nodes.values())
    similar_pairs = []
    
    for i, node1 in enumerate(node_list):
        if node1.vec is None or node1.vec.sum() == 0:
            continue
            
        for j, node2 in enumerate(node_list[i+1:], i+1):
            if node2.vec is None or node2.vec.sum() == 0:
                continue
            
            # ベクトルの正規化
            vec1_norm = node1.vec / (node1.vec.sum() + 1e-12)
            vec2_norm = node2.vec / (node2.vec.sum() + 1e-12)
            
            # コサイン類似度計算
            dot_product = np.dot(vec1_norm, vec2_norm)
            similarity = dot_product
            
            if similarity > similarity_threshold:
                similar_pairs.append((node1.idx, node2.idx, similarity))
    
    # 類似度でソート
    similar_pairs.sort(key=lambda x: x[2], reverse=True)
    return similar_pairs

def create_shared_subtree(nodes, parent_nodes, separator, N, K, P, next_id):
    """共有部分木を作成"""
    # 新しい共有ノードを作成
    shared_node = Node(next_id, False)
    shared_node.sep = separator
    shared_node.vec = np.zeros(N)
    shared_node.creation_context = f"shared_sep_{separator}"
    
    # 親ノードからの確率を統合
    for parent_id in parent_nodes:
        parent = nodes[parent_id]
        if parent.vec is not None:
            shared_node.vec += parent.vec * 0.5  # 簡単な重み付け
    
    # 子ノードを作成
    left_child = Node(next_id + 1, True)
    right_child = Node(next_id + 2, True)
    
    # 分割計算
    prow = np.array(P[separator])
    v1 = shared_node.vec * prow
    v2 = shared_node.vec * (1 - prow)
    
    left_child.vec = v1.copy()
    right_child.vec = v2.copy()
    left_child.cls = int(np.argmax(left_child.vec))
    right_child.cls = int(np.argmax(right_child.vec))
    left_child.creation_context = f"shared_left_{separator}"
    right_child.creation_context = f"shared_right_{separator}"
    
    # エッジを設定
    shared_node.add_outgoing(next_id + 1)
    shared_node.add_outgoing(next_id + 2)
    left_child.add_incoming(next_id)
    right_child.add_incoming(next_id)
    
    for parent_id in parent_nodes:
        shared_node.add_incoming(parent_id)
        nodes[parent_id].add_outgoing(next_id)
    
    return shared_node, left_child, right_child

def build_dag_from_patterns(nodes, next_id, N, M, K, P):
    """パターンベースDAG構築"""
    print("パターンベースDAG構築開始...")
    
    # 分別器の使用頻度を分析
    separator_usage = defaultdict(list)
    for node in nodes.values():
        if not node.is_leaf and node.sep is not None:
            separator_usage[node.sep].append(node.idx)
    
    print(f"分別器使用状況: {dict(separator_usage)}")
    
    # 同じ分別器を使用するノード群を基にDAG構築
    dag_created = 0
    for sep, node_ids in separator_usage.items():
        if len(node_ids) >= 2 and len(nodes) + 3 <= M + N:
            print(f"分別器{sep}でDAG構築試行: ノード{node_ids}")
            
            # 共有部分木を作成
            shared, left, right = create_shared_subtree(
                nodes, node_ids[:2], sep, N, K, P, next_id
            )
            
            nodes[next_id] = shared
            nodes[next_id + 1] = left
            nodes[next_id + 2] = right
            next_id += 3
            dag_created += 1
            
            print(f"  共有ノード{shared.idx}を作成")
    
    return dag_created, next_id

def progressive_dag_construction(N, M, K, P):
    """段階的DAG構築"""
    print("段階的DAG構築開始...")
    
    # Phase 1: 初期木構造
    nodes, next_id = build_initial_tree(N, M, K, P)
    print(f"Phase 1完了: {len(nodes)}ノード")
    
    # Phase 2: 類似ノードベースの拡張
    similar_pairs = find_similar_nodes(nodes, similarity_threshold=0.7)
    print(f"類似ノードペア発見: {len(similar_pairs)}組")
    
    convergence_attempts = 0
    for similarity_threshold in [0.9, 0.8, 0.7, 0.6]:
        if len(nodes) >= M + N:
            break
            
        # 類似ノードペアから新しい分岐を作成
        similar_pairs = find_similar_nodes(nodes, similarity_threshold)
        print(f"  閾値{similarity_threshold}: {len(similar_pairs)}組の類似ペア")
        
        for node1_id, node2_id, sim in similar_pairs[:5]:  # 上位5組まで
            if len(nodes) + 2 >= M + N:
                break
                
            node1, node2 = nodes[node1_id], nodes[node2_id]
            
            # 新しい収束ノードを作成
            convergence_node = Node(next_id, False)
            convergence_node.creation_context = f"convergence_{node1_id}_{node2_id}"
            
            # 最適な分別器を選択
            combined_vec = (node1.vec + node2.vec) / 2
            best_sep = np.argmax([split_gain(combined_vec, P[i]) for i in range(K)])
            convergence_node.sep = best_sep
            convergence_node.vec = combined_vec.copy()
            
            # 子ノードを作成
            prow = np.array(P[best_sep])
            v1 = combined_vec * prow
            v2 = combined_vec * (1 - prow)
            
            left = Node(next_id + 1, True)
            right = Node(next_id + 2, True)
            left.vec = v1.copy()
            right.vec = v2.copy()
            left.cls = int(np.argmax(left.vec))
            right.cls = int(np.argmax(right.vec))
            left.creation_context = f"conv_left_{next_id}"
            right.creation_context = f"conv_right_{next_id}"
            
            # エッジ設定（DAG構造）
            convergence_node.add_outgoing(next_id + 1)
            convergence_node.add_outgoing(next_id + 2)
            left.add_incoming(next_id)
            right.add_incoming(next_id)
            
            # 類似ノードからの入力エッジ
            convergence_node.add_incoming(node1_id)
            convergence_node.add_incoming(node2_id)
            node1.add_outgoing(next_id)
            node2.add_outgoing(next_id)
            
            nodes[next_id] = convergence_node
            nodes[next_id + 1] = left
            nodes[next_id + 2] = right
            next_id += 3
            convergence_attempts += 1
            
            print(f"    収束ノード{next_id-3}を作成 (類似度{sim:.3f})")
    
    print(f"収束ノード作成: {convergence_attempts}個")
    
    # Phase 3: パターンベース拡張
    dag_created, next_id = build_dag_from_patterns(nodes, next_id, N, M, K, P)
    print(f"Phase 3完了: {dag_created}個のDAG構造作成")
    
    # Phase 4: 残り予算での拡張
    expand_remaining_budget(nodes, next_id, N, M, K, P)
    
    return list(nodes.values())

def expand_remaining_budget(nodes, next_id, N, M, K, P):
    """残り予算での追加ノード作成"""
    print(f"残り予算活用: 現在{len(nodes)}ノード, 予算{M+N}")
    
    # 低純度葉ノードを拡張
    leaf_nodes = [(nid, n) for nid, n in nodes.items() if n.is_leaf]
    leaf_performance = []
    
    for node_id, node in leaf_nodes:
        if node.vec is not None and node.vec.sum() > 0:
            purity = node.vec[node.cls] / node.vec.sum()
            leaf_performance.append((purity, node_id, node))
    
    leaf_performance.sort()  # 純度の低い順
    
    expansions = 0
    for purity, node_id, node in leaf_performance:
        if len(nodes) + 2 > M + N:
            break
            
        if purity > 0.8:  # 十分純度が高い
            continue
            
        # 葉ノードを内部ノードに変換
        node.is_leaf = False
        node.cls = None
        
        # 最適な分別器を選択
        best_i = np.argmax([split_gain(node.vec, P[i]) for i in range(K)])
        node.sep = best_i
        
        # 子ノード作成
        v1 = node.vec * np.array(P[best_i])
        v2 = node.vec * (1 - np.array(P[best_i]))
        
        left = Node(next_id, True)
        right = Node(next_id + 1, True)
        left.vec = v1.copy()
        right.vec = v2.copy()
        left.cls = int(np.argmax(left.vec))
        right.cls = int(np.argmax(right.vec))
        left.creation_context = f"expanded_left_{node_id}"
        right.creation_context = f"expanded_right_{node_id}"
        
        nodes[next_id] = left
        nodes[next_id + 1] = right
        
        node.add_outgoing(next_id)
        node.add_outgoing(next_id + 1)
        left.add_incoming(node_id)
        right.add_incoming(node_id)
        
        next_id += 2
        expansions += 1
        
        print(f"  葉ノード{node_id}を拡張 (純度: {purity:.3f})")
    
    print(f"葉ノード拡張: {expansions}個")

def topo_sort(nodes):
    """トポロジカルソート"""
    node_map = {nd.idx: nd for nd in nodes}
    indeg = defaultdict(int)
    for nd in nodes:
        for o in nd.out:
            if o in node_map:
                indeg[o] += 1
    
    order = []
    queue = [0] if 0 in node_map else []
    
    while queue:
        x = queue.pop(0)
        order.append(x)
        nd = node_map[x]
        for o in nd.out:
            if o in node_map:
                indeg[o] -= 1
                if indeg[o] == 0:
                    queue.append(o)
    
    return order

def propagate(nodes, P):
    """確率伝播計算（DAG対応）"""
    node_map = {nd.idx: nd for nd in nodes}
    
    # 初期化
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
    
    # 最終的なクラス割り当て
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

def analyze_dag_structure(nodes):
    """DAG構造を分析"""
    total_edges = sum(len(n.out) for n in nodes)
    tree_edges = len(nodes) - 1
    shared_edges = total_edges - tree_edges
    
    incoming_counts = [len(n.incoming) for n in nodes]
    multi_parent_nodes = sum(1 for count in incoming_counts if count > 1)
    
    print(f"DAG構造分析:")
    print(f"  総エッジ数: {total_edges}")
    print(f"  木構造エッジ: {tree_edges}")
    print(f"  共有エッジ数: {shared_edges}")
    print(f"  複数親ノード: {multi_parent_nodes}")
    
    return shared_edges

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # 段階的DAG構築
    nodes = progressive_dag_construction(N, M, K, P)
    
    # 確率伝播と評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    
    # DAG構造分析
    shared_edges = analyze_dag_structure(nodes)
    
    print(f"\n真のDAG構築結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
