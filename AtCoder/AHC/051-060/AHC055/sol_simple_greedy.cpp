/**
 * AHC055 - Simple Greedy Solution
 * 1. 最小硬さの宝箱を開ける
 * 2. 得た武器で最も効率がいい順に攻撃
 * 3. 武器が壊れたら1に戻る
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

// 武器の効率性を計算（攻撃力 / 耐久値消費 = 攻撃力そのもの）
struct WeaponTarget {
    int weapon_id;
    int target_id;
    int power;
    double efficiency;

    WeaponTarget(int w, int t, int p) : weapon_id(w), target_id(t), power(p) {
        efficiency = p; // 1回の攻撃あたりの効率
    }

    bool operator<(const WeaponTarget& other) const {
        return efficiency > other.efficiency; // 効率の高い順
    }
};

vector<pair<int, int>> simpleGreedySolution(const Input& input) {
    vector<pair<int, int>> attacks;
    vector<bool> opened(input.N, false);
    vector<int> available_weapons; // 利用可能な武器のリスト
    vector<int> weapon_durability; // 各武器の残り耐久値

    int opened_count = 0;

    while (opened_count < input.N) {
        // 1. 利用可能な武器がある間は、最も効率的な攻撃を実行
        bool weapon_used = true;
        while (weapon_used && opened_count < input.N) {
            weapon_used = false;

            // 未開封の宝箱に対する最も効率的な攻撃を探す
            WeaponTarget best_attack(-1, -1, 0);
            int best_weapon_idx = -1;

            for (int w_idx = 0; w_idx < available_weapons.size(); w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;

                int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < input.N; target++) {
                    if (opened[target]) continue;

                    int power = input.A[weapon_id][target];
                    WeaponTarget attack(weapon_id, target, power);

                    if (attack.efficiency > best_attack.efficiency) {
                        best_attack = attack;
                        best_weapon_idx = w_idx;
                    }
                }
            }

            // 最も効率的な攻撃が見つかった場合
            if (best_attack.weapon_id != -1) {
                attacks.push_back({best_attack.weapon_id, best_attack.target_id});
                weapon_durability[best_weapon_idx]--;
                weapon_used = true;

                // 宝箱が開いたかチェック
                // 簡単のため、1回の攻撃で開くかどうかは別途計算が必要
                // ここでは攻撃のログだけ記録
            }
        }

        if (opened_count >= input.N) break;

        // 2. 最小硬さの未開封宝箱を選択
        int min_hardness = INT_MAX;
        int target_box = -1;

        for (int i = 0; i < input.N; i++) {
            if (!opened[i] && input.H[i] < min_hardness) {
                min_hardness = input.H[i];
                target_box = i;
            }
        }

        if (target_box == -1) break;

        // 3. その宝箱を素手で開ける
        for (int j = 0; j < input.H[target_box]; j++) {
            attacks.push_back({-1, target_box});
        }

        // 4. 新しい武器を利用可能リストに追加
        opened[target_box] = true;
        opened_count++;
        available_weapons.push_back(target_box);
        weapon_durability.push_back(input.C[target_box]);

        cerr << "Opened box " << target_box << " (hardness=" << input.H[target_box]
             << ", weapon durability=" << input.C[target_box] << ")" << endl;
    }

    return attacks;
}

// より正確なシミュレーション版
vector<pair<int, int>> improvedSimpleGreedy(const Input& input) {
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

            // 最も効率的な攻撃を探す
            double best_efficiency = 0;
            int best_weapon_idx = -1;
            int best_target = -1;

            for (int w_idx = 0; w_idx < available_weapons.size(); w_idx++) {
                if (weapon_durability[w_idx] <= 0) continue;

                int weapon_id = available_weapons[w_idx];

                for (int target = 0; target < input.N; target++) {
                    if (opened[target]) continue;

                    int power = input.A[weapon_id][target];
                    double efficiency = (double)power; // 攻撃力がそのまま効率

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

                    cerr << "Box " << best_target << " opened by weapon " << weapon_id
                         << " (remaining: " << (input.N - opened_count) << ")" << endl;
                }
            }
        }

        if (opened_count >= input.N) break;

        // 2. 最小硬さの未開封宝箱を素手で開ける
        int min_remaining = INT_MAX;
        int target_box = -1;

        for (int i = 0; i < input.N; i++) {
            if (!opened[i] && remaining_hardness[i] < min_remaining) {
                min_remaining = remaining_hardness[i];
                target_box = i;
            }
        }

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

        cerr << "Box " << target_box << " opened by hand (remaining: "
             << (input.N - opened_count) << ")" << endl;
    }

    return attacks;
}

void solve() {
    Input input;
    input.read();

    auto attacks = improvedSimpleGreedy(input);

    int total_h = 0;
    for (int h : input.H) total_h += h;
    int score = total_h - (int)attacks.size() + 1;

    cerr << "Total H: " << total_h << endl;
    cerr << "Total attacks: " << attacks.size() << endl;
    cerr << "Final score: " << score << endl;

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