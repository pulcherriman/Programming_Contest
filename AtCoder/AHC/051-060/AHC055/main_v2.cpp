/**
 * AHC055 - Improved Greedy Solution v2
 * 改善1: 武器価値評価の精密化（期待削減コスト方式）
 * 改善2: 将来価値考慮（武器攻撃による連鎖効果の評価）
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

// 改善された武器価値評価：期待削減コストを計算
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

// 新機能：武器攻撃の将来価値を評価（連鎖効果考慮）
double calculateAttackFutureValue(int weapon_id, int target_id, const Input& input,
                                 const vector<bool>& opened,
                                 const vector<int>& remaining_hardness) {
    int power = input.A[weapon_id][target_id];
    int actual_damage = min(remaining_hardness[target_id], power);
    int new_hardness = remaining_hardness[target_id] - actual_damage;

    double future_value = 0;

    // 宝箱が開かれる場合の将来価値
    if (new_hardness <= 0) {
        // 新武器の価値を評価
        vector<bool> temp_opened = opened;
        vector<int> temp_hardness = remaining_hardness;
        temp_opened[target_id] = true;
        temp_hardness[target_id] = 0;

        double new_weapon_value = calculateWeaponValue(target_id, input, temp_opened, temp_hardness);
        future_value += new_weapon_value * 0.8; // 将来価値の割引率

        // 開いた宝箱分のコスト削減
        future_value += remaining_hardness[target_id] - 1; // 素手攻撃が不要になった分
    }

    return future_value;
}

// 改善された攻撃効率評価（将来価値込み）
double calculateEnhancedAttackEfficiency(int weapon_id, int target_id, const Input& input,
                                       const vector<bool>& opened,
                                       const vector<int>& remaining_hardness) {
    int power = input.A[weapon_id][target_id];
    int actual_damage = min(remaining_hardness[target_id], power);

    // 基本効率：immediate savings
    double immediate_value = actual_damage - 1.0;

    // 将来価値：future chain effects
    double future_value = calculateAttackFutureValue(weapon_id, target_id, input, opened, remaining_hardness);

    // 総合効率 = 即効価値 + 将来価値
    return immediate_value + future_value;
}

// 改善された初期宝箱選択：費用対効果を考慮
int selectBestInitialBox(const Input& input, const vector<bool>& opened,
                        const vector<int>& remaining_hardness) {
    double best_score = -1;
    int best_box = -1;

    for (int i = 0; i < input.N; i++) {
        if (opened[i]) continue;

        double weapon_value = calculateWeaponValue(i, input, opened, remaining_hardness);
        double cost = remaining_hardness[i];

        // 費用対効果にボーナス項目を追加
        double bonus = 0;

        // 低硬度ボーナス：早期に開けやすい宝箱を優遇
        if (cost <= 3) bonus += 2.0;
        else if (cost <= 5) bonus += 1.0;

        // 高耐久武器ボーナス：長く使える武器を優遇
        if (input.C[i] >= 5) bonus += 1.5;
        else if (input.C[i] >= 3) bonus += 0.5;

        double score = (weapon_value + bonus) / cost;

        if (score > best_score) {
            best_score = score;
            best_box = i;
        }
    }

    // フォールバック
    if (best_box == -1) {
        int min_hardness = INT_MAX;
        for (int i = 0; i < input.N; i++) {
            if (!opened[i] && remaining_hardness[i] < min_hardness) {
                min_hardness = remaining_hardness[i];
                best_box = i;
            }
        }
    }

    return best_box;
}

vector<pair<int, int>> improvedGreedySolutionV2(const Input& input) {
    vector<pair<int, int>> attacks;
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;

    int opened_count = 0;

    while (opened_count < input.N) {
        // 1. 利用可能な武器で攻撃（改善版効率評価）
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

                    // 改善された効率評価（将来価値込み）
                    double efficiency = calculateEnhancedAttackEfficiency(
                        weapon_id, target, input, opened, remaining_hardness);

                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_weapon_idx = w_idx;
                        best_target = target;
                    }
                }
            }

            // 攻撃実行
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

        // 2. 改善された初期宝箱選択
        int target_box = selectBestInitialBox(input, opened, remaining_hardness);

        if (target_box == -1) break;

        // 素手で攻撃
        while (remaining_hardness[target_box] > 0) {
            attacks.push_back({-1, target_box});
            remaining_hardness[target_box]--;
        }

        opened[target_box] = true;
        opened_count++;
        available_weapons.push_back(target_box);
        weapon_durability.push_back(input.C[target_box]);
    }

    return attacks;
}

void solve() {
    Input input;
    input.read();

    auto attacks = improvedGreedySolutionV2(input);

    int total_h = 0;
    for (int h : input.H) total_h += h;

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