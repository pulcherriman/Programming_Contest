#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <chrono>
#include <cstdlib>
#include <array>
#include <queue>
using namespace std;

using pii = pair<int, int>;
#define rep(i, n) for(int i = 0; i < (int)(n); ++i)

const int N = 20, H = 1000;
const int GRID_ROWS = 5, GRID_COLS = 10;  // パレット分割数
const int MAX_WELL_CAPACITY = 8;  // 各ウェルの最大容量（固定値）
const int MAX_PRECOMPUTE_TIME_MS = 60000;  // 前処理制限時間をさらに短縮（0.6秒）
int K, T, D;
int actual_max_precompute_grams = 8;  // 実際に前処理できた最大グラム数

// 色を表現する構造体
struct Color {
    double c, m, y;
    Color() : c(0), m(0), y(0) {}
    Color(double c_, double m_, double y_) : c(c_), m(m_), y(y_) {}
    
    Color operator+(const Color& other) const {
        return Color(c + other.c, m + other.m, y + other.y);
    }
    
    Color operator-(const Color& other) const {
        return Color(c - other.c, m - other.m, y - other.y);
    }
    
    Color operator*(double scalar) const {
        return Color(c * scalar, m * scalar, y * scalar);
    }
    
    Color operator/(double scalar) const {
        return Color(c / scalar, m / scalar, y / scalar);
    }
    
    double distanceSquared(const Color& other) const {
        double dc = c - other.c;
        double dm = m - other.m;
        double dy = y - other.y;
        return dc*dc + dm*dm + dy*dy;
    }
    
    double distance(const Color& other) const {
        return sqrt(distanceSquared(other));
    }
};

vector<Color> tubes;
vector<Color> targets;

// デバッグ用カウンタ
long long findClosestMix_calls = 0;
long long total_distance_calculations = 0;

// 事前計算済み混色データ
struct PrecomputedMix {
    Color color;
    vector<int> recipe;  // tubes[i]をrecipe[i]グラム使用
    
    PrecomputedMix() : recipe(0) {}
    PrecomputedMix(Color c, vector<int> r) : color(c), recipe(r) {}
};

// KD-Treeノード
struct KDNode {
    PrecomputedMix* mix;
    int axis;  // 0:C, 1:M, 2:Y
    KDNode* left;
    KDNode* right;
    
    KDNode(PrecomputedMix* m, int a) : mix(m), axis(a), left(nullptr), right(nullptr) {}
};

// KD-Tree最近傍探索クラス
class KDTree {
private:
    KDNode* root;
    
    // 指定軸での座標値を取得
    double getCoord(const Color& color, int axis) {
        if (axis == 0) return color.c;
        if (axis == 1) return color.m;
        return color.y;
    }
    
    // KD-Treeを構築
    KDNode* build(vector<PrecomputedMix*>& mixes, int depth) {
        if (mixes.empty()) return nullptr;
        
        int axis = depth % 3;
        
        // 指定軸でソート
        sort(mixes.begin(), mixes.end(), [&](PrecomputedMix* a, PrecomputedMix* b) {
            return getCoord(a->color, axis) < getCoord(b->color, axis);
        });
        
        // 中央値を選択
        int median = mixes.size() / 2;
        KDNode* node = new KDNode(mixes[median], axis);
        
        // 左右に分割して再帰構築
        vector<PrecomputedMix*> left_mixes(mixes.begin(), mixes.begin() + median);
        vector<PrecomputedMix*> right_mixes(mixes.begin() + median + 1, mixes.end());
        
        node->left = build(left_mixes, depth + 1);
        node->right = build(right_mixes, depth + 1);
        
        return node;
    }
    
    // 最近傍探索の再帰関数
    void searchNearest(KDNode* node, const Color& target, PrecomputedMix*& best, double& best_dist_sq) {
        if (node == nullptr) return;
        
        total_distance_calculations++;
        
        // 現在のノードとの距離を計算
        double dist_sq = target.distanceSquared(node->mix->color);
        if (dist_sq < best_dist_sq) {
            best_dist_sq = dist_sq;
            best = node->mix;
        }
        
        // 探索する子ノードを決定
        double target_coord = getCoord(target, node->axis);
        double node_coord = getCoord(node->mix->color, node->axis);
        
        KDNode* first_child = (target_coord < node_coord) ? node->left : node->right;
        KDNode* second_child = (target_coord < node_coord) ? node->right : node->left;
        
        // まず近い方の子ノードを探索
        searchNearest(first_child, target, best, best_dist_sq);
        
        // 軸に垂直な距離の二乗
        double axis_dist_sq = (target_coord - node_coord) * (target_coord - node_coord);
        
        // もう一方の子ノードも探索が必要かチェック
        if (axis_dist_sq < best_dist_sq) {
            searchNearest(second_child, target, best, best_dist_sq);
        }
    }
    
public:
    KDTree() : root(nullptr) {}
    
