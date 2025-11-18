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

def split_gain(vec, prow):
    """分割利得計算"""
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

def build_greedy(N, M, K, P):
    """貪欲法による初期DAG構築（元のコードベース）"""
    nodes = []
    root = Node(0, False)
    root.vec = np.ones(N)
    nodes.append(root)
    next_id = 1
    queue = [root]
    
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
        nodes.append(left)
        nodes.append(right)
        nd.out = [left.idx, right.idx]
        queue.append(left)
        queue.append(right)
        next_id += 2
    
    # 葉ノード判定＆クラス決定
    for nd in nodes:
        if not nd.out:
            nd.is_leaf = True
            if nd.vec is None:
                nd.vec = np.zeros(N)
            nd.cls = int(np.argmax(nd.vec))
    return nodes

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
        out1, out2 = nd.out
        node_map[out1].vec += v * prow
        node_map[out2].vec += v * (1 - prow)
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
                idx = nodes[idx].out[0] if random.random() < prob else nodes[idx].out[1]
            count[c] += int(nodes[idx].cls == c)
    recall = count / num
    sigma = N - recall.sum()
    return sigma

def deepcopy_nodes(nodes):
    """ノードのディープコピー"""
    new_nodes = []
    for n in nodes:
        new_n = Node(n.idx, n.is_leaf)
        new_n.sep = n.sep
        new_n.cls = n.cls
        new_n.out = list(n.out)
        new_n.vec = n.vec.copy() if n.vec is not None else None
        new_nodes.append(new_n)
    return new_nodes

# ===== 強化された近傍操作 =====

def op_change_separator(nodes, K):
    """操作1: 分別器変更（元の実装）"""
    choices = [n for n in nodes if not n.is_leaf]
    if not choices: return False
    n = random.choice(choices)
    old = n.sep
    new = random.randrange(K)
    if new == old: return False
    n.sep = new
    return True

def op_swap_separators(nodes, K):
    """操作2: 2つのノードの分別器を交換"""
    internal_nodes = [n for n in nodes if not n.is_leaf]
    if len(internal_nodes) < 2: return False
    
    n1, n2 = random.sample(internal_nodes, 2)
    n1.sep, n2.sep = n2.sep, n1.sep
    return True

def op_change_leaf_class(nodes, N):
    """操作3: 葉ノードのクラス割り当て変更"""
    leaf_nodes = [n for n in nodes if n.is_leaf]
    if not leaf_nodes: return False
    
    n = random.choice(leaf_nodes)
    old_cls = n.cls
    new_cls = random.randrange(N)
    if new_cls == old_cls: return False
    
    n.cls = new_cls
    return True

def op_subtree_separator_optimization(nodes, P, K):
    """操作4: 部分木全体の分別器最適化"""
    internal_nodes = [n for n in nodes if not n.is_leaf]
    if not internal_nodes: return False
    
    # ランダムに部分木のルートを選択
    root_node = random.choice(internal_nodes)
    
    # 部分木内の全内部ノードを取得
    subtree_nodes = get_subtree_nodes(nodes, root_node.idx)
    internal_subtree = [n for n in subtree_nodes if not n.is_leaf]
    
    if len(internal_subtree) < 2: return False
    
    # 部分木内でランダムに分別器を再配置
    separators = [n.sep for n in internal_subtree]
    random.shuffle(separators)
    
    for i, node in enumerate(internal_subtree):
        node.sep = separators[i]
    
    return True

