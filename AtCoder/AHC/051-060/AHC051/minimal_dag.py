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
        self.vec = None
        self.cls = None
        self.sep = None
        self.out = []
        self.incoming = []
        
    def add_outgoing(self, target_idx):
        if target_idx not in self.out:
            self.out.append(target_idx)
    
    def add_incoming(self, source_idx):
        if source_idx not in self.incoming:
            self.incoming.append(source_idx)

def split_gain(vec, prow):
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def build_greedy(N, M, K, P):
    """元の貪欲法"""
    nodes = []
    root = Node(0, False)
    root.vec = np.ones(N)
    nodes.append(root)
    next_id = 1
    queue = [root]
    
    while len(nodes) < M + N and queue:
        nd = queue.pop(0)
        best_i = np.argmax([split_gain(nd.vec, P[i]) for i in range(K)])
        nd.sep = best_i
        v1 = nd.vec * np.array(P[best_i])
        v2 = nd.vec * (1 - np.array(P[best_i]))
        left = Node(next_id, False)
        right = Node(next_id + 1, False)
        left.vec = v1.copy()
        right.vec = v2.copy()
        nodes.append(left)
        nodes.append(right)
        nd.out = [left.idx, right.idx]
        queue.append(left)
        queue.append(right)
        next_id += 2
    
    for nd in nodes:
        if not nd.out:
            nd.is_leaf = True
            nd.cls = int(np.argmax(nd.vec))
    return nodes

def add_minimal_dag_structure(nodes, P, K):
    """最小限のDAG構造を追加（性能劣化を最小化）"""
    print("最小限DAG構造追加...")
    
    node_map = {n.idx: n for n in nodes}
    
    # 同じ分別器を使用するノードペアを発見
    separator_usage = defaultdict(list)
    for node in nodes:
        if not node.is_leaf and node.sep is not None:
            separator_usage[node.sep].append(node)
    
    dag_additions = 0
    
    # 最も頻繁に使用される分別器の上位2つでDAG構造を作成
    frequent_separators = sorted(separator_usage.items(), 
                               key=lambda x: len(x[1]), reverse=True)
    
    for sep, node_list in frequent_separators[:2]:  # 上位2つのみ
        if len(node_list) >= 2 and dag_additions < 2:  # 最大2つのDAG構造
            # 最も類似したベクトルを持つ2ノードを選択
            best_pair = None
            best_similarity = -1
            
            for i, n1 in enumerate(node_list):
                for n2 in node_list[i+1:]:
                    if n1.vec is not None and n2.vec is not None:
                        v1_norm = n1.vec / (n1.vec.sum() + 1e-12)
                        v2_norm = n2.vec / (n2.vec.sum() + 1e-12)
                        similarity = np.dot(v1_norm, v2_norm)
                        if similarity > best_similarity:
                            best_similarity = similarity
                            best_pair = (n1, n2)
            
            if best_pair and best_similarity > 0.5:  # 閾値を設けて品質を保証
                n1, n2 = best_pair
                print(f"分別器{sep}でDAG接続: ノード{n1.idx}→{n2.idx} (類似度: {best_similarity:.3f})")
                
                # 既存ノード間に新しいエッジを追加
                if n2.idx not in n1.out:
                    n1.add_outgoing(n2.idx)
                    n2.add_incoming(n1.idx)
                    dag_additions += 1
    
    print(f"DAG構造追加: {dag_additions}個")
    return dag_additions

def topo_sort(nodes):
    node_map = {nd.idx: nd for nd in nodes}
    indeg = defaultdict(int)
    for nd in nodes:
        for o in nd.out:
            indeg[o] += 1
    order = []
    dq = [0]
    while dq:
        x = dq.pop(0)
        order.append(x)
        nd = node_map[x]
        for o in nd.out:
            indeg[o] -= 1
            if indeg[o] == 0:
                dq.append(o)
    return order

