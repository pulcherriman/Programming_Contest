// C++ Performance Optimized Version
// g++ -std=gnu++23 -O3 -march=native -pipe -static -s -flto -ffast-math main.cpp -o main

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
    double time_limit   = 1.93;  // 拡張
};

// 最適化されたホットパス関数
static inline double attack_efficiency_turbo(
    const int weapon_id, const int target_id,
    const vector<vector<int>>& A,
    const vector<int>& C,
    const vector<int>& remaining_hardness)
{
    const int power = A[weapon_id][target_id];
    const int rh    = remaining_hardness[target_id];
    const int actual_damage = min(power, rh);
    double efficiency = static_cast<double>(actual_damage - 1);

    if (__builtin_expect(rh - actual_damage <= 0, 0)) {
        efficiency += C[target_id] * 0.5 + rh * 0.3;
    }
    return efficiency;
}

// v2.1アルゴリズム（高速化版）
vector<pair<int, int>> generateV21SolutionTurbo(const Input& input) {
    const int N = input.N;
    vector<bool> opened(N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    vector<pair<int, int>> attacks;
    attacks.reserve(N * 20); // メモリ事前確保
    available_weapons.reserve(N);
    weapon_durability.reserve(N);

    int opened_count = 0;

    while (opened_count < N) {
        // 武器攻撃フェーズ（最適化版）
        bool made_progress = true;
        while (made_progress && opened_count < N) {
            made_progress = false;
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            const int weapon_count = available_weapons.size();
            for (int w_idx = 0; w_idx < weapon_count; w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; target++) {
                    if (opened[target]) continue;
                    const double efficiency = attack_efficiency_turbo(
                        weapon_id, target, input.A, input.C, remaining_hardness);
                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power = input.A[weapon_id][best_target];
                attacks.emplace_back(weapon_id, best_target);
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;
                made_progress = true;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = true;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        // 手攻撃フェーズ（最適化版）
        int best_box = -1;
        int min_cost = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (!opened[i] && remaining_hardness[i] < min_cost) {
                min_cost = remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            const int cost = remaining_hardness[best_box];
            for (int i = 0; i < cost; i++) {
                attacks.emplace_back(-1, best_box);
            }
            opened[best_box] = true;
            opened_count++;
            available_weapons.push_back(best_box);
            weapon_durability.push_back(input.C[best_box]);
            remaining_hardness[best_box] = 0;
        }
    }
    return attacks;
}

// 順序抽出（最適化版）
vector<int> extractBoxOrderTurbo(const vector<pair<int, int>>& solution) {
    vector<int> order;
    order.reserve(solution.size() / 10); // 概算予約

    for (const auto& [weapon, target] : solution) {
        if (weapon == -1) {
            if (find(order.begin(), order.end(), target) == order.end()) {
                order.push_back(target);
            }
        }
    }
    return order;
}

// デフォルト順序生成（最適化版）
vector<int> generateDefaultOrderTurbo(const Input& input) {
    vector<int> order(input.N);
    iota(order.begin(), order.end(), 0);

    // ラムダ最適化
    sort(order.begin(), order.end(), [&input](int a, int b) noexcept {
        return input.H[a] < input.H[b];
    });
    return order;
}

// 差分計算版解生成（ターボ版）
int calculateSolutionScoreTurbo(const Input& input, const vector<int>& box_order) {
    const int N = input.N;
    vector<bool> opened(N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    available_weapons.reserve(N);
    weapon_durability.reserve(N);

    int attack_count = 0;
    int opened_count = 0;
    int order_idx = 0;

    while (opened_count < N) {
        // 武器攻撃フェーズ（ターボ版）
        bool has_weapon = true;
        while (has_weapon && opened_count < N) {
            has_weapon = false;
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            const int weapon_count = available_weapons.size();
            for (int w_idx = 0; w_idx < weapon_count; w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;
                has_weapon = true;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; target++) {
                    if (opened[target]) continue;
                    const double efficiency = attack_efficiency_turbo(
                        weapon_id, target, input.A, input.C, remaining_hardness);
                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power = input.A[weapon_id][best_target];
                attack_count++;
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = true;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        // 手攻撃フェーズ（ターボ版）
        int next_box = -1;

        // 順序優先
        while (order_idx < static_cast<int>(box_order.size())) {
            const int candidate = box_order[order_idx++];
            if (!opened[candidate]) {
                next_box = candidate;
                break;
            }
        }

        // フォールバック
        if (next_box == -1) {
            int min_cost = INT_MAX;
            for (int i = 0; i < N; i++) {
                if (!opened[i] && remaining_hardness[i] < min_cost) {
                    min_cost = remaining_hardness[i];
                    next_box = i;
                }
            }
        }

        if (next_box != -1) {
            attack_count += remaining_hardness[next_box];
            opened[next_box] = true;
            opened_count++;
            available_weapons.push_back(next_box);
            weapon_durability.push_back(input.C[next_box]);
            remaining_hardness[next_box] = 0;
        }
    }
    return attack_count;
}

// 詳細解生成（ターボ版）
vector<pair<int, int>> generateSolutionWithOrderTurbo(const Input& input, const vector<int>& box_order) {
    const int N = input.N;
    vector<bool> opened(N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    vector<pair<int, int>> attacks;
    attacks.reserve(N * 20);
    available_weapons.reserve(N);
    weapon_durability.reserve(N);

    int opened_count = 0;
    int order_idx = 0;

    while (opened_count < N) {
        // 武器攻撃フェーズ
        bool has_weapon = true;
        while (has_weapon && opened_count < N) {
            has_weapon = false;
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            const int weapon_count = available_weapons.size();
            for (int w_idx = 0; w_idx < weapon_count; w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;
                has_weapon = true;
                const int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < N; target++) {
                    if (opened[target]) continue;
                    const double efficiency = attack_efficiency_turbo(
                        weapon_id, target, input.A, input.C, remaining_hardness);
                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                const int weapon_id = available_weapons[best_weapon_idx];
                const int power = input.A[weapon_id][best_target];
                attacks.emplace_back(weapon_id, best_target);
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;

                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = true;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= N) break;

        // 手攻撃フェーズ
        int next_box = -1;

        // 順序優先
        while (order_idx < static_cast<int>(box_order.size())) {
            const int candidate = box_order[order_idx++];
            if (!opened[candidate]) {
                next_box = candidate;
                break;
            }
        }

        // フォールバック
        if (next_box == -1) {
            int min_cost = INT_MAX;
            for (int i = 0; i < N; i++) {
                if (!opened[i] && remaining_hardness[i] < min_cost) {
                    min_cost = remaining_hardness[i];
                    next_box = i;
                }
            }
        }

        if (next_box != -1) {
            const int cost = remaining_hardness[next_box];
            for (int i = 0; i < cost; i++) {
                attacks.emplace_back(-1, next_box);
            }
            opened[next_box] = true;
            opened_count++;
            available_weapons.push_back(next_box);
            weapon_durability.push_back(input.C[next_box]);
            remaining_hardness[next_box] = 0;
        }
    }
    return attacks;
}

// 近傍操作（最適化版）
enum NeighborType : uint8_t { SWAP, INSERT, HARDNESS_BASED_MOVE };

vector<int> generateHybridNeighborTurbo(const vector<int>& order, const Input& input, mt19937& rng, NeighborType type) {
    vector<int> new_order = order;
    const int size = new_order.size();
    if (size < 2) return new_order;

    uniform_int_distribution<int> dist(0, size - 1);

    switch (type) {
        case SWAP: {
            const int i = dist(rng);
            const int j = dist(rng);
            swap(new_order[i], new_order[j]);
            break;
        }
        case INSERT: {
            const int from = dist(rng);
            const int to = dist(rng);
            if (from != to) {
                const int val = new_order[from];
                new_order.erase(new_order.begin() + from);
                new_order.insert(new_order.begin() + (to > from ? to - 1 : to), val);
            }
            break;
        }
        case HARDNESS_BASED_MOVE: {
            int min_hardness = INT_MAX;
            int min_idx = -1;

            const int start_search = size / 2;
            for (int i = start_search; i < size; i++) {
                const int box_id = new_order[i];
                if (input.H[box_id] < min_hardness) {
                    min_hardness = input.H[box_id];
                    min_idx = i;
                }
            }

            if (min_idx != -1 && min_idx > 0) {
                const int target_pos = uniform_int_distribution<int>(0, start_search - 1)(rng);
                const int val = new_order[min_idx];
                new_order.erase(new_order.begin() + min_idx);
                new_order.insert(new_order.begin() + target_pos, val);
            }
            break;
        }
    }
    return new_order;
}

// ターボハイブリッド焼きなまし法
vector<pair<int, int>> turboHybridSimulatedAnnealingSolution(const Input& input, const SAParams& params = SAParams()) {
    // 1. v2.1解を生成
    auto v21_solution = generateV21SolutionTurbo(input);
    const int v21_score = v21_solution.size();

    // 2. v2.1解から宝箱順序を抽出
    auto initial_order = extractBoxOrderTurbo(v21_solution);

    // 空の場合はデフォルト順序を使用
    if (initial_order.empty()) {
        initial_order = generateDefaultOrderTurbo(input);
    }

    auto current_order = initial_order;
    auto best_order = initial_order;
    int current_score = v21_score;
    int best_score = v21_score;

    mt19937 rng(42);
    const auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;

    // 近傍操作の重み（最適化版）
    constexpr array<NeighborType, 3> neighbor_types = {SWAP, INSERT, HARDNESS_BASED_MOVE};
    constexpr array<double, 3> neighbor_weights = {0.63, 0.35, 0.02};
    discrete_distribution<int> neighbor_dist(neighbor_weights.begin(), neighbor_weights.end());

    // 温度計算の事前計算
    const double temp_ratio = params.final_temp / params.initial_temp;

    while (true) {
        const auto current_time = chrono::high_resolution_clock::now();
        const double elapsed = chrono::duration<double>(current_time - start_time).count();
        if (elapsed >= params.time_limit) break;

        // 近傍解生成（高速版）
        const NeighborType neighbor_type = neighbor_types[neighbor_dist(rng)];
        auto new_order = generateHybridNeighborTurbo(current_order, input, rng, neighbor_type);

        // 新しい解を評価（差分計算）
        const int new_score = calculateSolutionScoreTurbo(input, new_order);
        const int delta = new_score - current_score;

        // 受容判定（最適化版）
        bool accept = false;
        if (neighbor_type == HARDNESS_BASED_MOVE) {
            accept = (new_score < best_score);
        } else {
            if (delta < 0) {
                accept = true;
            } else {
                const double progress = elapsed / params.time_limit;
                const double temperature = params.initial_temp * pow(temp_ratio, progress);
                if (temperature > params.final_temp) {
                    const double prob = exp(-delta / temperature);
                    accept = (static_cast<double>(rng()) / rng.max()) < prob;
                }
            }
        }

        if (accept) {
            current_order = move(new_order);
            current_score = new_score;

            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
            }
        }

        iter++;
    }

    cerr << "Total Iterations: " << iter << endl;

    // 最良解が見つからなかった場合はv2.1解をそのまま返す
    if (best_score >= v21_score) {
        return v21_solution;
    } else {
        return generateSolutionWithOrderTurbo(input, best_order);
    }
}

void solve() {
    Input input;
    input.read();

    auto attacks = turboHybridSimulatedAnnealingSolution(input);

    for (const auto& [w, b] : attacks) {
        cout << w << " " << b << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}