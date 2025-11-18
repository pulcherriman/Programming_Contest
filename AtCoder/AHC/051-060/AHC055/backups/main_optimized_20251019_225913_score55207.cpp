// g++ -std=gnu++23 -O3 -march=native -pipe -static -s main.cpp -o main
// メモリ管理とアルゴリズムオーダー最適化版

#include <bits/stdc++.h>
using namespace std;

struct Input {
    int N{};
    vector<int> H, C;
    vector<vector<int>> A;

    void read() {
        cin >> N;
        H.resize(N); C.resize(N); A.assign(N, vector<int>(N));
        for (int i = 0; i < N; i++) cin >> H[i];
        for (int i = 0; i < N; i++) cin >> C[i];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> A[i][j];
    }
};

struct SAParams {
    double initial_temp = 100.0;
    double final_temp   = 0.1;
    double time_limit   = 1.92;
};

// 攻撃効率評価（ホットパス最適化）
static inline double attack_efficiency_fast(
    const int weapon_id, const int target_id,
    const Input& input,
    const vector<char>& opened,
    const vector<int>& remaining_hardness)
{
    const int power = input.A[weapon_id][target_id];
    const int rh    = remaining_hardness[target_id];
    const int actual_damage = (power < rh ? power : rh);
    double efficiency = double(actual_damage) - 1.0;

    const int new_hardness = rh - actual_damage;
    if (new_hardness <= 0) {
        const double durability_bonus = input.C[target_id] * 0.5;
        const double opening_bonus    = rh * 0.3;
        efficiency += durability_bonus + opening_bonus;
    }
    (void)opened;
    return efficiency;
}

