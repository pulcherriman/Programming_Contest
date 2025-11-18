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
        self.efficiency = 0.0  # ノード効率性
        
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

def build_greedy_foundation(N, M, K, P):
    """元の貪欲法をベースとした基盤構築"""
    nodes = {}
    root = Node(0, False)
    root.vec = np.ones(N)
    nodes[0] = root
    next_id = 1
    queue = [root]
    
    # 元の貪欲法と同じロジックで高品質な基盤を構築
    while len(nodes) < M + N and queue:
        nd = queue.pop(0)
        
        # 情報利得最大の分割軸
        best_i = np.argmax([split_gain(nd.vec, P[i]) for i in range(K)])
        nd.sep = best_i
        v1 = nd.vec * np.array(P[best_i])
        v2 = nd.vec * (1 - np.array(P[best_i]))
        
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
    
    # 葉ノード判定
    for nd in nodes.values():
        if not nd.out:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
    
    return nodes, next_id

def identify_dag_opportunities(nodes, P, K):
    """DAG化の機会を特定"""
    opportunities = []
    
    # 効率性を計算
    for node in nodes.values():
        if node.vec is not None and node.vec.sum() > 0:
            if node.is_leaf:
                # 葉ノードの純度
                node.efficiency = node.vec[node.cls] / node.vec.sum()
            else:
                # 内部ノードの分割効率
                best_gain = max(split_gain(node.vec, P[i]) for i in range(K))
                node.efficiency = best_gain / node.vec.sum()
    
    # 類似した分別器を使用するノード群を特定
    separator_groups = defaultdict(list)
    for node in nodes.values():
        if not node.is_leaf and node.sep is not None:
            separator_groups[node.sep].append(node)
    
    # DAG化機会を評価
    for sep, node_list in separator_groups.items():
        if len(node_list) >= 2:
            # 効率性の高いノード群を優先
            node_list.sort(key=lambda x: x.efficiency, reverse=True)
            avg_efficiency = np.mean([n.efficiency for n in node_list])
            opportunities.append((avg_efficiency, sep, node_list))
    
    # 効率性でソート
    opportunities.sort(reverse=True)
    return opportunities

def create_strategic_dag_node(nodes, node_group, separator, N, K, P, next_id):
    """戦略的DAGノード作成"""
    # 最も効率的なノードのベクトルを基準とする
    base_node = max(node_group, key=lambda x: x.efficiency)
    
    # 共有ノードを作成
    shared_node = Node(next_id, False)
    shared_node.sep = separator
    shared_node.vec = base_node.vec.copy()  # 最高効率ノードのベクトルを使用
    
    # 分割効率を再計算して最適化
    best_sep = separator
    best_gain = split_gain(shared_node.vec, P[separator])
    
    # より良い分別器があるかチェック
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
    
    # 効率性計算
    left_child.efficiency = left_child.vec[left_child.cls] / left_child.vec.sum()
    right_child.efficiency = right_child.vec[right_child.cls] / right_child.vec.sum()
    shared_node.efficiency = best_gain / shared_node.vec.sum()
    
    # エッジ設定
    shared_node.add_outgoing(next_id + 1)
    shared_node.add_outgoing(next_id + 2)
    left_child.add_incoming(next_id)
    right_child.add_incoming(next_id)
    
    # 高効率ノードからの接続のみ作成
    high_efficiency_nodes = [n for n in node_group if n.efficiency > 0.3]
    if not high_efficiency_nodes:
        high_efficiency_nodes = node_group[:2]  # 最低2つは接続
    
    for node in high_efficiency_nodes:
        shared_node.add_incoming(node.idx)
        nodes[node.idx].add_outgoing(next_id)
    
    return shared_node, left_child, right_child

