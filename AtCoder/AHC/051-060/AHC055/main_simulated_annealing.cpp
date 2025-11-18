/**
 * AHC055 - Simulated Annealing Solution
 * 焼きなまし法による初期宝箱選択順序の最適化
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

// 焼きなましのパラメータ（時間ベース）
struct SAParams {
    double initial_temp = 100.0;
    double final_temp = 0.1;
    double time_limit = 1.8;  // 1.8秒制限（マージン考慮）
};

// ゲーム状態
struct GameState {
    vector<bool> opened;
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness;
    vector<pair<int, int>> attacks;
    int opened_count;

    GameState(int N) : opened(N, false), remaining_hardness(N), opened_count(0) {}
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

// 武器攻撃実行
void performWeaponAttacks(GameState& state, const Input& input) {
    bool made_progress = true;
    while (made_progress && state.opened_count < input.N) {
        made_progress = false;

        double best_efficiency = 0;
        int best_weapon_idx = -1;
        int best_target = -1;

        for (int w_idx = 0; w_idx < state.available_weapons.size(); w_idx++) {
            if (state.weapon_durability[w_idx] <= 0) continue;

            int weapon_id = state.available_weapons[w_idx];

            for (int target = 0; target < input.N; target++) {
                if (state.opened[target]) continue;

                double efficiency = calculateEnhancedAttackEfficiency(
                    weapon_id, target, input, state.opened, state.remaining_hardness);

                if (efficiency > best_efficiency) {
                    best_efficiency = efficiency;
                    best_weapon_idx = w_idx;
                    best_target = target;
                }
            }
        }

        if (best_weapon_idx != -1) {
            int weapon_id = state.available_weapons[best_weapon_idx];
            int power = input.A[weapon_id][best_target];

            state.attacks.push_back({weapon_id, best_target});
            state.weapon_durability[best_weapon_idx]--;
            state.remaining_hardness[best_target] -= power;
            made_progress = true;

            if (state.remaining_hardness[best_target] <= 0) {
                state.opened[best_target] = true;
                state.opened_count++;
                state.available_weapons.push_back(best_target);
                state.weapon_durability.push_back(input.C[best_target]);
            }
        }
    }
}

// 素手で宝箱開封
void openBoxByHand(GameState& state, int box_id, const Input& input) {
    while (state.remaining_hardness[box_id] > 0) {
        state.attacks.push_back({-1, box_id});
        state.remaining_hardness[box_id]--;
    }

    state.opened[box_id] = true;
    state.opened_count++;
    state.available_weapons.push_back(box_id);
    state.weapon_durability.push_back(input.C[box_id]);
}

// 指定された順序で宝箱を開く
int evaluateBoxOrder(const vector<int>& box_order, const Input& input) {
    GameState state(input.N);
    state.remaining_hardness = input.H;

    for (int box_id : box_order) {
        if (state.opened[box_id]) continue;

        performWeaponAttacks(state, input);
        if (state.opened_count >= input.N) break;

        if (!state.opened[box_id]) {
            openBoxByHand(state, box_id, input);
        }
    }

    // 残りを最小硬さで処理
    while (state.opened_count < input.N) {
        performWeaponAttacks(state, input);
        if (state.opened_count >= input.N) break;

        int best_box = -1;
        int min_cost = INT_MAX;
        for (int i = 0; i < input.N; i++) {
            if (!state.opened[i] && state.remaining_hardness[i] < min_cost) {
                min_cost = state.remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            openBoxByHand(state, best_box, input);
        } else {
            break;
        }
    }

    return state.attacks.size();
}

// v2.1アルゴリズムで初期解を生成
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

        // 最小硬さ宝箱を選択
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

// 焼きなまし法による最適化
vector<pair<int, int>> simulatedAnnealingSolution(const Input& input, const SAParams& params = SAParams()) {
    // 初期解：v2.1と同じアルゴリズムで生成
    auto v21_solution = generateV21Solution(input);
    int v21_score = v21_solution.size();

    // v2.1解から宝箱開封順序を抽出
    vector<int> current_order, best_order;
    for (auto [weapon, target] : v21_solution) {
        if (weapon == -1) { // 素手攻撃（新しい宝箱開封）
            if (find(current_order.begin(), current_order.end(), target) == current_order.end()) {
                current_order.push_back(target);
            }
        }
    }
    best_order = current_order;

    int current_score = v21_score;
    int best_score = v21_score;
    bool improved = false;

    double temperature = params.initial_temp;
    mt19937 rng(42);

    auto start_time = chrono::high_resolution_clock::now();
    int iter = 0;

    while (true) {
        auto current_time = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(current_time - start_time).count();

        if (elapsed >= params.time_limit) break;
        // 近傍解生成：ランダムな2要素の交換
        vector<int> new_order = current_order;
        int i = rng() % input.N;
        int j = rng() % input.N;
        swap(new_order[i], new_order[j]);

        int new_score = evaluateBoxOrder(new_order, input);
        int delta = new_score - current_score;

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

            if (current_score < best_score) {
                best_score = current_score;
                best_order = current_order;
                improved = true;
            }
        }

        // 時間ベース温度更新
        double progress = elapsed / params.time_limit;
        temperature = params.initial_temp * (1.0 - progress) + params.final_temp * progress;

        // 進捗表示（大幅削減）
        if (iter % 5000 == 0) {
            cerr << "Iter " << iter << ": Best=" << best_score
                 << ", Temp=" << fixed << setprecision(1) << temperature
                 << ", Time=" << fixed << setprecision(2) << elapsed << "s" << endl;
        }

        iter++;
    }

    // 改善がなかった場合は元のv2.1解を返す
    if (!improved) {
        return v21_solution;
    }

    // 改善があった場合のみ最適順序で再実行
    GameState final_state(input.N);
    final_state.remaining_hardness = input.H;

    for (int box_id : best_order) {
        if (final_state.opened[box_id]) continue;

        performWeaponAttacks(final_state, input);
        if (final_state.opened_count >= input.N) break;

        if (!final_state.opened[box_id]) {
            openBoxByHand(final_state, box_id, input);
        }
    }

    // 残り処理
    while (final_state.opened_count < input.N) {
        performWeaponAttacks(final_state, input);
        if (final_state.opened_count >= input.N) break;

        int best_box = -1;
        int min_cost = INT_MAX;
        for (int i = 0; i < input.N; i++) {
            if (!final_state.opened[i] && final_state.remaining_hardness[i] < min_cost) {
                min_cost = final_state.remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            openBoxByHand(final_state, best_box, input);
        } else {
            break;
        }
    }

    return final_state.attacks;
}

void solve() {
    Input input;
    input.read();

    auto attacks = simulatedAnnealingSolution(input);

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