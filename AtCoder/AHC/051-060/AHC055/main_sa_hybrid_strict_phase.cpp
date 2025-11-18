/**
 * AHC055 - Phase Separated Hybrid Simulated Annealing Solution
 * フェーズ分離版：武器攻撃と手攻撃を完全分離
 */

#include <bits/stdc++.h>
using namespace std;

struct Input {
    int N;
    vector<int> H, C;
    vector<vector<int>> A;

    void read() {
        cin >> N;
        H.resize(N); C.resize(N); A.resize(N, vector<int>(N));
        for (int i = 0; i < N; i++) cin >> H[i];
        for (int i = 0; i < N; i++) cin >> C[i];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> A[i][j];
    }
};

// 焼きなましパラメータ
struct SAParams {
    double initial_temp = 100.0;
    double final_temp = 0.1;
    double time_limit = 1.8;
};

// v2.1の攻撃効率評価
double calculateEnhancedAttackEfficiency(int weapon_id, int target_id, const Input& input,
                                       const vector<bool>& opened,
                                       const vector<int>& remaining_hardness) {
    int power = input.A[weapon_id][target_id];
    int actual_damage = min(remaining_hardness[target_id], power);

    double efficiency = actual_damage - 1.0;

    int new_hardness = remaining_hardness[target_id] - actual_damage;
    if (new_hardness <= 0) {
        double durability_bonus = input.C[target_id] * 0.5;
        double opening_bonus = remaining_hardness[target_id] * 0.3;
        efficiency += durability_bonus + opening_bonus;
    }

    return efficiency;
}