    // KD-Treeを構築
    void build(vector<PrecomputedMix>& mixes) {
        vector<PrecomputedMix*> mix_ptrs;
        for (auto& mix : mixes) {
            mix_ptrs.push_back(&mix);
        }
        root = build(mix_ptrs, 0);
    }
    
    // 最近傍探索
    PrecomputedMix* findNearest(const Color& target) {
        if (root == nullptr) return nullptr;
        
        PrecomputedMix* best = nullptr;
        double best_dist_sq = 1e18;
        
        searchNearest(root, target, best, best_dist_sq);
        return best;
    }
};

// グラム数別の事前計算済み混色テーブル
vector<vector<PrecomputedMix>> precomputed_colors;  // precomputed_colors[grams] = 該当グラム数の全混色
vector<KDTree> kdtrees;  // グラム数別のKD-Tree

// 数学的に重複組み合わせを生成する関数（最適化版 - std::function削除）
void generate_multiset_combinations(int total_grams, int num_tubes, vector<vector<int>>& recipes) {
    // total_gramsをnum_tubes個の非負整数に分割する全ての方法を生成
    // 理論組み合わせ数: C(total_grams + num_tubes - 1, num_tubes - 1)
    
    // 予想される組み合わせ数を事前計算して容量を予約
    size_t expected_size = 1;
    for (int i = 0; i < min(num_tubes - 1, total_grams); i++) {
        expected_size = expected_size * (total_grams + num_tubes - 1 - i) / (i + 1);
    }
    recipes.reserve(expected_size);
    
    vector<int> current_recipe(num_tubes, 0);
    
    // 再帰関数をクラス内で定義（std::function削除）
    class Generator {
    public:
        vector<vector<int>>& recipes;
        vector<int>& current_recipe;
        int num_tubes;
        
        Generator(vector<vector<int>>& r, vector<int>& cr, int nt) 
            : recipes(r), current_recipe(cr), num_tubes(nt) {}
        
        void generate(int tube_idx, int remaining_grams) {
            if (tube_idx == num_tubes - 1) {
                // 最後のチューブに残りのグラムを全て割り当て
                current_recipe[tube_idx] = remaining_grams;
                recipes.push_back(current_recipe);
                return;
            }
            
            // 現在のチューブに0～remaining_gramsを割り当て
            for (int use_grams = 0; use_grams <= remaining_grams; use_grams++) {
                current_recipe[tube_idx] = use_grams;
                generate(tube_idx + 1, remaining_grams - use_grams);
            }
        }
    };
    
    Generator gen(recipes, current_recipe, num_tubes);
    gen.generate(0, total_grams);
}

// 時間制限付き事前計算: 数学的組み合わせ生成による最適化版
bool precomputeAllMixtures() {
    auto start_time = chrono::high_resolution_clock::now();
    
    precomputed_colors.resize(MAX_WELL_CAPACITY + 1);
    kdtrees.resize(MAX_WELL_CAPACITY + 1);
    
    // 各グラム数に対して数学的に組み合わせを生成
    for (int total_grams = 1; total_grams <= MAX_WELL_CAPACITY; total_grams++) {
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(current_time - start_time);
        
        if (elapsed_ms.count() > MAX_PRECOMPUTE_TIME_MS) {
            actual_max_precompute_grams = total_grams - 1;
            cerr << "Precomputation stopped at grams=" << actual_max_precompute_grams 
                 << " due to time limit (" << elapsed_ms.count() << "ms)" << endl;
            return false;
        }
        
        vector<vector<int>> recipes;
        
        // 数学的組み合わせ生成を使用（従来の指数的再帰を置換）
        generate_multiset_combinations(total_grams, K, recipes);
        
        cerr << "Generated " << recipes.size() << " recipes for " << total_grams << " grams" << endl;
        
        // 各レシピから色を計算
        for (const auto& r : recipes) {
            Color mixed_color;
            int total = 0;
            
            for (int i = 0; i < K; i++) {
                if (r[i] > 0) {
                    mixed_color = mixed_color + tubes[i] * r[i];
                    total += r[i];
                }
            }
            
            if (total > 0) {
                mixed_color = mixed_color / total;
                precomputed_colors[total_grams].emplace_back(mixed_color, r);
            }
        }
        
        // KD-Treeを構築
        if (!precomputed_colors[total_grams].empty()) {
            kdtrees[total_grams].build(precomputed_colors[total_grams]);
        }
        
        actual_max_precompute_grams = total_grams;
    }
    
    return true;
}