// v2.1アルゴリズム（ベースライン）
vector<pair<int,int>> generateV21Solution(const Input& input) {
    const int N = input.N;
    vector<char> opened(N, 0);
    vector<int>  available_weapons; available_weapons.reserve(N);
    vector<int>  weapon_durability; weapon_durability.reserve(N);
    vector<int>  remaining_hardness = input.H;
    vector<pair<int,int>> attacks; attacks.reserve(N * 8);

    int opened_count = 0;

    while (opened_count < N) {
        bool made_progress = true;
        while (made_progress && opened_count < N) {
            made_progress = false;
            double best_efficiency = 0.0;
            int best_weapon_idx = -1, best_target = -1;

            for (int w_idx = 0, ws = (int)available_weapons.size(); w_idx < ws; ++w_idx) {
                if (weapon_durability[w_idx] <= 0) continue;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; ++target) {
                    if (opened[target]) continue;
                    const double eff = attack_efficiency_fast(weapon_id, target, input, opened, remaining_hardness);
                    if (eff > best_efficiency) {
                        best_efficiency = eff;
                        best_weapon_idx = w_idx;
                        best_target     = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power     = input.A[weapon_id][best_target];
                attacks.emplace_back(weapon_id, best_target);
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;
                made_progress = true;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = 1;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        int best_box = -1, min_cost = INT_MAX;
        for (int i = 0; i < N; ++i) {
            if (!opened[i] && remaining_hardness[i] < min_cost) {
                min_cost = remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            while (remaining_hardness[best_box] > 0) {
                attacks.emplace_back(-1, best_box);
                remaining_hardness[best_box]--;
            }
            opened[best_box] = 1;
            opened_count++;
            available_weapons.push_back(best_box);
            weapon_durability.push_back(input.C[best_box]);
        }
    }
    return attacks;
}

// 宝箱開封順序抽出（O(n)化）
vector<int> extractBoxOrder(const vector<pair<int,int>>& solution, int N) {
    vector<int> order; order.reserve(N);
    vector<char> seen(N, 0);
    for (auto [weapon, target] : solution) {
        if (weapon == -1 && !seen[target]) {
            seen[target] = 1;
            order.push_back(target);
        }
    }
    return order;
}

// デフォルト順序（硬さ昇順）
vector<int> generateDefaultOrder(const Input& input) {
    vector<int> order(input.N);
    iota(order.begin(), order.end(), 0);
    const auto &H = input.H;
    sort(order.begin(), order.end(), [&](int a, int b){ return H[a] < H[b]; });
    return order;
}

// スコア計算専用（差分計算最適化の核心）
static inline int calculateScoreOptimized(const Input& input, const vector<int>& box_order) {
    const int N = input.N;
    vector<char> opened(N, 0);
    vector<int>  available_weapons; available_weapons.reserve(N);
    vector<int>  weapon_durability; weapon_durability.reserve(N);
    vector<int>  remaining_hardness = input.H;
    int attack_count = 0;
    int opened_count = 0;
    int order_idx = 0;

    while (opened_count < N) {
        bool made_progress = true;
        while (made_progress && opened_count < N) {
            made_progress = false;
            double best_efficiency = 0.0;
            int best_weapon_idx = -1, best_target = -1;

            for (int w_idx = 0, ws = (int)available_weapons.size(); w_idx < ws; ++w_idx) {
                if (weapon_durability[w_idx] <= 0) continue;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; ++target) {
                    if (opened[target]) continue;
                    const double eff = attack_efficiency_fast(weapon_id, target, input, opened, remaining_hardness);
                    if (eff > best_efficiency) {
                        best_efficiency = eff;
                        best_weapon_idx = w_idx;
                        best_target     = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power     = input.A[weapon_id][best_target];
                attack_count++;
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;
                made_progress = true;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = 1;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        int next_box = -1;
        if (order_idx < (int)box_order.size()) {
            const int cand = box_order[order_idx];
            if (!opened[cand]) next_box = cand;
            order_idx++;
        }

        if (next_box == -1) {
            int min_cost = INT_MAX;
            for (int i = 0; i < N; ++i) {
                if (!opened[i] && remaining_hardness[i] < min_cost) {
                    min_cost = remaining_hardness[i];
                    next_box = i;
                }
            }
        }

        if (next_box != -1) {
            attack_count += remaining_hardness[next_box];
            opened[next_box] = 1;
            opened_count++;
            available_weapons.push_back(next_box);
            weapon_durability.push_back(input.C[next_box]);
        }
    }
    return attack_count;
}

// 完全解生成（最終出力用のみ）
vector<pair<int,int>> generateSolutionWithOrder(const Input& input, const vector<int>& box_order) {
    const int N = input.N;
    vector<char> opened(N, 0);
    vector<int>  available_weapons; available_weapons.reserve(N);
    vector<int>  weapon_durability; weapon_durability.reserve(N);
    vector<int>  remaining_hardness = input.H;
    vector<pair<int,int>> attacks; attacks.reserve(N * 8);
    int opened_count = 0;
    int order_idx = 0;

    while (opened_count < N) {
        bool made_progress = true;
        while (made_progress && opened_count < N) {
            made_progress = false;
            double best_efficiency = 0.0;
            int best_weapon_idx = -1, best_target = -1;

            for (int w_idx = 0, ws = (int)available_weapons.size(); w_idx < ws; ++w_idx) {
                if (weapon_durability[w_idx] <= 0) continue;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; ++target) {
                    if (opened[target]) continue;
                    const double eff = attack_efficiency_fast(weapon_id, target, input, opened, remaining_hardness);
                    if (eff > best_efficiency) {
                        best_efficiency = eff;
                        best_weapon_idx = w_idx;
                        best_target     = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power     = input.A[weapon_id][best_target];
                attacks.emplace_back(weapon_id, best_target);
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;
                made_progress = true;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = 1;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        int next_box = -1;
        if (order_idx < (int)box_order.size()) {
            const int cand = box_order[order_idx];
            if (!opened[cand]) next_box = cand;
            order_idx++;
        }

        if (next_box == -1) {
            int min_cost = INT_MAX;
            for (int i = 0; i < N; ++i) {
                if (!opened[i] && remaining_hardness[i] < min_cost) {
                    min_cost = remaining_hardness[i];
                    next_box = i;
                }
            }
        }

        if (next_box != -1) {
            while (remaining_hardness[next_box] > 0) {
                attacks.emplace_back(-1, next_box);
                remaining_hardness[next_box]--;
            }
            opened[next_box] = 1;
            opened_count++;
            available_weapons.push_back(next_box);
            weapon_durability.push_back(input.C[next_box]);
        }
    }
    return attacks;
}

enum NeighborType { SWAP, INSERT, HARDNESS_BASED_MOVE };

// 近傍生成器（メモリ効率最適化）
struct NeighborGen {
    mt19937& rng;
    int last_n = -1;
    unique_ptr<uniform_int_distribution<int>> dist;
    NeighborGen(mt19937& r): rng(r) {}

    inline int rand_idx(int n) {
        if (n != last_n) {
            dist = make_unique<uniform_int_distribution<int>>(0, n - 1);
            last_n = n;
        }
        return (*dist)(rng);
    }
};

vector<int> generateOptimizedNeighbor(const vector<int>& order, const Input& input, NeighborGen& ng, NeighborType type) {
    vector<int> new_order = order;
    const int n = (int)new_order.size();
    if (n < 2) return new_order;

    switch (type) {
        case SWAP: {
            const int i = ng.rand_idx(n);
            const int j = ng.rand_idx(n);
            if (i != j) std::swap(new_order[i], new_order[j]);
            break;
        }
        case INSERT: {
            const int from = ng.rand_idx(n);
            const int to   = ng.rand_idx(n);
            if (from != to) {
                const int val = new_order[from];
                new_order.erase(new_order.begin() + from);
                new_order.insert(new_order.begin() + (to > from ? to - 1 : to), val);
            }
            break;
        }
        case HARDNESS_BASED_MOVE: {
            int min_hardness = INT_MAX, min_idx = -1;
            const int start_search = n >> 1;
            for (int i = start_search; i < n; ++i) {
                const int box_id = new_order[i];
                const int h = input.H[box_id];
                if (h < min_hardness) {
                    min_hardness = h;
                    min_idx = i;
                }
            }
            if (min_idx != -1 && min_idx > 0 && start_search > 0) {
                uniform_int_distribution<int> headDist(0, start_search - 1);
                const int target_pos = headDist(ng.rng);
                const int val = new_order[min_idx];
                new_order.erase(new_order.begin() + min_idx);
                new_order.insert(new_order.begin() + target_pos, val);
            }
            break;
        }
    }
    return new_order;
}

vector<pair<int,int>> optimizedSimulatedAnnealingSolution(const Input& input, const SAParams& params = SAParams()) {
    auto v21_solution = generateV21Solution(input);
    const int v21_score = (int)v21_solution.size();

    auto initial_order = extractBoxOrder(v21_solution, input.N);
    if (initial_order.empty()) {
        cerr << "Warning: Empty initial order, using default order\n";
        initial_order = generateDefaultOrder(input);
    }

    auto current_order = initial_order;
    auto best_order    = initial_order;
    int  current_score = v21_score;
    int  best_score    = v21_score;

    mt19937 rng(42);
    NeighborGen ng(rng);

    const auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;

    // 最適化された近傍重み
    vector<NeighborType> neighbor_types = {SWAP, INSERT, HARDNESS_BASED_MOVE};
    vector<double> neighbor_weights = {0.52, 0.45, 0.03};
    discrete_distribution<int> neighbor_dist(neighbor_weights.begin(), neighbor_weights.end());

    while (true) {
        const auto now   = chrono::high_resolution_clock::now();
        const double elp = chrono::duration<double>(now - start_time).count();
        if (elp >= params.time_limit) break;

        const NeighborType ntype = neighbor_types[neighbor_dist(rng)];
        auto new_order = generateOptimizedNeighbor(current_order, input, ng, ntype);

        // 差分計算による高速化
        const int new_score = calculateScoreOptimized(input, new_order);
        const int delta = new_score - current_score;

        bool accept = false;
        if (ntype == HARDNESS_BASED_MOVE) {
            if (new_score < best_score) accept = true;
        } else {
            if (delta < 0) {
                accept = true;
            } else {
                const double progress = elp / params.time_limit;
                const double temperature =
                    params.initial_temp * (1.0 - progress) + params.final_temp * progress;
                if (temperature > params.final_temp) {
                    const double prob = exp(-double(delta) / temperature);
                    accept = (rng() / (double)rng.max()) < prob;
                }
            }
        }

        if (accept) {
            current_order = std::move(new_order);
            current_score = new_score;
            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
            }
        }

        ++iter;
        if ((iter % 10000) == 0) {
            cerr << "Iter " << iter << ": Best=" << best_score
                 << ", Current=" << current_score << '\n';
        }
    }
	cerr << "Total Iterations: " << iter << endl;

    if (best_score >= v21_score) {
        return v21_solution;
    } else {
        return generateSolutionWithOrder(input, best_order);
    }
}

static inline void solve() {
    Input input; input.read();
    auto attacks = optimizedSimulatedAnnealingSolution(input);
    for (auto [w, b] : attacks) {
        cout << w << ' ' << b << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}