#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Greedy splitter‑tree builder for the probabilistic classifier‑separator task.

* Reads N, M, K and a K×N matrix P from **stdin**.
* Builds a binary decision tree (no DAG sharing) with at most M separator
  copies, selecting at each internal node the separator that maximises the
  reduction of mis‑classification mass.
* After construction, prints **per‑class recall**
  (probability that element *j* reaches endpoint T_j).

Run:
    python3 classifier_greedy.py < in.txt
"""
import sys
import heapq
from typing import List, Tuple

EPS = 1e-12

# ─────────────────────────────── I/O ────────────────────────────────

def read_input() -> Tuple[int, int, int, List[List[float]]]:
    data = sys.stdin.read().strip().split()
    if len(data) < 3:
        sys.exit("Input too short (need N M K header)")
    it = iter(data)
    N = int(next(it)); M = int(next(it)); K = int(next(it))
    P: List[List[float]] = [[0.0]*N for _ in range(K)]
    for i in range(K):
        for j in range(N):
            try:
                x = float(next(it))
            except StopIteration:
                sys.exit(f"Not enough numbers for P (row {i})")
            # clamp to [0,1]
            if x < 0.0: x = 0.0
            if x > 1.0: x = 1.0
            P[i][j] = x
    return N, M, K, P

# ───────────────────────────── utilities ────────────────────────────

def cost_leaf(v: List[float]) -> float:
    s = sum(v)
    m = max(v)
    return s - m  # mis‑classified mass at this leaf

def split_vec(v: List[float], prow: List[float], tmp1: List[float], tmp2: List[float]):
    for j, x in enumerate(v):
        p = prow[j]
        tmp1[j] = x * p
        tmp2[j] = x * (1.0 - p)

# ──────────────────────────── tree node ─────────────────────────────

class Node:
    __slots__ = ("id", "v", "cost", "cls", "best_i", "best_gain", "left", "right", "alive")
    def __init__(self, nid: int, v: List[float]):
        self.id = nid
        self.v = v
        self.cost = cost_leaf(v)
        self.cls = v.index(max(v))  # target endpoint if this is a leaf
        self.best_i = -1            # best separator index
        self.best_gain = 0.0        # gain achieved by that separator
        self.left = -1
        self.right = -1
        self.alive = True           # becomes False when split

# ─────────────────────────── greedy splitting ───────────────────────

def compute_best_split(node: Node, P: List[List[float]]):
    if node.cost <= EPS:  # already perfect
        node.best_i = -1; node.best_gain = 0.0; return
    N = len(node.v); K = len(P)
    tmp1 = [0.0]*N; tmp2 = [0.0]*N
    best_gain = 0.0; best_i = -1
    for i in range(K):
        prow = P[i]
        split_vec(node.v, prow, tmp1, tmp2)
        gain = node.cost - (cost_leaf(tmp1) + cost_leaf(tmp2))
        if gain > best_gain + 1e-18:
            best_gain = gain; best_i = i
    node.best_i = best_i; node.best_gain = best_gain


def build_tree(N: int, M: int, K: int, P: List[List[float]]):
    nodes: List[Node] = []
    # root node with initial vector (all classes mass 1)
    root = Node(0, [1.0]*N)
    nodes.append(root)
    compute_best_split(root, P)

    heap: List[Tuple[float,int]] = []  # (−gain, node_id)
    if root.best_i >= 0 and root.best_gain > EPS:
        heapq.heappush(heap, (-root.best_gain, root.id))

    used_separators = 0
    next_id = 1

    while used_separators < M and heap:
        neg_gain, nid = heapq.heappop(heap)
        node = nodes[nid]
        if not node.alive:
            continue  # already split by another pull
        # recompute best split (heap may be stale)
        compute_best_split(node, P)
        if node.best_i < 0 or node.best_gain <= EPS:
            continue  # no profitable split

        # perform split
        i = node.best_i
        tmp1 = [0.0]*N; tmp2 = [0.0]*N
        split_vec(node.v, P[i], tmp1, tmp2)
        left = Node(next_id, tmp1[:]);   right = Node(next_id+1, tmp2[:])
        nodes.append(left); nodes.append(right)
        node.left = left.id; node.right = right.id; node.alive = False
        used_separators += 1; next_id += 2

        # enqueue children if further profitable
        compute_best_split(left, P)
        compute_best_split(right, P)
        if left.best_i >= 0 and left.best_gain > EPS:
            heapq.heappush(heap, (-left.best_gain, left.id))
        if right.best_i >= 0 and right.best_gain > EPS:
            heapq.heappush(heap, (-right.best_gain, right.id))

    leaves = [nd for nd in nodes if nd.alive]
    return nodes, leaves, used_separators

# ──────────────────────────── evaluation ────────────────────────────

def class_origin_stats(N: int, leaves: List[Node]):
    """Return per‑class totals, correct mass, and per‑class recall ≈ P(correct)."""
    tot = [0.0]*N; correct = [0.0]*N
    for nd in leaves:
        v   = nd.v
        tgt = nd.cls
        for j, x in enumerate(v):
            tot[j] += x
            if j == tgt:
                correct[j] += x
    recall = [ (correct[j] / tot[j] if tot[j] > 0 else 0.0) for j in range(N) ]
    sigma  = sum(tot[j] - correct[j] for j in range(N))  # total mis‑classification mass
    return sigma, recall, correct, tot

# ─────────────────────────────── main ───────────────────────────────

def main():
    N, M, K, P = read_input()
    nodes, leaves, used = build_tree(N, M, K, P)
    sigma, recall, correct, tot = class_origin_stats(N, leaves)

    # ── output ──
    print(f"sigma={sigma:.10f} used_M={used} leaves={len(leaves)}")
    print("# per‑class recall (probability that the right element arrives at its endpoint)")
    for j in range(N):
        print(f"class {j+1:02d}: recall={recall[j]:.10f}  correct_mass={correct[j]:.10f}  total_mass={tot[j]:.10f}")

    print("\n# leaf details: leaf_id -> T_cls  (total, correct, error)")
    for nd in leaves:
        v = nd.v
        s = sum(v)
        j = nd.cls
        corr = v[j]
        err = s - corr
        print(f"leaf {nd.id:3d} -> T_{j+1:02d}  total={s:.10f}  correct={corr:.10f}  error={err:.10f}")

if __name__ == "__main__":
    main()
