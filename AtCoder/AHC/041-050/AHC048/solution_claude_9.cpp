#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <chrono>
using namespace std;

using pii = pair<int, int>;
#define rep(i, n) for(int i = 0; i < (int)(n); ++i)

const int N = 20, H = 1000;
const int GRID_ROWS = 5, GRID_COLS = 10;  // パレット分割数
const int MAX_WELL_CAPACITY = 8;  // 各ウェルの最大容量（固定値）
const int MAX_PRECOMPUTE_TIME_MS = 600;  // 前処理制限時間をさらに短縮（0.6秒）
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

// 時間制限付き事前計算: 全ての可能な混色を列挙
bool precomputeAllMixtures() {
    auto start_time = chrono::high_resolution_clock::now();
    
    precomputed_colors.resize(MAX_WELL_CAPACITY + 1);
    kdtrees.resize(MAX_WELL_CAPACITY + 1);
    
    // DPで各グラム数の全組み合わせを生成（重複組み合わせ対応）
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
        
        // total_gramsを実現する全ての重複組み合わせを生成
        function<void(int, vector<int>&, int)> generate_recipes = [&](int tube_idx, vector<int>& current_recipe, int remaining_grams) {
            if (tube_idx == K) {
                if (remaining_grams == 0) {
                    recipes.push_back(current_recipe);
                }
                return;
            }
            
            // tubes[tube_idx]を0～remaining_gramsグラム使用（重複使用可能）
            for (int use_grams = 0; use_grams <= remaining_grams; use_grams++) {
                current_recipe[tube_idx] = use_grams;
                generate_recipes(tube_idx + 1, current_recipe, remaining_grams - use_grams);
            }
        };
        
        vector<int> recipe(K, 0);
        generate_recipes(0, recipe, total_grams);
        
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
        vector<pii> additions; // {tubeId, grams}
        int disposalAmount; // 事前廃棄量
        double score; // D*(操作回数-1) + 10000*誤差 + turn_penalty_weight*ターン数
        Color resultColor;
        int turnCount; // このアクションで消費するターン数
        
        Action() : wellId(-1), disposalAmount(0), score(1e9), turnCount(0) {}
        
        // ターン数を計算
        void calculateTurnCount() {
            turnCount = disposalAmount; // 廃棄操作
            for (auto [tubeId, grams] : additions) {
                turnCount += grams; // 追加操作
            }
            turnCount += 1; // 消費操作
        }
    };
    
    Action findBestAction(const Color& target, double turn_penalty_weight = 0.0, int remaining_targets = 0) {
        Action bestAction;
        
        // 残りターン数制約をチェック
        int remaining_turns = T - total_turns_used;
        int max_allowed_turns_per_target = remaining_targets > 0 ? 
            max(1, remaining_turns / remaining_targets) : remaining_turns;
        
        rep(wellId, GRID_ROWS * GRID_COLS) {
            Well& well = wells[wellId];
            
            // 1. 現在の色をそのまま使用（廃棄なし、追加なし）
            if (!well.isEmpty()) {
                Action action;
                action.wellId = wellId;
                action.resultColor = well.currentColor;
                action.turnCount = 1; // 消費のみ
                
                // ターン数制約チェック
                if (action.turnCount <= max_allowed_turns_per_target) {
                    action.score = 10000.0 * sqrt(target.distanceSquared(well.currentColor)) 
                                 + turn_penalty_weight * action.turnCount;
                    
                    if (action.score < bestAction.score) {
                        bestAction = action;
                    }
                }
            }
            
            // 2. 新しいアルゴリズム: (ウェル, 追加グラム数)でループ
            // ターン数制約が厳しい場合は追加グラム数を制限
            int max_add_grams = std::min({MAX_WELL_CAPACITY, actual_max_precompute_grams, max_allowed_turns_per_target - 1});
            
            for (int add_grams = 1; add_grams <= max_add_grams; add_grams++) {
                // 現在のウェル容量制限チェック
                if (well.currentGrams + add_grams > MAX_WELL_CAPACITY) continue;
                
                // 理想の追加色ベクトルを計算
                Color ideal_add_color = computeIdealAdditionColor(
                    well.currentColor, well.currentGrams, target, add_grams
                );
                
                // 事前計算済みの色から最適なものを検索
                const PrecomputedMix* best_mix = findClosestMix(
                    add_grams, ideal_add_color
                );
                
                if (best_mix != nullptr) {
                    // 実際の結果色を計算
                    Color result_color;
                    if (well.currentGrams == 0) {
                        result_color = best_mix->color;
                    } else {
                        Color total_color = well.currentColor * well.currentGrams + best_mix->color * add_grams;
                        result_color = total_color / (well.currentGrams + add_grams);
                    }
                    
                    // アクションを構築
                    Action action;
                    action.wellId = wellId;
                    action.resultColor = result_color;
                    
                    // レシピをadditionsに変換
                    for (int i = 0; i < K; i++) {
                        if (best_mix->recipe[i] > 0) {
                            action.additions.push_back({i, best_mix->recipe[i]});
                        }
                    }
                    
                    action.calculateTurnCount();
                    
                    // ターン数制約チェック
                    if (action.turnCount <= max_allowed_turns_per_target) {
                        action.score = D * add_grams + 10000.0 * sqrt(target.distanceSquared(result_color))
                                     + turn_penalty_weight * action.turnCount;
                        
                        if (action.score < bestAction.score) {
                            bestAction = action;
                        }
                    }
                }
            }
            
            // 3. 廃棄戦略: 制約が緩い場合のみ実行
            if (!well.isEmpty() && turn_penalty_weight < D * 5.0) {
                for (int dispose_grams = 1; dispose_grams <= min(well.currentGrams, max_allowed_turns_per_target / 2); dispose_grams++) {
                    int remaining_grams = well.currentGrams - dispose_grams;
                    
                    int max_add_after_dispose = min({MAX_WELL_CAPACITY - remaining_grams, 
                                                   actual_max_precompute_grams, 
                                                   max_allowed_turns_per_target - dispose_grams - 1});
                    
                    for (int add_grams = 1; add_grams <= max_add_after_dispose; add_grams++) {
                        // 廃棄後の理想の追加色ベクトルを計算
                        Color ideal_add_color = computeIdealAdditionColor(
                            well.currentColor, remaining_grams, target, add_grams
                        );
                        
                        const PrecomputedMix* best_mix = findClosestMix(
                            add_grams, ideal_add_color
                        );
                        
                        if (best_mix != nullptr) {
                            Color result_color;
                            if (remaining_grams == 0) {
                                result_color = best_mix->color;
                            } else {
                                Color total_color = well.currentColor * remaining_grams + best_mix->color * add_grams;
                                result_color = total_color / (remaining_grams + add_grams);
                            }
                            
                            Action action;
                            action.wellId = wellId;
                            action.disposalAmount = dispose_grams;
                            action.resultColor = result_color;
                            
                            for (int i = 0; i < K; i++) {
                                if (best_mix->recipe[i] > 0) {
                                    action.additions.push_back({i, best_mix->recipe[i]});
                                }
                            }
                            
                            action.calculateTurnCount();
                            
                            // ターン数制約チェック
                            if (action.turnCount <= max_allowed_turns_per_target) {
                                action.score = D * (dispose_grams + add_grams) + 10000.0 * sqrt(target.distanceSquared(result_color))
                                             + turn_penalty_weight * action.turnCount;
                                
                                if (action.score < bestAction.score) {
                                    bestAction = action;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        return bestAction;
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
        }
        
        // メイン処理開始
        auto start_main = chrono::high_resolution_clock::now();
        
        AdvancedPalette palette;
        palette.printPalette();
        
        // 各ターゲット色に対して最適なアクションを実行
        rep(i, targets.size()) {
            int remaining_targets = targets.size() - i;
            AdvancedPalette::Action bestAction = palette.findBestAction(targets[i], turn_penalty_weight, remaining_targets);
            palette.executeAction(bestAction);
            
            // ターン数制限チェック
            if (palette.total_turns_used >= T) {
                cerr << "Turn limit exceeded at target " << i << "/" << targets.size() << endl;
                break;
            }
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
    
    return 0;
}
