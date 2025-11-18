/**
 * AHC055 - Enhanced Simulated Annealing Solution
 * 複数近傍操作と適応的温度制御による改善版焼きなまし
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

// 強化された焼きなましパラメータ
struct EnhancedSAParams {
    double initial_temp = 150.0;     // 初期温度を上げる
    double final_temp = 0.05;        // 最終温度を下げる
    double time_limit = 1.8;
    double adaptive_factor = 0.1;    // 適応的調整因子
    int restart_interval = 5000;     // 再開間隔
};

// v2.1の武器価値評価
double calculateWeaponValue(int weapon_id, const Input& input,
                           const vector<bool>& opened,
                           const vector<int>& remaining_hardness) {
    double total_value = 0;
    vector<double> effectiveness;

    for (int target = 0; target < input.N; target++) {
        if (opened[target]) continue;

        int power = input.A[weapon_id][target];
        int actual_damage = min(remaining_hardness[target], power);
        double saved_attacks = actual_damage - 1.0;

        if (saved_attacks > 0) {
            effectiveness.push_back(saved_attacks);
        }
    }

    sort(effectiveness.rbegin(), effectiveness.rend());

    int durability = input.C[weapon_id];
    for (int i = 0; i < min(durability, (int)effectiveness.size()); i++) {
        total_value += effectiveness[i];
    }

    return total_value;
}

// v2.1の強化された攻撃効率評価
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

// 指定順序で解を生成
vector<pair<int, int>> generateSolutionWithOrder(const Input& input, const vector<int>& box_order) {
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;
    vector<pair<int, int>> attacks;
    int opened_count = 0;
    int order_idx = 0;

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

        // 順序に従って次の宝箱を選択
        int next_box = -1;
        if (order_idx < box_order.size()) {
            int candidate = box_order[order_idx];
            if (!opened[candidate]) {
                next_box = candidate;
            }
            order_idx++;
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

// 複数の近傍操作
enum NeighborType { SWAP, INSERT, REVERSE };

vector<int> generateNeighbor(const vector<int>& order, mt19937& rng, NeighborType type) {
    vector<int> new_order = order;
    if (new_order.size() < 2) return new_order;

    uniform_int_distribution<int> dist(0, new_order.size() - 1);

    switch (type) {
        case SWAP: {
            int i = dist(rng);
            int j = dist(rng);
            swap(new_order[i], new_order[j]);
            break;
        }
        case INSERT: {
            int i = dist(rng);
            int j = dist(rng);
            if (i != j) {
                int val = new_order[i];
                new_order.erase(new_order.begin() + i);
                new_order.insert(new_order.begin() + (j > i ? j - 1 : j), val);
            }
            break;
        }
        case REVERSE: {
            int i = dist(rng);
            int j = dist(rng);
            if (i > j) swap(i, j);
            reverse(new_order.begin() + i, new_order.begin() + j + 1);
            break;
        }
    }
    return new_order;
}

// 強化された焼きなまし法
vector<pair<int, int>> enhancedSimulatedAnnealingSolution(const Input& input, const EnhancedSAParams& params = EnhancedSAParams()) {
    // 1. v2.1解を生成
    auto v21_solution = generateV21Solution(input);
    int v21_score = v21_solution.size();

    // 2. v2.1解から宝箱順序を抽出
    auto initial_order = extractBoxOrder(v21_solution);

    auto current_order = initial_order;
    auto best_order = initial_order;
    int current_score = v21_score;
    int best_score = v21_score;

    mt19937 rng(42);
    auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;
    int accepted = 0;
    int trials = 0;

    // 近傍操作の重み
    vector<NeighborType> neighbor_types = {SWAP, INSERT, REVERSE};
    vector<double> neighbor_weights = {0.5, 0.3, 0.2};
    discrete_distribution<int> neighbor_dist(neighbor_weights.begin(), neighbor_weights.end());

    while (true) {
        auto current_time = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(current_time - start_time).count();
        if (elapsed >= params.time_limit) break;

        // 適応的温度計算
        double progress = elapsed / params.time_limit;
        double base_temp = params.initial_temp * (1.0 - progress) + params.final_temp * progress;

        // 受容率に基づく適応的調整
        double acceptance_rate = trials > 0 ? (double)accepted / trials : 0.5;
        double temp_factor = 1.0 + params.adaptive_factor * (acceptance_rate - 0.3);
        double temperature = base_temp * temp_factor;

        // 近傍解生成（複数タイプからランダム選択）
        NeighborType neighbor_type = neighbor_types[neighbor_dist(rng)];
        auto new_order = generateNeighbor(current_order, rng, neighbor_type);

        // 新しい解を評価
        auto new_solution = generateSolutionWithOrder(input, new_order);
        int new_score = new_solution.size();
        int delta = new_score - current_score;

        trials++;

        // 受容判定
        bool accept = false;
        if (delta < 0) { // 改善
            accept = true;
        } else if (temperature > params.final_temp) {
            double prob = exp(-delta / temperature);
            accept = (rng() / (double)rng.max()) < prob;
        }

        if (accept) {
            current_order = new_order;
            current_score = new_score;
            accepted++;

            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
            }
        }

        // 統計リセット（適応制御のため）
        if (iter % 1000 == 0) {
            trials = accepted = 0;
        }

        // 再開処理
        if (iter % params.restart_interval == 0 && iter > 0) {
            if (best_score < current_score) {
                current_order = best_order;
                current_score = best_score;
            }
        }

        iter++;
        if (iter % 1000 == 0) {
            cerr << "Iter " << iter << ": Best=" << best_score
                 << ", Current=" << current_score
                 << ", Temp=" << fixed << setprecision(1) << temperature << endl;
        }
    }

    // 最良解が見つからなかった場合はv2.1解をそのまま返す
    if (best_score >= v21_score) {
        return v21_solution;
    } else {
        return generateSolutionWithOrder(input, best_order);
    }
}

void solve() {
    Input input;
    input.read();

    auto attacks = enhancedSimulatedAnnealingSolution(input);

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