// 理想の追加色ベクトルを計算
Color computeIdealAdditionColor(const Color& current_color, int current_grams, const Color& target_color, int add_grams) {
    if (current_grams == 0) {
        return target_color;  // 空のウェルの場合、目標色をそのまま
    }
    
    int total_grams = current_grams + add_grams;
    // target = (current * current_grams + ideal_add * add_grams) / total_grams
    // 解く: ideal_add = (target * total_grams - current * current_grams) / add_grams
    return (target_color * total_grams - current_color * current_grams) / add_grams;
}

// 事前計算済み色の中から最も近いものを検索（KD-Tree使用）
const PrecomputedMix* findClosestMix(int grams, const Color& target_color) {
    findClosestMix_calls++;
    
    // 配列外アクセス防止
    if (grams <= 0 || grams > actual_max_precompute_grams) {
        return nullptr;
    }
    
    return kdtrees[grams].findNearest(target_color);
}

// 50個のウェル管理（10x5分割）
struct Well {
    Color currentColor;
    int currentGrams;
    pii position;
    
    Well() : currentGrams(0), position({-1, -1}) {}
    Well(pii pos) : currentGrams(0), position(pos) {}
    
    bool isEmpty() const { return currentGrams == 0; }
    bool isAvailable() const { return position.first >= 0; }
    
    // 絵の具を追加
    void addPaint(int tubeId, int grams) {
        Color newTotal = currentColor * currentGrams + tubes[tubeId] * grams;
        currentGrams += grams;
        currentColor = newTotal / currentGrams;
    }
    
    // 1グラム消費
    void consume() {
        if (currentGrams > 0) {
            currentGrams--;
        }
    }
    
    // 指定量廃棄
    void dispose(int grams) {
        currentGrams = max(0, currentGrams - grams);
    }
};

// パレット管理クラス（10x5分割版）
class AdvancedPalette {
public:
    vector<Well> wells;
    int total_turns_used = 0;  // 使用済みターン数の追跡
    
    AdvancedPalette() {
        wells.resize(GRID_ROWS * GRID_COLS);
        // 10x5グリッドに配置（各ウェルの容量 = MAX_WELL_CAPACITY）
        rep(i, GRID_ROWS * GRID_COLS) {
            int row = i / GRID_COLS;
            int col = i % GRID_COLS;
            int cell_height = N / GRID_ROWS;
            int cell_width = N / GRID_COLS;
            wells[i] = Well({row * cell_height + 1, col * cell_width + 1});
        }
    }
    
    // パレット設定を出力（GRID_COLS x GRID_ROWS分割）
    void printPalette() {
        int cell_width = N / GRID_COLS;
        int cell_height = N / GRID_ROWS;
        
        // 縦の壁 (N行, N-1列)
        rep(i, N) {
            rep(j, N-1) {
                cout << ((j % cell_width == cell_width - 1) ? 1 : 0);
                if (j < N-2) cout << " ";
            }
            cout << "\n";
        }
        
        // 横の壁 (N-1行, N列)
        rep(i, N-1) {
            rep(j, N) {
                cout << ((i % cell_height == cell_height - 1) ? 1 : 0);
                if (j < N-1) cout << " ";
            }
            cout << "\n";
        }
    }
      // 指定されたターゲット色に対して最適な行動を計算（ターン数ペナルティ対応）
    struct Action {
        int wellId;
    static constexpr int K_MAX = 8;              // 絵の具の種類
    array<pair<int,int>,K_MAX> additions;
    uint8_t addCnt = 0;
        int disposalAmount; // 事前廃棄量
        double score; // D*(操作回数-1) + 10000*誤差 + turn_penalty_weight*ターン数
        Color resultColor;
        int turnCount; // このアクションで消費するターン数
        