def hybrid_dag_construction(N, M, K, P):
    """ハイブリッドDAG構築（高性能＋DAG構造）"""
    print("ハイブリッドDAG構築開始...")
    
    # Phase 1: 高品質基盤構築（元の貪欲法ベース）
    nodes, next_id = build_greedy_foundation(N, M, K, P)
    print(f"Phase 1完了: {len(nodes)}ノード (貪欲法基盤)")
    
    # 初期性能を測定
    propagate(list(nodes.values()), P)
    initial_sigma, _ = score(list(nodes.values()))
    print(f"初期σ: {initial_sigma:.4f}")
    
    # Phase 2: 戦略的DAG化
    dag_opportunities = identify_dag_opportunities(nodes, P, K)
    print(f"DAG化機会: {len(dag_opportunities)}個")
    
    dag_additions = 0
    performance_threshold = initial_sigma * 1.1  # 10%の性能劣化まで許容
    
    for efficiency, sep, node_group in dag_opportunities:
        if len(nodes) + 3 > M + N:
            break
            
        if len(node_group) >= 2 and efficiency > 0.2:
            print(f"分別器{sep}でDAG化試行 (効率性: {efficiency:.3f})")
            
            # DAGノード作成前の性能を保存
            nodes_backup = {k: (v.vec.copy() if v.vec is not None else None, v.cls, v.sep, list(v.out), list(v.incoming)) 
                          for k, v in nodes.items()}
            
            # DAGノード作成
            shared, left, right = create_strategic_dag_node(
                nodes, node_group, sep, N, K, P, next_id
            )
            
            nodes[next_id] = shared
            nodes[next_id + 1] = left
            nodes[next_id + 2] = right
            
            # 性能評価
            propagate(list(nodes.values()), P)
            new_sigma, _ = score(list(nodes.values()))
            
            if new_sigma <= performance_threshold:
                # 性能が許容範囲内
                print(f"  DAG追加成功: σ {initial_sigma:.4f} → {new_sigma:.4f}")
                next_id += 3
                dag_additions += 1
                performance_threshold = new_sigma * 1.05  # 閾値を更新
            else:
                # 性能が悪化しすぎ - ロールバック
                print(f"  性能悪化でロールバック: σ {new_sigma:.4f}")
                del nodes[next_id]
                del nodes[next_id + 1] 
                del nodes[next_id + 2]
                
                # 元の状態に復元
                for k, (vec, cls, sep, out, incoming) in nodes_backup.items():
                    nodes[k].vec = vec
                    nodes[k].cls = cls
                    nodes[k].sep = sep
                    nodes[k].out = out
                    nodes[k].incoming = incoming
    
    print(f"戦略的DAG化完了: {dag_additions}個追加")
    
    return list(nodes.values())

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

def analyze_final_dag(nodes):
    """最終DAG構造分析"""
    total_edges = sum(len(n.out) for n in nodes)
    tree_edges = len(nodes) - 1
    shared_edges = total_edges - tree_edges
    
    incoming_counts = [len(n.incoming) for n in nodes]
    multi_parent_nodes = sum(1 for count in incoming_counts if count > 1)
    max_incoming = max(incoming_counts) if incoming_counts else 0
    
    # 効率性統計
    efficiencies = [n.efficiency for n in nodes if hasattr(n, 'efficiency')]
    avg_efficiency = np.mean(efficiencies) if efficiencies else 0
    
    print(f"最終DAG構造分析:")
    print(f"  総エッジ数: {total_edges}")
    print(f"  木構造エッジ: {tree_edges}")
    print(f"  共有エッジ数: {shared_edges}")
    print(f"  複数親ノード: {multi_parent_nodes}")
    print(f"  最大入力数: {max_incoming}")
    print(f"  平均効率性: {avg_efficiency:.3f}")
    
    return shared_edges, multi_parent_nodes

def advanced_hillclimb(nodes, P, K, steps=3000):
    """高度な山登り法（DAG構造保持）"""
    print("高度な山登り法開始...")
    
    best_nodes = [Node(n.idx, n.is_leaf) for n in nodes]
    for i, n in enumerate(nodes):
        best_nodes[i].vec = n.vec.copy() if n.vec is not None else None
        best_nodes[i].cls = n.cls
        best_nodes[i].sep = n.sep
        best_nodes[i].out = list(n.out)
        best_nodes[i].incoming = list(n.incoming)
        if hasattr(n, 'efficiency'):
            best_nodes[i].efficiency = n.efficiency
    
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
                if step % 300 == 0:
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
    
    # ハイブリッドDAG構築
    nodes = hybrid_dag_construction(N, M, K, P)
    
    # 山登り法で最適化
    nodes, best_sigma = advanced_hillclimb(nodes, P, K, steps=2000)
    
    # 最終評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    
    # DAG構造分析
    shared_edges, multi_parent = analyze_final_dag(nodes)
    
    print(f"\nハイブリッドDAG最終結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  共有エッジ: {shared_edges}, 複数親ノード: {multi_parent}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
