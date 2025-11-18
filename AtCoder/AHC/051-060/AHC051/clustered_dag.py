import sys
import numpy as np
import random
from collections import defaultdict
from tqdm import tqdm
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics.pairwise import cosine_similarity
from scipy.spatial.distance import pdist, squareform
import time
import itertools

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
        self.target_classes = None  # このノードが処理対象とするクラス群
        
    def add_outgoing(self, target_idx):
        if target_idx not in self.out:
            self.out.append(target_idx)
    
    def add_incoming(self, source_idx):
        if source_idx not in self.incoming:
            self.incoming.append(source_idx)

def analyze_class_similarity(P, N, K):
    """P行列からクラス間類似度を分析"""
    P_array = np.array(P)  # (K, N)
    
    # クラス別の分別器応答パターン（各クラスをK次元ベクトルで表現）
    class_patterns = P_array.T  # (N, K)
    
    # コサイン類似度計算
    cos_sim = cosine_similarity(class_patterns)
    
    # ユークリッド距離
    euclidean_dist = squareform(pdist(class_patterns, 'euclidean'))
    
    print(f"クラス類似度分析:")
    print(f"  コサイン類似度の平均: {np.mean(cos_sim[np.triu_indices(N, k=1)]):.4f}")
    print(f"  ユークリッド距離の平均: {np.mean(euclidean_dist[np.triu_indices(N, k=1)]):.4f}")
    
    return class_patterns, cos_sim, euclidean_dist

def hierarchical_clustering(class_patterns, N, method='ward'):
    """階層クラスタリングによるクラス群の発見（改善版）"""
    # 適応的クラスタ数決定
    if N <= 4:
        n_clusters = 2
    elif N <= 8:
        n_clusters = 3
    elif N <= 12:
        n_clusters = 4
    elif N <= 16:
        n_clusters = 5
    else:
        n_clusters = 6
    
    # AgglomerativeClusteringを実行
    clustering = AgglomerativeClustering(n_clusters=n_clusters, linkage=method)
    cluster_labels = clustering.fit_predict(class_patterns)
    
    # クラスタ情報を整理
    clusters = defaultdict(list)
    for class_id, cluster_id in enumerate(cluster_labels):
        clusters[cluster_id].append(class_id)
    
    print(f"階層クラスタリング結果 ({method}法, {n_clusters}クラスタ):")
    for cluster_id, classes in clusters.items():
        print(f"  クラスタ{cluster_id}: クラス{classes}")
    
    return clusters, cluster_labels

def split_gain(vec, prow):
    """分割利得計算"""
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def find_best_separator(target_classes, P, K, cluster_labels):
    """対象クラス群に最適な分別器を選択"""
    if len(target_classes) <= 1:
        return 0
    
    # クラスタ間分離 vs クラスタ内分離を判定
    target_clusters = set(cluster_labels[c] for c in target_classes)
    
    if len(target_clusters) > 1:
        # クラスタ間分離：最大分離度の分別器
        best_sep = 0
        best_separation = -1
        
        for k in range(K):
            cluster_probs = {}
            for cluster_id in target_clusters:
                cluster_classes = [c for c in target_classes if cluster_labels[c] == cluster_id]
                cluster_probs[cluster_id] = np.mean([P[k][c] for c in cluster_classes])
            
            # クラスタ間の最大分離度
            probs = list(cluster_probs.values())
            separation = max(probs) - min(probs)
            
            if separation > best_separation:
                best_separation = separation
                best_sep = k
        
        return best_sep
    else:
        # クラスタ内分離：情報利得最大の分別器
        class_vec = np.zeros(len(P[0]))
        for c in target_classes:
            class_vec[c] = 1.0
        
        best_i = np.argmax([split_gain(class_vec, P[i]) for i in range(K)])
        return best_i

def improved_split(target_classes, prow):
    """改善版分割：空集合を防ぐ"""
    left_classes = []
    right_classes = []
    
    # 各クラスを確率に基づいて分割
    for c in target_classes:
        if random.random() < prow[c]:
            left_classes.append(c)
        else:
            right_classes.append(c)
    
    # 空集合を防ぐ調整
    if not left_classes and target_classes:
        left_classes = [target_classes[0]]
        right_classes = target_classes[1:]
    elif not right_classes and target_classes:
        right_classes = [target_classes[-1]]
        left_classes = target_classes[:-1]
    
    return left_classes, right_classes

