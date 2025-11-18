/**
 * AHC055 - Improved Greedy Solution v2.1
 * v2の問題点を修正：計算複雑度を削減し、効果的な部分のみ残す
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

// v1のシンプルな武器価値評価
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

// 簡素化された攻撃効率評価（宝箱開封ボーナスのみ追加）
double calculateEnhancedAttackEfficiency(int weapon_id, int target_id, const Input& input,
                                       const vector<bool>& opened,
                                       const vector<int>& remaining_hardness) {
    int power = input.A[weapon_id][target_id];
    int actual_damage = min(remaining_hardness[target_id], power);

    // 基本効率
    double efficiency = actual_damage - 1.0;

    // 宝箱開封ボーナス（シンプル版）
    int new_hardness = remaining_hardness[target_id] - actual_damage;
    if (new_hardness <= 0) {
        // 開封により新武器獲得 - 固定ボーナス
        double durability_bonus = input.C[target_id] * 0.5; // 耐久値に比例
        double opening_bonus = remaining_hardness[target_id] * 0.3; // 削減された素手攻撃
        efficiency += durability_bonus + opening_bonus;
    }

    return efficiency;
}

// v1の初期宝箱選択（実績あり）
int selectBestInitialBox(const Input& input, const vector<bool>& opened,
                        const vector<int>& remaining_hardness) {
    double best_score = -1;
    int best_box = -1;

    for (int i = 0; i < input.N; i++) {
        if (opened[i]) continue;

        double weapon_value = calculateWeaponValue(i, input, opened, remaining_hardness);
        double cost = remaining_hardness[i];
        double score = weapon_value / cost;

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

vector<pair<int, int>> improvedGreedySolutionV21(const Input& input) {
    vector<pair<int, int>> attacks;
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H;

    int opened_count = 0;

    while (opened_count < input.N) {
        // 1. 利用可能な武器で攻撃（軽量化された効率評価）
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

                    // 軽量化された効率評価
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

        // 2. v1の安定した初期宝箱選択
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

    auto attacks = improvedGreedySolutionV21(input);

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