/**
 * AHC055 - Improved Greedy Solution v1
 * 改善1: 武器価値評価の精密化（期待削減コスト方式）
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
        // 素手攻撃と比較してどれだけ攻撃回数を削減できるか
        double saved_attacks = actual_damage - 1.0; // 1回の武器使用で actual_damage - 1回の素手を節約

        if (saved_attacks > 0) {
            effectiveness.push_back(saved_attacks);
        }
    }

    // 効果の高い順にソート
    sort(effectiveness.rbegin(), effectiveness.rend());

    // 耐久値分の上位効果を合計
    int durability = input.C[weapon_id];
    for (int i = 0; i < min(durability, (int)effectiveness.size()); i++) {
        total_value += effectiveness[i];
    }

    return total_value;
}

// 改善された初期宝箱選択：費用対効果を考慮
int selectBestInitialBox(const Input& input, const vector<bool>& opened,
                        const vector<int>& remaining_hardness) {
    double best_score = -1;
    int best_box = -1;

    for (int i = 0; i < input.N; i++) {
        if (opened[i]) continue;

        // この宝箱を開けることで得られる武器の価値
        double weapon_value = calculateWeaponValue(i, input, opened, remaining_hardness);

        // 開けるのに必要なコスト（現在の残り硬さ）
        double cost = remaining_hardness[i];

        // 費用対効果
        double score = weapon_value / cost;

        if (score > best_score) {
            best_score = score;
            best_box = i;
        }
    }

    // 全宝箱の武器価値が0以下の場合は最小硬さを選択（フォールバック）
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

vector<pair<int, int>> improvedGreedySolution(const Input& input) {
    vector<pair<int, int>> attacks;
    vector<bool> opened(input.N, false);
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness = input.H; // 各宝箱の残り硬さ

    int opened_count = 0;

    while (opened_count < input.N) {
        // 1. 利用可能な武器で攻撃
        bool made_progress = true;
        while (made_progress && opened_count < input.N) {
            made_progress = false;

            // 最も効率的な攻撃を探す（改良版）
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            for (int w_idx = 0; w_idx < available_weapons.size(); w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;

                int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < input.N; target++) {
                    if (opened[target]) continue;

                    int power = input.A[weapon_id][target];
                    int actual_damage = min(remaining_hardness[target], power);

                    // 改善された効率計算：実際のダメージによる削減効果
                    double efficiency = actual_damage - 1.0; // 素手と比較した節約回数

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

                // 宝箱が開いたかチェック
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

        // 新しい武器を追加
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

    auto attacks = improvedGreedySolution(input);

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