        Action() : wellId(-1), disposalAmount(0), score(1e9), turnCount(0) {}
        
    int totalAddedGrams() const {
        int s = 0; for (int i = 0; i < addCnt; ++i) s += additions[i].second;
        return s;
    }
    void calculateTurnCount() {
        // 1 (consume) + addCnt + (disposal>0)
        turnCount = 1 + addCnt + (disposalAmount > 0);
    }
        
        // デバッグ出力
        void printDebugInfo(const Color& target) const {
            cerr << "Action - WellID:" << wellId << " Score:" << score << " Turns:" << turnCount;
            cerr << " Result:(" << resultColor.c << "," << resultColor.m << "," << resultColor.y << ")";
            cerr << " Target:(" << target.c << "," << target.m << "," << target.y << ")";
            cerr << " Distance:" << sqrt(target.distanceSquared(resultColor));
            if (disposalAmount > 0) {
                cerr << " Dispose:" << disposalAmount;
            }
            if (!additions.empty()) {
                cerr << " Additions:";
                for (auto [tubeId, grams] : additions) {
                    cerr << " (" << tubeId << "," << grams << ")";
                }
            }
            cerr << endl;
        }
    };
	
	// 上位X個の候補を取得する関数
vector<Action>
findTopActions(const Color& target,
               int num_candidates = 10,
               double turn_penalty_weight = 0.0,
               int remaining_targets = 0)
{
    /* ---------- 0. 型定義 & ヒープ用ユーティリティ ---------- */
    struct Entry {
        double score2;     // 距離は二乗で評価
        Action action;
        bool operator<(const Entry& rhs) const
        {   // priority_queue はデフォルトで「大きい方」が top
            return score2 < rhs.score2;
        }
    };
    std::priority_queue<Entry> pq;           // 上位 num_candidates だけ保持

    auto tryPush = [&](Action&& a, double dist2) {
        double scr2 = 10000.0 * dist2 +
                      turn_penalty_weight * a.turnCount +
                      D * (a.disposalAmount + a.totalAddedGrams());

        if (pq.size() < static_cast<size_t>(num_candidates)) {
            pq.push({scr2, std::move(a)});
        } else if (scr2 < pq.top().score2) { // より良ければ置換
            pq.pop();
            pq.push({scr2, std::move(a)});
        }
    };

    /* ---------- 1. 残ターン許容幅の計算 ----------------------- */
    const int turns_left       = T - total_turns_used;
    const int max_turns_per_tg = (remaining_targets > 0)
        ? max(1, turns_left / remaining_targets)
        : turns_left;

    /* ---------- 2. 各ウェルでアクション列挙 ------------------- */
    bool empty_well_done = false;

    for (int wid = 0; wid < GRID_ROWS * GRID_COLS; ++wid) {
        Well& w = wells[wid];

        /* ---- 2-A. そのまま 1 g 消費 -------------------------- */
        if (!w.isEmpty()) {
            Action a;
            a.wellId      = wid;
            a.resultColor = w.currentColor;
            a.turnCount   = 1;
            double d2     = target.distanceSquared(a.resultColor);
            tryPush(std::move(a), d2);
        }

        /* ---- 2-B. 追加のみ ----------------------------------- */
        if (w.isEmpty() && empty_well_done) {
            // 空ウェルは 1 度だけ考慮
        } else {
            int cap = min(MAX_WELL_CAPACITY - w.currentGrams,
                           actual_max_precompute_grams);
            for (int addg = 1; addg <= cap; ++addg) {
                if (w.currentGrams + addg > MAX_WELL_CAPACITY) break;

                Color ideal = computeIdealAdditionColor(
                                  w.currentColor, w.currentGrams,
                                  target, addg);
                const PrecomputedMix* mix = findClosestMix(addg, ideal);
                if (!mix) continue;

                Color res;
                if (w.currentGrams == 0) {
                    res = mix->color;
                } else {
                    Color tot = w.currentColor * w.currentGrams
                              + mix->color   * addg;
                    res = tot / (w.currentGrams + addg);
                }

                Action a;
                a.wellId      = wid;
                a.resultColor = res;
                a.disposalAmount = 0;

                a.addCnt = 0;
                for (int i = 0; i < K; ++i)
                    if (mix->recipe[i]) {
                        a.additions[a.addCnt++] = {i, mix->recipe[i]};
                    }
                a.calculateTurnCount();

                if (a.turnCount <= max_turns_per_tg) {
                    double d2 = target.distanceSquared(res);
                    tryPush(std::move(a), d2);
                }
            }
            if (w.isEmpty()) empty_well_done = true;
        }

        /* ---- 2-C. 廃棄 → 追加 -------------------------------- */
        if (!w.isEmpty()) {
            for (int dump = 1; dump <= w.currentGrams; ++dump) {
                int grams_after_dump = w.currentGrams - dump;
                int cap = min(MAX_WELL_CAPACITY - grams_after_dump,
                               actual_max_precompute_grams);
                for (int addg = 1; addg <= cap; ++addg) {
                    if (grams_after_dump + addg > MAX_WELL_CAPACITY) break;

                    Color ideal = computeIdealAdditionColor(
                                      w.currentColor, grams_after_dump,
                                      target, addg);
                    const PrecomputedMix* mix = findClosestMix(addg, ideal);
                    if (!mix) continue;

                    Color res;
                    if (grams_after_dump == 0) {
                        res = mix->color;
                    } else {
                        Color tot = w.currentColor * grams_after_dump
                                  + mix->color   * addg;
                        res = tot / (grams_after_dump + addg);
                    }

                    Action a;
                    a.wellId         = wid;
                    a.resultColor    = res;
                    a.disposalAmount = dump;

                    a.addCnt = 0;
                    for (int i = 0; i < K; ++i)
                        if (mix->recipe[i]) {
                            a.additions[a.addCnt++] = {i, mix->recipe[i]};
                        }
                    a.calculateTurnCount();

                    if (a.turnCount <= max_turns_per_tg) {
                        double d2 = target.distanceSquared(res);
                        tryPush(std::move(a), d2);
                    }
                }
            }
        }
    }

    /* ---------- 3. ヒープ → ベクタ変換 & 正確な score 計算 ---- */
    vector<Action> res;
    res.reserve(pq.size());
    while (!pq.empty()) {
        auto en = pq.top(); pq.pop();
        // score2 は dist² で作っているので最終精密スコアへ更新
        double dist = sqrt(target.distanceSquared(en.action.resultColor));
        en.action.score =
            D * (en.action.disposalAmount + en.action.totalAddedGrams()) +
            10000.0 * dist +
            turn_penalty_weight * en.action.turnCount;

        res.emplace_back(std::move(en.action));
    }
    sort(res.begin(), res.end(),
         [](const Action& a, const Action& b) { return a.score < b.score; });

    return res;
}
    