def op_focused_separator_change(nodes, P, K):
    """操作5: 性能に基づく重点的分別器変更"""
    internal_nodes = [n for n in nodes if not n.is_leaf]
    if not internal_nodes: return False
    
    # ノードの重要度を分布の大きさで評価
    node_importance = []
    for node in internal_nodes:
        if node.vec is not None:
            importance = node.vec.sum()
            node_importance.append((importance, node))
    
    if not node_importance: return False
    
    # 重要度に基づく重み付き選択
    node_importance.sort(reverse=True)
    
    # 上位50%から選択
    top_half = node_importance[:len(node_importance)//2 + 1]
    _, selected_node = random.choice(top_half)
    
    # 現在の分別器の情報利得を計算
    current_gain = split_gain(selected_node.vec, P[selected_node.sep])
    
    # より良い分別器を探索
    best_sep = selected_node.sep
    best_gain = current_gain
    
    # 候補分別器をテスト
    candidates = random.sample(range(K), min(K, 10))
    for sep in candidates:
        gain = split_gain(selected_node.vec, P[sep])
        if gain > best_gain:
            best_gain = gain
            best_sep = sep
    
    if best_sep != selected_node.sep:
        selected_node.sep = best_sep
        return True
    
    return False

def op_multi_node_separator_change(nodes, K, num_changes=3):
    """操作6: 複数ノードの分別器を同時変更"""
    internal_nodes = [n for n in nodes if not n.is_leaf]
    if len(internal_nodes) < num_changes: return False
    
    selected_nodes = random.sample(internal_nodes, num_changes)
    
    changed = False
    for node in selected_nodes:
        old_sep = node.sep
        new_sep = random.randrange(K)
        if new_sep != old_sep:
            node.sep = new_sep
            changed = True
    
    return changed

def get_subtree_nodes(nodes, root_idx):
    """指定されたルートの部分木に含まれる全ノードを取得"""
    node_map = {n.idx: n for n in nodes}
    if root_idx not in node_map:
        return []
    
    result = []
    queue = [root_idx]
    
    while queue:
        current_idx = queue.pop(0)
        if current_idx in node_map:
            current_node = node_map[current_idx]
            result.append(current_node)
            queue.extend(current_node.out)
    
    return result

def enhanced_hillclimb(nodes, P, K, steps=5000):
    """強化版山登り法"""
    N = len(P[0])
    
    best_nodes = deepcopy_nodes(nodes)
    propagate(best_nodes, P)
    best_sigma, _ = score(best_nodes)
    
    print(f"山登り法開始: 初期σ={best_sigma:.4f}")
    
    # 操作の重み（動的調整用）
    operation_weights = {
        'change_sep': 0.3,
        'swap_sep': 0.15,
        'change_leaf': 0.1,
        'subtree_opt': 0.2,
        'focused_change': 0.15,
        'multi_change': 0.1
    }
    
    # 操作成功回数の記録
    operation_success = defaultdict(int)
    operation_attempts = defaultdict(int)
    
    improvements = 0
    no_improvement_streak = 0
    
    pbar = tqdm(range(steps))
    for step in pbar:
        cand_nodes = deepcopy_nodes(best_nodes)
        
        # 重み付きランダム選択で操作を選択
        operation = random.choices(
            list(operation_weights.keys()),
            weights=list(operation_weights.values())
        )[0]
        
        operation_attempts[operation] += 1
        
        # 選択された操作を実行
        changed = False
        if operation == 'change_sep':
            changed = op_change_separator(cand_nodes, K)
        elif operation == 'swap_sep':
            changed = op_swap_separators(cand_nodes, K)
        elif operation == 'change_leaf':
            changed = op_change_leaf_class(cand_nodes, N)
        elif operation == 'subtree_opt':
            changed = op_subtree_separator_optimization(cand_nodes, P, K)
        elif operation == 'focused_change':
            changed = op_focused_separator_change(cand_nodes, P, K)
        elif operation == 'multi_change':
            changed = op_multi_node_separator_change(cand_nodes, K)
        
        if not changed:
            continue
        
        propagate(cand_nodes, P)
        new_sigma, _ = score(cand_nodes)
        
        if new_sigma < best_sigma:
            best_nodes = deepcopy_nodes(cand_nodes)
            best_sigma = new_sigma
            improvements += 1
            operation_success[operation] += 1
            no_improvement_streak = 0
            
            pbar.set_description(f"step{step} best→{best_sigma:.4f}")
        else:
            no_improvement_streak += 1
        
        # 動的重み調整（100ステップごと）
        if step % 100 == 0 and step > 0:
            for op in operation_weights:
                if operation_attempts[op] > 0:
                    success_rate = operation_success[op] / operation_attempts[op]
                    # 成功率に基づいて重みを調整
                    operation_weights[op] = 0.05 + success_rate * 0.4
            
            pbar.set_postfix(
                sigma=new_sigma, 
                best=best_sigma, 
                improvements=improvements,
                no_improve_streak=no_improvement_streak
            )
        
        # 長時間改善がない場合の多様化
        if no_improvement_streak > 200:
            # より大きな変更を試す
            for _ in range(3):
                op_multi_node_separator_change(best_nodes, K, num_changes=5)
            propagate(best_nodes, P)
            best_sigma, _ = score(best_nodes)
            no_improvement_streak = 0
    
    print(f"山登り法完了: 最終σ={best_sigma:.4f}, 改善回数={improvements}")
    print("操作成功率:")
    for op in operation_weights:
        if operation_attempts[op] > 0:
            success_rate = operation_success[op] / operation_attempts[op]
            print(f"  {op}: {success_rate:.3f} ({operation_success[op]}/{operation_attempts[op]})")
    
    return best_nodes, best_sigma

def main():
    start_time = time.time()
    
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    
    print(f"問題パラメータ: N={N}, M={M}, K={K}")
    
    # Phase 1: 貪欲法による初期構築
    nodes = build_greedy(N, M, K, P)
    propagate(nodes, P)
    sigma, recall = score(nodes)
    
    print("初期貪欲法結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}\n")
    
    # Phase 2: 強化版山登り法
    best_nodes, best_sigma = enhanced_hillclimb(nodes, P, K, steps=8000)
    
    # Phase 3: 最終評価
    propagate(best_nodes, P)
    sigma, recall = score(best_nodes)
    
    construction_time = time.time() - start_time
    
    print("\n強化版山登り法結果:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(best_nodes, P):.4f}")
    print(f"  ノード数: {len(best_nodes)}")
    print(f"  構築時間: {construction_time:.4f}秒")

if __name__ == "__main__":
    main()