def propagate(nodes, P):
    node_map = {nd.idx: nd for nd in nodes}
    for nd in nodes:
        nd.vec = np.zeros_like(nodes[0].vec)
    node_map[0].vec = np.ones_like(nodes[0].vec)
    order = topo_sort(nodes)
    for idx in order:
        nd = node_map[idx]
        if nd.is_leaf:
            nd.cls = int(np.argmax(nd.vec))
            continue
        prow = np.array(P[nd.sep])
        v = nd.vec
        
        # DAG対応：複数の出力がある場合は分割
        if len(nd.out) >= 2:
            out1, out2 = nd.out[0], nd.out[1]
            node_map[out1].vec += v * prow
            node_map[out2].vec += v * (1 - prow)
        
        # 追加のDAGエッジがある場合
        for additional_out in nd.out[2:]:
            if additional_out in node_map:
                # 追加出力には小さな重みを付与
                node_map[additional_out].vec += v * 0.1
    
    for nd in nodes:
        if nd.is_leaf:
            nd.cls = int(np.argmax(nd.vec))

def score(nodes):
    N = nodes[0].vec.shape[0]
    tot = np.zeros(N)
    cor = np.zeros(N)
    for n in nodes:
        if n.is_leaf:
            v = n.vec
            tot += v
            cor[n.cls] += v[n.cls]
    recall = cor / (tot + 1e-12)
    sigma = np.sum(tot - cor)
    return sigma, recall

def simulate_sigma(nodes, P, num=10000):
    N = len(P[0])
    count = np.zeros(N)
    for c in range(N):
        for _ in range(num):
            idx = 0
            while not nodes[idx].is_leaf:
                sep = nodes[idx].sep
                prob = P[sep][c]
                # 通常の2分岐のみ使用（DAGエッジは無視）
                if len(nodes[idx].out) >= 2:
                    idx = nodes[idx].out[0] if random.random() < prob else nodes[idx].out[1]
                else:
                    break
            count[c] += int(nodes[idx].cls == c)
    recall = count / num
    sigma = N - recall.sum()
    return sigma

def hillclimb_global(nodes, P, K, steps=5000):
    best_nodes = [Node(n.idx, n.is_leaf) for n in nodes]
    for i, n in enumerate(nodes):
        best_nodes[i].vec = n.vec.copy()
        best_nodes[i].cls = n.cls
        best_nodes[i].sep = n.sep
        best_nodes[i].out = list(n.out)
        best_nodes[i].incoming = list(n.incoming)
    
    propagate(best_nodes, P)
    best_sigma, _ = score(best_nodes)
    
    improvements = 0
    pbar = tqdm(range(steps))
    for step in pbar:
        choices = [n for n in best_nodes if not n.is_leaf]
        if not choices: break
        n = random.choice(choices)
        old = n.sep
        new = random.randrange(K)
        if new == old: continue
        n.sep = new
        propagate(best_nodes, P)
        new_sigma, _ = score(best_nodes)
        if new_sigma < best_sigma:
            best_sigma = new_sigma
            improvements += 1
            pbar.set_description(f"step{step} best→{best_sigma:.4f}")
        else:
            n.sep = old
    
    print(f"山登り法完了: {improvements}回改善")
    return best_nodes, best_sigma

def analyze_dag_structure(nodes):
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
    
    return shared_edges, multi_parent_nodes

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # Phase 1: 元の貪欲法で高品質基盤を構築
    nodes = build_greedy(N, M, K, P)
    propagate(nodes, P)
    sigma, recall = score(nodes)
    print(f"貪欲法ベースライン: σ={sigma:.4f}")
    
    # Phase 2: 最小限のDAG構造を追加
    dag_count = add_minimal_dag_structure(nodes, P, K)
    
    # Phase 3: 山登り法で最適化
    nodes, best_sigma = hillclimb_global(nodes, P, K, steps=4000)
    
    # 最終評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    shared_edges, multi_parent = analyze_dag_structure(nodes)
    
    print(f"\n最小限DAG最終結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  共有エッジ: {shared_edges}, 複数親ノード: {multi_parent}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