    // 従来のfindBestAction関数（互換性のため）
    Action findBestAction(const Color& target, double turn_penalty_weight = 0.0, int remaining_targets = 0) {
        vector<Action> topActions = findTopActions(target, 1, turn_penalty_weight, remaining_targets);
        if (topActions.empty()) {
            return Action(); // デフォルトアクション
        }
        return topActions[0];
    }
    
    // アクションを実行
    void executeAction(const Action& action) {
        if (action.wellId < 0) return;
        
        Well& well = wells[action.wellId];
        
        // 事前廃棄
        if (action.disposalAmount > 0) {
            rep(i, action.disposalAmount) {
                cout << "3 " << well.position.first << " " << well.position.second << "\n";
                total_turns_used++;
            }
            well.dispose(action.disposalAmount);
        }
        
        // 絵の具を追加
        for (auto [tubeId, grams] : action.additions) {
            rep(g, grams) {
                cout << "1 " << well.position.first << " " << well.position.second 
                     << " " << tubeId << "\n";
                total_turns_used++;
            }
            well.addPaint(tubeId, grams);
        }
        
        // 1グラム消費
        cout << "2 " << well.position.first << " " << well.position.second << "\n";
        well.consume();
        total_turns_used++;
    }
    
    // プレイアウト用のパレット状態をコピー
    AdvancedPalette copyPalette() const {
        AdvancedPalette copy;
        copy.wells = this->wells;
        copy.total_turns_used = this->total_turns_used;
        return copy;
    }
    
