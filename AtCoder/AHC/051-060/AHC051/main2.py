import sys
import numpy as np
import random
from collections import defaultdict
from tqdm import tqdm

np.set_printoptions(precision=4, suppress=True)

class Node:
    def __init__(self, idx, is_leaf=False):
        self.idx = idx
        self.is_leaf = is_leaf
        self.vec = None       # np.array([class_mass])
        self.cls = None       # int: assigned class
        self.sep = None      # for internal: which separator (feature row) [0..K-1]
        self.out = []        # [out0, out1]: outgoing node indices (for internal)

# 分割利得
def split_gain(vec, prow):
    v1 = vec * np.array(prow)
    v2 = vec * (1 - np.array(prow))
    return (sum(vec) - max(vec)) - ((sum(v1) - v1.max()) + (sum(v2) - v2.max()))

# greedy分割
def build_greedy(N, M, K, P):
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
        out1, out2 = nd.out
        node_map[out1].vec += v * prow
        node_map[out2].vec += v * (1 - prow)
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
                idx = nodes[idx].out[0] if random.random() < prob else nodes[idx].out[1]
            count[c] += int(nodes[idx].cls == c)
    recall = count / num
    sigma = N - recall.sum()
    return sigma

# 山登り法

def deepcopy_nodes(nodes):
    idx_map = {}
    new_nodes = []
    for n in nodes:
        new_n = Node(n.idx, n.is_leaf)
        new_n.sep = n.sep
        new_n.cls = n.cls
        new_n.out = list(n.out)
        new_n.vec = n.vec.copy() if n.vec is not None else None
        new_nodes.append(new_n)
        idx_map[n.idx] = new_n
    return new_nodes

def op_change_sep(nodes, K):
    choices = [n for n in nodes if not n.is_leaf]
    if not choices: return False
    n = random.choice(choices)
    old = n.sep
    new = random.randrange(K)
    if new == old: return False
    n.sep = new
    return True

# 新たなグローバルな山登り法

def hillclimb_global(nodes, P, K, steps=3000):
    best_nodes = deepcopy_nodes(nodes)
    propagate(best_nodes, P)
    best_sigma, _ = score(best_nodes)
    pbar = tqdm(range(steps))
    for step in pbar:
        cand_nodes = deepcopy_nodes(best_nodes)
        changed = op_change_sep(cand_nodes, K)
        if not changed:
            continue
        propagate(cand_nodes, P)
        new_sigma, _ = score(cand_nodes)
        if new_sigma < best_sigma:
            best_nodes = deepcopy_nodes(cand_nodes)
            best_sigma = new_sigma
            pbar.set_description(f"step{step} best→{best_sigma:.4f}")
        if step % 100 == 0:
            pbar.set_postfix(sigma=new_sigma, best=best_sigma)
    return best_nodes, best_sigma

def main():
    N, M, K = map(int, sys.stdin.readline().split())
    P = [list(map(float, sys.stdin.readline().split())) for _ in range(K)]
    nodes = build_greedy(N, M, K, P)
    propagate(nodes, P)
    sigma, recall = score(nodes)
    print("Greedy:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(nodes, P):.4f}\n")
    best_nodes, best_sigma = hillclimb_global(nodes, P, K, steps=3000)
    propagate(best_nodes, P)
    sigma, recall = score(best_nodes)
    print("Improved:")
    for i, r in enumerate(recall, 1):
        print(f"  class{i:02d}: success={r:.4f}")
    print(f"  σ={sigma:.4f}  MC σ̂={simulate_sigma(best_nodes, P):.4f}")

if __name__ == "__main__":
    main()