def build_improved_dag(N, M, K, P, clusters, cluster_labels):
    """改善版DAG構築：真のDAG構造と積極的ノード活用"""
    print("改善版DAG構築開始...")
    
    nodes = {}
    next_id = 0
    node_budget = M + N
    
    # ルートノード作成
    root = Node(next_id, False)
    root.vec = np.ones(N)
    root.target_classes = list(range(N))
    nodes[next_id] = root
    next_id += 1
    
    # 構築キュー：(node_id, target_classes, depth)
    queue = [(root.idx, list(range(N)), 0)]
    
    # ノード共有のためのハッシュテーブル
    subproblem_cache = {}  # (tuple(sorted_classes), depth) -> node_id
    
    while queue and len(nodes) < node_budget:
        current_id, target_classes, depth = queue.pop(0)
        current_node = nodes[current_id]
        
        # 単一クラスなら葉ノード化
        if len(target_classes) == 1:
            current_node.is_leaf = True
            current_node.cls = target_classes[0]
            continue
        
        # 深度制限（無限ループ防止）
        if depth > 10:
            current_node.is_leaf = True
            current_node.cls = max(target_classes, key=lambda c: current_node.vec[c] if current_node.vec is not None else 0.5)
            continue
        
        # 最適分別器選択
        best_sep = find_best_separator(target_classes, P, K, cluster_labels)
        current_node.sep = best_sep
        
        # 確率的分割（改善版）
        left_classes, right_classes = improved_split(target_classes, P[best_sep])
        
        # 子ノード処理
        for child_classes, is_left in [(left_classes, True), (right_classes, False)]:
            if not child_classes:
                continue
            
            # ノード共有チェック（小さな部分問題のみ）
            cache_key = (tuple(sorted(child_classes)), min(depth + 1, 5))
            if cache_key in subproblem_cache and len(child_classes) > 1 and len(child_classes) <= 3:
                # 既存ノードを再利用（DAG構造）
                child_id = subproblem_cache[cache_key]
                current_node.add_outgoing(child_id)
                nodes[child_id].add_incoming(current_id)
                print(f"ノード{child_id}を再利用: クラス{child_classes}")
            else:
                # 新しいノードを作成
                if len(nodes) >= node_budget:
                    break
                
                child = Node(next_id, False)
                child.target_classes = child_classes
                nodes[next_id] = child
                current_node.add_outgoing(next_id)
                child.add_incoming(current_id)
                
                # キャッシュに登録（小さな部分問題のみ）
                if len(child_classes) > 1 and len(child_classes) <= 3:
                    subproblem_cache[cache_key] = next_id
                
                queue.append((next_id, child_classes, depth + 1))
                next_id += 1
    
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
    """確率伝播計算"""
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
        if len(nd.out) >= 2:
            out1, out2 = nd.out[0], nd.out[1]
            node_map[out1].vec += v * prow
            node_map[out2].vec += v * (1 - prow)
        elif len(nd.out) == 1:
            # 1つの子ノードの場合
            node_map[nd.out[0]].vec += v
    for nd in nodes:
        if nd.is_leaf:
            nd.cls = int(np.argmax(nd.vec))

def score(nodes):
    """スコア計算"""
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
    """モンテカルロシミュレーション"""
    N = len(P[0])
    count = np.zeros(N)
    for c in range(N):
        for _ in range(num):
            idx = 0
            while not nodes[idx].is_leaf:
                sep = nodes[idx].sep
                prob = P[sep][c]
                if len(nodes[idx].out) >= 2:
                    idx = nodes[idx].out[0] if random.random() < prob else nodes[idx].out[1]
                elif len(nodes[idx].out) == 1:
                    idx = nodes[idx].out[0]
                else:
                    break
            count[c] += int(nodes[idx].cls == c)
    recall = count / num
    sigma = N - recall.sum()
    return sigma

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # Phase 1: クラス類似性分析
    class_patterns, cos_sim, euclidean_dist = analyze_class_similarity(P, N, K)
    
    # Phase 2: 階層クラスタリング
    clusters, cluster_labels = hierarchical_clustering(class_patterns, N)
    
    # Phase 3: 改善版DAG構築
    nodes = build_improved_dag(N, M, K, P, clusters, cluster_labels)
    
    # Phase 4: 性能評価
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    construction_time = time.time() - start_time
    
    print("\n改善版クラスタベースDAG結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}")
    print(f"  ノード数: {len(nodes)}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