    // アクションを実行（出力なし、プレイアウト用）
    void executeActionSilent(const Action& action) {
        if (action.wellId < 0) return;
        
        Well& well = wells[action.wellId];
        
        // 事前廃棄
        if (action.disposalAmount > 0) {
            total_turns_used += action.disposalAmount;
            well.dispose(action.disposalAmount);
        }
        
        // 絵の具を追加
        for (auto [tubeId, grams] : action.additions) {
            total_turns_used += grams;
            well.addPaint(tubeId, grams);
        }
        
        // 1グラム消費
        well.consume();
        total_turns_used++;
    }
      // プレイアウト：指定アクションを実行後、残りターゲットに対して最善手を続けた場合の総合スコアを計算
    double evaluateWithPlayout(const Action& firstAction, const vector<Color>& remainingTargets, int maxDepth = 8) {
        // パレット状態をコピー
        AdvancedPalette playoutPalette = copyPalette();
        
        // 最初のアクションを実行
        playoutPalette.executeActionSilent(firstAction);
        
        double totalScore = 0.0;
        double errorSum = 0.0;
        int totalOperations = firstAction.turnCount - 1; // 消費分を除く
        
        // 最初のターゲットの誤差を追加
        double firstError = sqrt(firstAction.resultColor.distanceSquared(remainingTargets[0]));
        errorSum += firstError;
        
        // 残りのターゲットに対してプレイアウト（効率化）
        int remainingTurns = T - playoutPalette.total_turns_used;
        int remainingTargetCount = remainingTargets.size() - 1;
        int processedTargets = min({maxDepth, remainingTargetCount, remainingTurns});
        
        for (int i = 1; i <= processedTargets; i++) {
            if (playoutPalette.total_turns_used >= T) break;
            
            int remaining = remainingTargets.size() - i;
            Action bestAction = playoutPalette.findBestAction(remainingTargets[i], 0.0, remaining);
            
            if (bestAction.wellId >= 0 && playoutPalette.total_turns_used + bestAction.turnCount <= T) {
                playoutPalette.executeActionSilent(bestAction);
                
                double error = sqrt(bestAction.resultColor.distanceSquared(remainingTargets[i]));
                errorSum += error;
                totalOperations += (bestAction.turnCount - 1); // 消費分を除く
            } else {
                // アクションが見つからない、またはターン数超過の場合、大きなペナルティ
                errorSum += 1.0;
                break; // プレイアウト中止
            }
        }
        
        // 未処理のターゲットに対するペナルティ
        int unprocessedTargets = remainingTargetCount - processedTargets;
        if (unprocessedTargets > 0) {
            errorSum += unprocessedTargets * 0.5; // 未処理ペナルティ
        }
        
        // スコア計算：1 + D*(V-H) + round(10^4 * E)
        // V = totalOperations + remainingTargets.size() (消費ターン数)
        // H = remainingTargets.size()
        // なので D*(V-H) = D*totalOperations
        totalScore = 1.0 + D * totalOperations + 10000.0 * errorSum;
        
        return totalScore;
    }
};

