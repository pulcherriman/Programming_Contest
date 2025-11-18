/**
 * AHC055 - Beam Search Solution
 * ビームサーチによる初期宝箱選択の最適化
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

// ゲーム状態を表現する構造体
struct GameState {
    vector<bool> opened;
    vector<int> available_weapons;
    vector<int> weapon_durability;
    vector<int> remaining_hardness;
    vector<pair<int, int>> attacks;
    int opened_count;
    double score;

    GameState(int N) : opened(N, false), remaining_hardness(N), opened_count(0), score(0) {}

    // 状態のコピーコンストラクタ
    GameState(const GameState& other)
        : opened(other.opened), available_weapons(other.available_weapons),
          weapon_durability(other.weapon_durability), remaining_hardness(other.remaining_hardness),
          attacks(other.attacks), opened_count(other.opened_count), score(other.score) {}
};

// v2.1の武器価値評価関数
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

// 利用可能な武器で最適な攻撃を実行
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

// 素手で宝箱を開ける
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

// 状態の評価関数（将来性を考慮）
double evaluateState(const GameState& state, const Input& input) {
    if (state.opened_count >= input.N) {
        // 完了状態：総攻撃数の逆数（少ないほど良い）
        return 100000.0 - state.attacks.size();
    }

    double score = 0;

    // 利用可能武器の価値
    for (int i = 0; i < state.available_weapons.size(); i++) {
        if (state.weapon_durability[i] > 0) {
            int weapon_id = state.available_weapons[i];
            double weapon_value = calculateWeaponValue(weapon_id, input, state.opened, state.remaining_hardness);
            score += weapon_value * state.weapon_durability[i];
        }
    }

    // 進捗ボーナス：開いた宝箱数に比例
    score += state.opened_count * 10.0;

    // 攻撃数ペナルティ
    score -= state.attacks.size() * 0.1;

    return score;
}

// ビームサーチによる解法
vector<pair<int, int>> beamSearchSolution(const Input& input) {
    const int BEAM_WIDTH = 8; // ビーム幅
    const int MAX_DEPTH = min(20, input.N); // 最大探索深度

    // 初期状態
    GameState initial_state(input.N);
    initial_state.remaining_hardness = input.H;

    vector<GameState> beam = {initial_state};

    for (int depth = 0; depth < MAX_DEPTH && !beam.empty(); depth++) {
        vector<GameState> next_beam;

        for (const auto& state : beam) {
            if (state.opened_count >= input.N) {
                next_beam.push_back(state);
                continue;
            }

            // 武器攻撃を先に実行
            GameState current_state = state;
            performWeaponAttacks(current_state, input);

            if (current_state.opened_count >= input.N) {
                next_beam.push_back(current_state);
                continue;
            }

            // 次に開く宝箱の候補を生成
            vector<pair<double, int>> candidates;
            for (int i = 0; i < input.N; i++) {
                if (current_state.opened[i]) continue;

                double weapon_value = calculateWeaponValue(i, input, current_state.opened, current_state.remaining_hardness);
                double cost = current_state.remaining_hardness[i];
                double score = weapon_value / max(cost, 1.0);

                candidates.push_back({score, i});
            }

            // 上位候補のみ展開
            sort(candidates.rbegin(), candidates.rend());
            int expand_count = min(3, (int)candidates.size()); // 各状態から3候補まで展開

            for (int j = 0; j < expand_count; j++) {
                int box_id = candidates[j].second;
                GameState new_state = current_state;

                openBoxByHand(new_state, box_id, input);
                new_state.score = evaluateState(new_state, input);

                next_beam.push_back(new_state);
            }
        }

        // ビーム幅で制限
        sort(next_beam.begin(), next_beam.end(),
             [](const GameState& a, const GameState& b) { return a.score > b.score; });

        if (next_beam.size() > BEAM_WIDTH) {
            next_beam.resize(BEAM_WIDTH);
        }

        beam = next_beam;
    }

    // 最良の解を選択
    if (beam.empty()) return {};

    GameState best_state = beam[0];

    // 残りを貪欲法で処理
    while (best_state.opened_count < input.N) {
        performWeaponAttacks(best_state, input);

        if (best_state.opened_count >= input.N) break;

        // 最小コストの宝箱を選択
        int best_box = -1;
        int min_cost = INT_MAX;
        for (int i = 0; i < input.N; i++) {
            if (!best_state.opened[i] && best_state.remaining_hardness[i] < min_cost) {
                min_cost = best_state.remaining_hardness[i];
                best_box = i;
            }
        }

        if (best_box != -1) {
            openBoxByHand(best_state, best_box, input);
        } else {
            break;
        }
    }

    return best_state.attacks;
}

void solve() {
    Input input;
    input.read();

    auto attacks = beamSearchSolution(input);

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