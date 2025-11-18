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
        self.depth = 0       # ノードの深さ
        self.quality_score = 0.0  # ノードの品質スコア
        
    def add_outgoing(self, target_idx):
        if target_idx not in self.out:
            self.out.append(target_idx)
    
    def add_incoming(self, source_idx):
        if source_idx not in self.incoming:
            self.incoming.append(source_idx)
    
    def calculate_quality(self):
        """ノードの品質を計算"""
        if self.vec is None or self.vec.sum() == 0:
            return 0.0
        
        if self.is_leaf:
            # 葉ノードは純度で評価
            purity = self.vec[self.cls] / self.vec.sum()
            self.quality_score = purity
        else:
            # 内部ノードは情報利得で評価
            max_class = self.vec.max()
            total = self.vec.sum()
            self.quality_score = max_class / total if total > 0 else 0.0
        
        return self.quality_score

def split_gain(vec, prow):
    """分割利得計算"""
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def build_quality_tree(N, M, K, P):
    """品質重視の初期木構築"""
    nodes = {}
    root = Node(0, False)
    root.vec = np.ones(N)
    root.depth = 0
    nodes[0] = root
    next_id = 1
    
    # 優先度キューで品質の高い分割を優先
    priority_queue = [(root.calculate_quality(), 0, root)]
    
    while len(nodes) < min(40, M//2) and priority_queue:
        # 品質の高いノードから処理
        priority_queue.sort(reverse=True)
        _, _, nd = priority_queue.pop(0)
        
        if nd.is_leaf:
            continue
        
        # 情報利得最大の分割軸を選択
        gains = [split_gain(nd.vec, P[i]) for i in range(K)]
        best_i = np.argmax(gains)
        
        # 利得が小さすぎる場合は葉ノード化
        if gains[best_i] < 0.02:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
            nd.calculate_quality()
            continue
            
        nd.sep = best_i
        v1 = nd.vec * np.array(P[best_i])
        v2 = nd.vec * (1 - np.array(P[best_i]))
        
        # 子ノード作成
        left = Node(next_id, False)
        right = Node(next_id + 1, False)
        left.vec = v1.copy()
        right.vec = v2.copy()
        left.depth = nd.depth + 1
        right.depth = nd.depth + 1
        
        nodes[next_id] = left
        nodes[next_id + 1] = right
        
        nd.add_outgoing(next_id)
        nd.add_outgoing(next_id + 1)
        left.add_incoming(nd.idx)
        right.add_incoming(nd.idx)
        
        # 新しいノードを優先度キューに追加
        priority_queue.append((left.calculate_quality(), next_id, left))
        priority_queue.append((right.calculate_quality(), next_id + 1, right))
        
        next_id += 2
    
    # 残りのノードを葉ノード化
    for nd in nodes.values():
        if not nd.out and not nd.is_leaf:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
            nd.calculate_quality()
    
    return nodes, next_id

def find_merge_candidates(nodes, min_quality=0.3):
    """マージ候補ノードを高品質なものから選択"""
    candidates = []
    
    # 各分別器ごとにノードをグループ化
    separator_groups = defaultdict(list)
    for node in nodes.values():
        if not node.is_leaf and node.sep is not None and node.quality_score > min_quality:
            separator_groups[node.sep].append(node)
    
    # 同じ分別器を使用する高品質ノード群を候補とする
    for sep, node_list in separator_groups.items():
        if len(node_list) >= 2:
            # 品質でソートして上位を選択
            node_list.sort(key=lambda x: x.quality_score, reverse=True)
            candidates.append((sep, node_list[:3]))  # 最大3ノードまで
    
    return candidates

def create_optimized_shared_subtree(nodes, node_group, separator, N, K, P, next_id):
    """最適化された共有部分木作成"""
    shared_node = Node(next_id, False)
    shared_node.sep = separator
    shared_node.depth = min(n.depth for n in node_group) + 1
    
    # 重み付き統合（品質の高いノードにより大きな重み）
    total_weight = sum(n.quality_score for n in node_group)
    shared_node.vec = np.zeros(N)
    
    for node in node_group:
        weight = node.quality_score / total_weight
        shared_node.vec += node.vec * weight
    
    shared_node.calculate_quality()
    
    # より良い分別器があるかチェック
    current_gain = split_gain(shared_node.vec, P[separator])
    best_sep = separator
    best_gain = current_gain
    
    # 上位分別器を試行
    for i in range(K):
        gain = split_gain(shared_node.vec, P[i])
        if gain > best_gain:
            best_gain = gain
            best_sep = i
    
    shared_node.sep = best_sep
    
    # 子ノード作成
    prow = np.array(P[best_sep])
    v1 = shared_node.vec * prow
    v2 = shared_node.vec * (1 - prow)
    
    left_child = Node(next_id + 1, True)
    right_child = Node(next_id + 2, True)
    left_child.vec = v1.copy()
    right_child.vec = v2.copy()
    left_child.cls = int(np.argmax(left_child.vec))
    right_child.cls = int(np.argmax(right_child.vec))
    left_child.depth = shared_node.depth + 1
    right_child.depth = shared_node.depth + 1
    left_child.calculate_quality()
    right_child.calculate_quality()
    
    # エッジ設定
    shared_node.add_outgoing(next_id + 1)
    shared_node.add_outgoing(next_id + 2)
    left_child.add_incoming(next_id)
    right_child.add_incoming(next_id)
    
    # 複数の親からの入力
    for node in node_group:
        shared_node.add_incoming(node.idx)
        nodes[node.idx].add_outgoing(next_id)
    
    return shared_node, left_child, right_child

def intelligent_dag_construction(N, M, K, P):
    """知能的DAG構築"""
    print("知能的DAG構築開始...")
    
    # Phase 1: 高品質初期木構築
    nodes, next_id = build_quality_tree(N, M, K, P)
    print(f"Phase 1完了: {len(nodes)}ノード (高品質初期木)")
    
    # 全ノードの品質を計算
    for node in nodes.values():
        node.calculate_quality()
    
    avg_quality = np.mean([n.quality_score for n in nodes.values()])
    print(f"平均ノード品質: {avg_quality:.3f}")
    
    # Phase 2: 戦略的DAG構築
    merge_candidates = find_merge_candidates(nodes, min_quality=0.2)
    print(f"マージ候補: {len(merge_candidates)}グループ")
    
    dag_structures = 0
    for sep, node_group in merge_candidates:
        if len(nodes) + 3 > M + N:
            break
            
        if len(node_group) >= 2:
            print(f"分別器{sep}でDAG構築: {len(node_group)}ノード")
            
            shared, left, right = create_optimized_shared_subtree(
                nodes, node_group, sep, N, K, P, next_id
            )
            
            nodes[next_id] = shared
            nodes[next_id + 1] = left
            nodes[next_id + 2] = right
            next_id += 3
            dag_structures += 1
            
            print(f"  共有ノード{shared.idx}作成 (品質: {shared.quality_score:.3f})")
    
    print(f"DAG構造作成: {dag_structures}個")
    
    # Phase 3: 適応的拡張
    adaptive_expansion(nodes, next_id, N, M, K, P)
    
    return list(nodes.values())

def adaptive_expansion(nodes, next_id, N, M, K, P):
    """適応的ノード拡張"""
    print(f"適応的拡張: 現在{len(nodes)}ノード, 予算{M+N}")
    
    # 拡張候補の品質評価
    expansion_candidates = []
    for node_id, node in nodes.items():
        if node.is_leaf and node.quality_score < 0.8:
            # 拡張による期待改善度を計算
            if node.vec is not None and node.vec.sum() > 0:
                best_gain = max(split_gain(node.vec, P[i]) for i in range(K))
                improvement_potential = best_gain * node.vec.sum()
                expansion_candidates.append((improvement_potential, node_id, node))
    
    # 改善期待度でソート
    expansion_candidates.sort(reverse=True)
    
    expansions = 0
    for potential, node_id, node in expansion_candidates:
        if len(nodes) + 2 > M + N:
            break
            
        if potential < 0.1:  # 改善期待度が低い
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
        left.depth = node.depth + 1
        right.depth = node.depth + 1
        left.calculate_quality()
        right.calculate_quality()
        
        nodes[next_id] = left
        nodes[next_id + 1] = right
        
        node.add_outgoing(next_id)
        node.add_outgoing(next_id + 1)
        left.add_incoming(node_id)
        right.add_incoming(node_id)
        
        next_id += 2
        expansions += 1
        
        print(f"  ノード{node_id}拡張 (期待改善: {potential:.3f})")
    
    print(f"適応的拡張: {expansions}ノード")

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
    
    # 品質再計算
    for nd in nodes:
        if nd.is_leaf and nd.vec is not None:
            nd.cls = int(np.argmax(nd.vec))
        nd.calculate_quality()

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
    """DAG構造の詳細分析"""
    total_edges = sum(len(n.out) for n in nodes)
    tree_edges = len(nodes) - 1
    shared_edges = total_edges - tree_edges
    
    incoming_counts = [len(n.incoming) for n in nodes]
    multi_parent_nodes = sum(1 for count in incoming_counts if count > 1)
    max_incoming = max(incoming_counts) if incoming_counts else 0
    
    # 品質統計
    qualities = [n.quality_score for n in nodes]
    avg_quality = np.mean(qualities)
    min_quality = np.min(qualities)
    
    print(f"DAG構造詳細分析:")
    print(f"  総エッジ数: {total_edges}")
    print(f"  木構造エッジ: {tree_edges}")
    print(f"  共有エッジ数: {shared_edges}")
    print(f"  複数親ノード: {multi_parent_nodes}")
    print(f"  最大入力数: {max_incoming}")
    print(f"  平均品質: {avg_quality:.3f}")
    print(f"  最低品質: {min_quality:.3f}")
    
    return shared_edges

def hillclimb_dag(nodes, P, K, steps=2000):
    """DAG対応山登り法"""
    print("DAG山登り法開始...")
    
    best_nodes = [Node(n.idx, n.is_leaf) for n in nodes]
    for i, n in enumerate(nodes):
        best_nodes[i].vec = n.vec.copy() if n.vec is not None else None
        best_nodes[i].cls = n.cls
        best_nodes[i].sep = n.sep
        best_nodes[i].out = list(n.out)
        best_nodes[i].incoming = list(n.incoming)
        best_nodes[i].depth = n.depth
        best_nodes[i].quality_score = n.quality_score
    
    propagate(best_nodes, P)
    best_sigma, _ = score(best_nodes)
    
    improvements = 0
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
                improvements += 1
                if step % 200 == 0:
                    print(f"  Step {step}: σ改善 -> {best_sigma:.4f}")
            else:
                node.sep = old_sep  # 戻す
    
    print(f"山登り法完了: {improvements}回改善")
    return best_nodes, best_sigma

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # 知能的DAG構築
    nodes = intelligent_dag_construction(N, M, K, P)
    
    # 初期評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    print(f"初期σ: {sigma:.4f}")
    
    # DAG対応山登り法
    nodes, best_sigma = hillclimb_dag(nodes, P, K, steps=1500)
    
    # 最終評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    
    # DAG構造分析
    shared_edges = analyze_dag_structure(nodes)
    
    print(f"\n知能的DAG構築結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