// v2.1アルゴリズムによる解の生成
vector<pair<int, int>> generateV21Solution(const Input& input) {
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    vector<pair<int, int>> attacks;
    int opened_count = 0;

    while (opened_count < input.N) {
        // 武器攻撃を最大限実行
        bool made_progress = true;
        while (made_progress && opened_count < input.N) {
            made_progress = false;
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            for (int w_idx = 0; w_idx < available_weapons.size(); w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;
                int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < input.N; target++) {
                    if (opened[target]) continue;
                    double efficiency = calculateEnhancedAttackEfficiency(
                        weapon_id, target, input, opened, remaining_hardness);
                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                int weapon_id = available_weapons[best_weapon_idx];
                int power = input.A[weapon_id][best_target];
                attacks.push_back({weapon_id, best_target});
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

        if (opened_count >= input.N) break;

        // 最小硬さの宝箱を選択
        int best_box = -1;
        int min_cost = INT_MAX;
        for (int i = 0; i < input.N; i++) {
            if (!opened[i] && remaining_hardness[i] < min_cost) {
                min_cost = remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            while (remaining_hardness[best_box] > 0) {
                attacks.push_back({-1, best_box});
                remaining_hardness[best_box]--;
            }
            opened[best_box] = true;
            opened_count++;
            available_weapons.push_back(best_box);
            weapon_durability.push_back(input.C[best_box]);
        }
    }
    return attacks;
}

// v2.1解から宝箱開封順序を抽出
vector<int> extractBoxOrder(const vector<pair<int, int>>& solution) {
    vector<int> order;
    for (auto [weapon, target] : solution) {
        if (weapon == -1) { // 素手攻撃（新しい宝箱開封）
            if (find(order.begin(), order.end(), target) == order.end()) {
                order.push_back(target);
            }
        }
    }
    return order;
}

// デフォルト順序を生成（空の場合のフォールバック）
vector<int> generateDefaultOrder(const Input& input) {
    vector<int> order;
    for (int i = 0; i < input.N; i++) {
        order.push_back(i);
    }
    // 硬さでソート（小さい順）
    sort(order.begin(), order.end(), [&](int a, int b) {
        return input.H[a] < input.H[b];
    });
    return order;
}

// フェーズ分離版：武器攻撃と手攻撃を完全分離
vector<pair<int, int>> generatePhaseSeparatedSolution(const Input& input, const vector<int>& box_order) {
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    vector<pair<int, int>> attacks;
    int opened_count = 0;
    int order_idx = 0;

    while (opened_count < input.N) {
        // フェーズ1: 武器攻撃フェーズ（すべての武器を使い切る）
        bool has_weapon = true;
        while (has_weapon && opened_count < input.N) {
            has_weapon = false;
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            // 利用可能な武器をチェック
            for (int w_idx = 0; w_idx < available_weapons.size(); w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;
                has_weapon = true;
                int weapon_id = available_weapons[w_idx];

                // 全ターゲットをチェック
                for (int target = 0; target < input.N; target++) {
                    if (opened[target]) continue;
                    double efficiency = calculateEnhancedAttackEfficiency(
                        weapon_id, target, input, opened, remaining_hardness);
                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            if (best_weapon_idx != -1) {
                int weapon_id = available_weapons[best_weapon_idx];
                int power = input.A[weapon_id][best_target];
                attacks.push_back({weapon_id, best_target});
                weapon_durability[best_weapon_idx]--;
                remaining_hardness[best_target] -= power;

                // 宝箱が開いた場合、新しい武器を獲得
                if (remaining_hardness[best_target] <= 0) {
                    opened[best_target] = true;
                    opened_count++;
                    available_weapons.push_back(best_target);
                    weapon_durability.push_back(input.C[best_target]);
                }
            }
        }

        if (opened_count >= input.N) break;

        // フェーズ2: 手攻撃フェーズ（1つの宝箱を完全に開封）
        int next_box = -1;

        // 順序に従って次の宝箱を選択
        while (order_idx < box_order.size()) {
            int candidate = box_order[order_idx];
            order_idx++;
            if (!opened[candidate]) {
                next_box = candidate;
                break;
            }
        }

        // 順序にない場合は最小硬さを選択
        if (next_box == -1) {
            int min_cost = INT_MAX;
            for (int i = 0; i < input.N; i++) {
                if (!opened[i] && remaining_hardness[i] < min_cost) {
                    min_cost = remaining_hardness[i];
                    next_box = i;
                }
            }
        }

        // 選択した宝箱を手で完全に開封
        if (next_box != -1) {
            while (remaining_hardness[next_box] > 0) {
                attacks.push_back({-1, next_box});
                remaining_hardness[next_box]--;
            }
            opened[next_box] = true;
            opened_count++;
            available_weapons.push_back(next_box);
            weapon_durability.push_back(input.C[next_box]);
        }
    }
    return attacks;
}

// 近傍操作の種類
enum NeighborType { SWAP, INSERT, HARDNESS_BASED_MOVE };

// ハイブリッド構造的近傍生成
vector<int> generateHybridNeighbor(const vector<int>& order, const Input& input, mt19937& rng, NeighborType type) {
    vector<int> new_order = order;
    if (new_order.size() < 2) return new_order;

    uniform_int_distribution<int> dist(0, new_order.size() - 1);

    switch (type) {
        case SWAP: {
            // 従来の2要素交換
            int i = dist(rng);
            int j = dist(rng);
            swap(new_order[i], new_order[j]);
            break;
        }
        case INSERT: {
            // 要素挿入：1つを抜いて別の位置に挿入
            int from = dist(rng);
            int to = dist(rng);
            if (from != to) {
                int val = new_order[from];
                new_order.erase(new_order.begin() + from);
                new_order.insert(new_order.begin() + (to > from ? to - 1 : to), val);
            }
            break;
        }
        case HARDNESS_BASED_MOVE: {
            // 耐久力ベース移動：硬さの小さい宝箱を前方に移動
            int min_hardness = INT_MAX;
            int min_idx = -1;

            // 後半の要素から硬さが最小のものを探す
            int start_search = new_order.size() / 2;
            for (int i = start_search; i < new_order.size(); i++) {
                int box_id = new_order[i];
                if (input.H[box_id] < min_hardness) {
                    min_hardness = input.H[box_id];
                    min_idx = i;
                }
            }

            if (min_idx != -1 && min_idx > 0) {
                // 硬さが最小の要素を前方に移動
                int target_pos = uniform_int_distribution<int>(0, start_search - 1)(rng);
                int val = new_order[min_idx];
                new_order.erase(new_order.begin() + min_idx);
                new_order.insert(new_order.begin() + target_pos, val);
            }
            break;
        }
    }
    return new_order;
}

// フェーズ分離ハイブリッド焼きなまし法
vector<pair<int, int>> phaseSeparatedHybridSimulatedAnnealingSolution(const Input& input, const SAParams& params = SAParams()) {
    // 1. v2.1解を生成
    auto v21_solution = generateV21Solution(input);
    int v21_score = v21_solution.size();

    // 2. v2.1解から宝箱順序を抽出
    auto initial_order = extractBoxOrder(v21_solution);

    // 空の場合はデフォルト順序を使用
    if (initial_order.empty()) {
        initial_order = generateDefaultOrder(input);
    }

    auto current_order = initial_order;
    auto best_order = initial_order;
    int current_score = v21_score;
    int best_score = v21_score;

    mt19937 rng(42);
    auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;

    // 近傍操作の重み（SWAP: 63%, INSERT: 35%, HARDNESS_BASED_MOVE: 2%）
    vector<NeighborType> neighbor_types = {SWAP, INSERT, HARDNESS_BASED_MOVE};
    vector<double> neighbor_weights = {0.63, 0.35, 0.02};
    discrete_distribution<int> neighbor_dist(neighbor_weights.begin(), neighbor_weights.end());

    while (true) {
        auto current_time = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(current_time - start_time).count();
        if (elapsed >= params.time_limit) break;

        // 近傍解生成（構造的近傍をランダム選択）
        NeighborType neighbor_type = neighbor_types[neighbor_dist(rng)];
        auto new_order = generateHybridNeighbor(current_order, input, rng, neighbor_type);

        // 新しい解を評価（フェーズ分離版を使用）
        auto new_solution = generatePhaseSeparatedSolution(input, new_order);
        int new_score = new_solution.size();
        int delta = new_score - current_score;

        // 受容判定（HARDNESS_BASED_MOVEには厳格条件を適用）
        bool accept = false;
        if (neighbor_type == HARDNESS_BASED_MOVE) {
            // HARDNESS_BASED_MOVEは過去最高スコアより厳密に良い場合のみ採用
            if (new_score < best_score) {
                accept = true;
            }
        } else {
            // 通常の焼きなまし受容判定
            if (delta < 0) { // 改善
                accept = true;
            } else {
                double progress = elapsed / params.time_limit;
                double temperature = params.initial_temp * (1.0 - progress) + params.final_temp * progress;
                if (temperature > params.final_temp) {
                    double prob = exp(-delta / temperature);
                    accept = (rng() / (double)rng.max()) < prob;
                }
            }
        }

        if (accept) {
            current_order = new_order;
            current_score = new_score;

            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
            }
        }

        iter++;
    }

    // 最良解が見つからなかった場合はv2.1解をそのまま返す
    if (best_score >= v21_score) {
        return v21_solution;
    } else {
        return generatePhaseSeparatedSolution(input, best_order);
    }
}

void solve() {
    Input input;
    input.read();

    auto attacks = phaseSeparatedHybridSimulatedAnnealingSolution(input);

    for (auto [w, b] : attacks) {
        cout << w << " " << b << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}