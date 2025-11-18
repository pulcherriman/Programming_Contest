/**
 * AHC055 - Hybrid Structural Simulated Annealing Solution with Debug Stats
 * ハイブリッド構造的近傍操作統計追跡版
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

// ハイブリッド焼きなまし法（統計追跡版）
vector<pair<int, int>> hybridStructuralSimulatedAnnealingSolution(const Input& input, const SAParams& params = SAParams()) {
    // 1. v2.1解を生成
    auto v21_solution = generateV21Solution(input);
    int v21_score = v21_solution.size();

    // 2. v2.1解から宝箱順序を抽出
    auto initial_order = extractBoxOrder(v21_solution);

    // 空の場合はデフォルト順序を使用
    if (initial_order.empty()) {
        cerr << "Warning: Empty initial order, using default order" << endl;
        initial_order = generateDefaultOrder(input);
    }

    auto current_order = initial_order;
    auto best_order = initial_order;
    int current_score = v21_score;
    int best_score = v21_score;

    mt19937 rng(42);
    auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;

    // 統計追跡
    vector<int> neighbor_tried(3, 0);    // [SWAP, INSERT, HARDNESS_BASED_MOVE]
    vector<int> neighbor_accepted(3, 0); // [SWAP, INSERT, HARDNESS_BASED_MOVE]
    vector<int> neighbor_improved(3, 0); // [SWAP, INSERT, HARDNESS_BASED_MOVE]
    int total_accepted = 0;
    int total_improved = 0;

    // 近傍操作の重み（SWAP: 60%, INSERT: 25%, HARDNESS_BASED_MOVE: 15%）
    vector<NeighborType> neighbor_types = {SWAP, INSERT, HARDNESS_BASED_MOVE};
    vector<double> neighbor_weights = {0.6, 0.25, 0.15};
    discrete_distribution<int> neighbor_dist(neighbor_weights.begin(), neighbor_weights.end());

    while (true) {
        auto current_time = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(current_time - start_time).count();
        if (elapsed >= params.time_limit) break;

        // 近傍解生成（構造的近傍をランダム選択）
        int neighbor_idx = neighbor_dist(rng);
        NeighborType neighbor_type = neighbor_types[neighbor_idx];
        neighbor_tried[neighbor_idx]++;

        auto new_order = generateHybridNeighbor(current_order, input, rng, neighbor_type);

        // 新しい解を評価
        auto new_solution = generateSolutionWithOrder(input, new_order);
        int new_score = new_solution.size();
        int delta = new_score - current_score;

        // 受容判定
        bool accept = false;
        if (delta < 0) { // 改善
            accept = true;
            neighbor_improved[neighbor_idx]++;
            total_improved++;
        } else {
            double progress = elapsed / params.time_limit;
            double temperature = params.initial_temp * (1.0 - progress) + params.final_temp * progress;
            if (temperature > params.final_temp) {
                double prob = exp(-delta / temperature);
                accept = (rng() / (double)rng.max()) < prob;
            }
        }

        if (accept) {
            neighbor_accepted[neighbor_idx]++;
            total_accepted++;
            current_order = new_order;
            current_score = new_score;

            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
            }
        }

        iter++;
        if (iter % 10000 == 0) {
            cerr << "Iter " << iter << ": Best=" << best_score
                 << ", Current=" << current_score << endl;
        }
    }

    // 統計出力
    cerr << "=== SA Statistics ===" << endl;
    cerr << "Total iterations: " << iter << endl;
    cerr << "Total accepted: " << total_accepted << " (" << (100.0 * total_accepted / iter) << "%)" << endl;
    cerr << "Total improved: " << total_improved << " (" << (100.0 * total_improved / iter) << "%)" << endl;
    cerr << "Initial score: " << v21_score << endl;
    cerr << "Final best score: " << best_score << endl;
    cerr << "Improvement: " << (v21_score - best_score) << endl;

    vector<string> neighbor_names = {"SWAP", "INSERT", "HARDNESS_BASED_MOVE"};
    for (int i = 0; i < 3; i++) {
        cerr << neighbor_names[i] << ":" << endl;
        cerr << "  Tried: " << neighbor_tried[i] << " (" << (100.0 * neighbor_tried[i] / iter) << "%)" << endl;
        cerr << "  Accepted: " << neighbor_accepted[i] << " (" << (100.0 * neighbor_accepted[i] / neighbor_tried[i]) << "%)" << endl;
        cerr << "  Improved: " << neighbor_improved[i] << " (" << (100.0 * neighbor_improved[i] / neighbor_tried[i]) << "%)" << endl;
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

    auto attacks = hybridStructuralSimulatedAnnealingSolution(input);

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