// 簡素化されたメインソルバー
class TurnConstrainedSolver {
public:
    void solve() {
        auto total_start = chrono::high_resolution_clock::now();
        
        // 入力読み込み
        int _N, _H;
        cin >> _N >> K >> _H >> T >> D;
        
        tubes.resize(K);
        rep(i, K) {
            cin >> tubes[i].c >> tubes[i].m >> tubes[i].y;
        }
        
        targets.resize(_H);
        rep(i, _H) {
            cin >> targets[i].c >> targets[i].m >> targets[i].y;
        }
        
        // 事前計算を実行
        auto start_precompute = chrono::high_resolution_clock::now();
        bool precompute_completed = precomputeAllMixtures();
        auto end_precompute = chrono::high_resolution_clock::now();
        
        auto precompute_duration = chrono::duration_cast<chrono::milliseconds>(end_precompute - start_precompute);
        cerr << "Precomputation time: " << precompute_duration.count() << " ms" << endl;
        
        // 前計算結果の統計を出力
        int total_mixes = 0;
        for (int g = 1; g <= actual_max_precompute_grams; g++) {
            total_mixes += precomputed_colors[g].size();
        }
        cerr << "Total precomputed mixes: " << total_mixes << endl;
        
        // ターン数制約の詳細分析
        int estimated_min_turns = targets.size();  // 各色最低1ターン
        double turn_constraint_ratio = (double)estimated_min_turns / T;
        double turn_penalty_weight = 0.0;
        
        cerr << "Turn constraint analysis:" << endl;
        cerr << "  Total targets: " << targets.size() << endl;
        cerr << "  Total turns available: " << T << endl;
        cerr << "  Estimated min turns: " << estimated_min_turns << endl;
        cerr << "  Constraint ratio: " << turn_constraint_ratio << endl;
        
        if (turn_constraint_ratio > 0.3) {
            // ターン数制約が厳しい場合、ペナルティを適用
            turn_penalty_weight = D * min(10.0, turn_constraint_ratio * 20.0);
            cerr << "  Severe turn constraint detected!" << endl;
            cerr << "  Applied penalty weight: " << turn_penalty_weight << endl;
        } else if (turn_constraint_ratio > 0.2) {
            // 中程度のターン数制約
            turn_penalty_weight = D * 2.0;
            cerr << "  Moderate turn constraint detected." << endl;
            cerr << "  Applied penalty weight: " << turn_penalty_weight << endl;
        } else {
            cerr << "  Turn constraint is loose." << endl;
        }          // メイン処理開始（モンテカルロプレイアウト版）
        auto start_main = chrono::high_resolution_clock::now();
        
        AdvancedPalette palette;
        palette.printPalette();
        
        // モンテカルロプレイアウトを使った候補選択
        for (int targetIndex = 0; targetIndex < targets.size(); targetIndex++) {
            if (palette.total_turns_used >= T) break;
            
            Color currentTarget = targets[targetIndex];
            vector<Color> remainingTargets(targets.begin() + targetIndex, targets.end());
            
            cerr << "\n=== Target " << (targetIndex + 1) << "/" << targets.size() << " ===" << endl;
            cerr << "Target color: (" << currentTarget.c << ", " << currentTarget.m << ", " << currentTarget.y << ")" << endl;
              // 上位候補を取得（動的調整）
            int remainingTargetsCount = targets.size() - targetIndex;
            int numCandidates;
            
            if (remainingTargetsCount > 50) {
                numCandidates = 5;  // 多くのターゲットが残っている場合は高速化
            } else if (remainingTargetsCount > 20) {
                numCandidates = 5;  // 中程度の場合
            } else {
                numCandidates = min(8, remainingTargetsCount);  // 少ない場合は詳細評価
            }
            
            vector<AdvancedPalette::Action> topActions = palette.findTopActions(
                currentTarget, numCandidates, turn_penalty_weight, remainingTargets.size()
            );
            
            if (topActions.empty()) {
                cerr << "No valid actions found!" << endl;
                break;
            }
            
            // プレイアウトによる評価
            double bestPlayoutScore = 1e9;
            int bestActionIndex = 0;
            
            cerr << "Evaluating " << topActions.size() << " candidates with playout..." << endl;
            
            for (int i = 0; i < topActions.size(); i++) {
                double playoutScore = palette.evaluateWithPlayout(topActions[i], remainingTargets);
                
                cerr << "Candidate " << (i+1) << ": Score=" << topActions[i].score 
                     << ", Playout=" << playoutScore << ", Turns=" << topActions[i].turnCount << endl;
                
                if (playoutScore < bestPlayoutScore) {
                    bestPlayoutScore = playoutScore;
                    bestActionIndex = i;
                }
            }
            
            // 最良のアクションを実行
            AdvancedPalette::Action bestAction = topActions[bestActionIndex];
            cerr << "Selected candidate " << (bestActionIndex + 1) << " with playout score " << bestPlayoutScore << endl;
            
            palette.executeAction(bestAction);
        }
        
        auto end_main = chrono::high_resolution_clock::now();
        auto main_duration = chrono::duration_cast<chrono::milliseconds>(end_main - start_main);
        
        auto total_end = chrono::high_resolution_clock::now();
        auto total_duration = chrono::duration_cast<chrono::milliseconds>(total_end - total_start);
        
        cerr << "Main processing time: " << main_duration.count() << " ms" << endl;
        cerr << "Total execution time: " << total_duration.count() << " ms" << endl;
        cerr << "Total turns used: " << palette.total_turns_used << "/" << T << endl;
        cerr << "Calls per target: " << (double)findClosestMix_calls / targets.size() << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    TurnConstrainedSolver solver;
    solver.solve();
    fflush(stdout);
	_Exit(0);
    return 0;
}
