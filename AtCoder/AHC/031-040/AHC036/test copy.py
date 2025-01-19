import time
import networkx as nx
import random
from collections import deque
import matplotlib.pyplot as plt

# 新しい入力ファイル形式に基づいてデータを読み込む
with open('./tools/in/0640.txt', 'r') as f:
    lines = f.readlines()

# 1行目の解析
N, M, T, La, Lb = map(int, lines[0].split())

# グラフの初期化
graph = nx.Graph()

# 辺の追加
for i in range(1, M + 1):
    u, v = map(int, lines[i].split())
    graph.add_edge(u, v)

# tListの取得
tList = list(map(int, lines[M + 1].split()))

# tSetの定義
tSet = set(tList)

# 各頂点の座標を取得
coordinates = []
for i in range(M + 2, M + 2 + N):
    x, y = map(int, lines[i].split())
    coordinates.append((x, y))

# パスの更新処理
def update_path_with_leaf_insertion(path, leafMap):
    new_path = []
    for i in range(len(path)):
        new_path.append(path[i])
        if path[i] in leafMap:
            # Pi の直後に leafMap[Pi] を挿入
            new_path.append(leafMap[path[i]])
            new_path.append(path[i])
    return new_path

# 新しい評価関数の定義
def evaluate_path(path, tSet):
    path_set = set(path)
    if tSet.issubset(path_set):
        return 100000 - len(path)
    else:
        return len(path)

def simulated_annealing_with_leaf_insertion(graph, start, end, tSet, max_time=5):
    current_path = nx.shortest_path(graph, start, end)
    current_score = evaluate_path(current_path, tSet)
    best_path = current_path[:]
    best_score = current_score

    failed_count = 0
    reset_count = 0
    start_time = time.time()
    while time.time() - start_time < max_time:
        if len(current_path) < 2:
            break
        
        idx = random.randint(0, len(current_path) - 2)
        u, v = current_path[idx], current_path[idx + 1]

        subpath = find_path_between_two_nodes_bfs_no_direct_edge_no_logging(graph, u, v, current_path)

        if subpath and subpath != [u, v]:
            if not any(vertex in current_path for vertex in subpath[1:-1]):
                new_path = update_path_with_subpath_correctly(current_path, u, v, subpath)
                
                new_score = evaluate_path(new_path, tSet)

                if new_score > current_score:
                    failed_count = -1
                    current_path = new_path
                    current_score = new_score

                    if new_score > best_score:
                        best_path = new_path
                        best_score = new_score
        failed_count += 1
        if failed_count > len(current_path) * 3:
            if best_score > 10000:
                break
            current_path = perturb_path_avoid_local_optima(graph, current_path)
            current_score = evaluate_path(current_path, tSet)
            failed_count = 0
            reset_count+=1
        if reset_count > 100:
            break

    return best_path, best_score

# Define the function to find an alternative path
def find_path_between_two_nodes_bfs_no_direct_edge_no_logging(graph, u, v, visited):
    queue = deque([[u]])
    visited = set(visited)
    visited.discard(v)
    
    while queue:
        path = queue.popleft()
        node = path[-1]
        if len(path) > 5:
            break
        
        if node == v and len(path) > 2:
            return path
        
        for neighbor in graph[node]:
            if neighbor not in visited and neighbor not in path:
                new_path = list(path)
                new_path.append(neighbor)
                queue.append(new_path)

    return [u, v]

# Define the function to update the path with a subpath
def update_path_with_subpath_correctly(original_path, u, v, subpath):
    u_index = original_path.index(u)
    v_index = original_path.index(v)
    
    new_path = original_path[:u_index] + subpath + original_path[v_index + 1:]
    return new_path

# Define the new perturbation function
def perturb_path_avoid_local_optima(graph, path):
    unvisited_vertices = set(graph.nodes()) - set(path)
    candidates = []
    for vertex in unvisited_vertices:
        neighbors = list(graph.neighbors(vertex))
        if any(neighbor in path for neighbor in neighbors):
            candidates.append(vertex)
    
    if not candidates:
        return path  # 該当する頂点がない場合、パスは変更されない
    
    u = random.choice(candidates)

    u_neighbors_in_path = [neighbor for neighbor in graph.neighbors(u) if neighbor in path]

    if len(u_neighbors_in_path) < 2:
        return path  # 該当する頂点対がない場合、パスは変更されない
    
    a, b = random.sample(u_neighbors_in_path, 2)
    
    a_index = path.index(a)
    b_index = path.index(b)

    if a_index < b_index:
        new_path = path[:a_index + 1] + [u] + path[b_index:]
    else:
        new_path = path[:b_index + 1] + [u] + path[a_index:]

    return new_path

# 実行
start_vertex = 0
end_vertex = tList[-1]
final_path_time_limited, final_length_time_limited = simulated_annealing_with_leaf_insertion(graph, start_vertex, end_vertex, tSet)

# 追加処理
path_set = set(final_path_time_limited)
final_path = []
for v in final_path_time_limited:
	final_path.append(v)
	for adj in graph[v]:
		if not adj in path_set:
			final_path.append(adj)
			path_set.add(adj)

print(final_path)
print(final_length_time_limited)
