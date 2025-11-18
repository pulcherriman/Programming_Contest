/**
* C++23 Template @ AtCoder
* AHC048 Solution - Advanced Version
* 中間色再利用とクラスタリング最適化
*/

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
// #undef _DEBUG
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vp=vector<pii>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define rep(i,n) for(int i=0;i<(int)(n);++i)
#define rrep(i,n) for(int i=(int)(n)-1;i>=0;--i)
#define sz(a) ((int)(a).size())

constexpr ll LINF=1ll<<60;
constexpr int INF=1000000;
constexpr double EPS=1e-9;

// 問題定数
const int N=20, H=1000;
int K, T, D;

// 色を表現する構造体
struct Color {
    double c, m, y;
    Color() : c(0), m(0), y(0) {}
    Color(double c_, double m_, double y_) : c(c_), m(m_), y(y_) {}
    
    Color operator+(const Color& other) const {
        return Color(c + other.c, m + other.m, y + other.y);
    }
    
    Color operator*(double scalar) const {
        return Color(c * scalar, m * scalar, y * scalar);
    }
    
    Color operator/(double scalar) const {
        return Color(c / scalar, m / scalar, y / scalar);
    }
    
    // 色の距離（ユークリッド距離の二乗）
    double distanceSquared(const Color& other) const {
        double dc = c - other.c;
        double dm = m - other.m;
        double dy = y - other.y;
        return dc*dc + dm*dm + dy*dy;
    }
    
    // 色の距離（平方根版）
    double distance(const Color& other) const {
        return sqrt(distanceSquared(other));
    }
    
    // 色が有効範囲内かチェック
    bool isValid() const {
        return c >= 0 && c <= 1 && m >= 0 && m <= 1 && y >= 0 && y <= 1;
    }
};

// 混合レシピを表現する構造体
struct MixingRecipe {
    map<int, int> tubes; // tubeId -> grams
    Color expectedColor;
    double expectedError;
    
    MixingRecipe() : expectedError(1e9) {}
    
    void addTube(int tubeId, int grams) {
        if (grams > 0) {
            tubes[tubeId] += grams;
        }
    }
    
    // 総グラム数を計算
    int getTotalGrams() const {
        int total = 0;
        for (auto& [tubeId, grams] : tubes) {
            total += grams;
        }
        return total;
    }
    
    // 正規化（最大10グラムまで）
    void normalize() {
        int total = getTotalGrams();
        if (total > 10) {
            for (auto& [tubeId, grams] : tubes) {
                grams = max(1, (grams * 10) / total);
            }
        }
    }
};

// 中間色情報
struct IntermediateColor {
    Color color;
    MixingRecipe recipe;
    vector<int> usefulFor; // この中間色が有用な目標色のリスト
    double priority; // 優先度
    
    IntermediateColor() : priority(0) {}
    IntermediateColor(const Color& c, const MixingRecipe& r) : color(c), recipe(r), priority(0) {}
};

// 高度な色最適化クラス
class AdvancedColorOptimizer {
private:
    vector<Color> tubes;
    vector<IntermediateColor> intermediates;
    
public:
    AdvancedColorOptimizer(const vector<Color>& tubes_) : tubes(tubes_) {}
    
    // 中間色を分析して生成
    void generateIntermediateColors(const vector<Color>& targets) {
        // 2色混合の中間色を生成
        rep(i, K) rep(j, i+1) {
            for (int w1 = 1; w1 <= 5; w1++) {
                for (int w2 = 1; w2 <= 5; w2++) {
                    if (w1 + w2 > 10) continue;
                    
                    Color mixed = (tubes[i] * w1 + tubes[j] * w2) / (w1 + w2);
                    MixingRecipe recipe;
                    recipe.addTube(i, w1);
                    recipe.addTube(j, w2);
                    recipe.expectedColor = mixed;
                    
                    IntermediateColor intermediate(mixed, recipe);
                    
                    // この中間色がどの目標色に有用かを分析
                    rep(targetIdx, min((int)targets.size(), 100)) { // 最初の100色で分析
                        double error = targets[targetIdx].distanceSquared(mixed);
                        if (error < 0.01) { // 十分近い場合
                            intermediate.usefulFor.push_back(targetIdx);
                        }
                    }
                    
                    // 複数の目標色に有用な場合のみ追加
                    if (intermediate.usefulFor.size() >= 2) {
                        intermediate.priority = intermediate.usefulFor.size();
                        intermediates.push_back(intermediate);
                    }
                }
            }
        }
        
        // 優先度でソート
        sort(intermediates.begin(), intermediates.end(), 
             [](const IntermediateColor& a, const IntermediateColor& b) {
                 return a.priority > b.priority;
             });
        
        // 上位のみ保持（メモリ節約）
        if (intermediates.size() > 50) {
            intermediates.resize(50);
        }
    }
    
    // 高精度最適化
    MixingRecipe findOptimalRecipe(const Color& target) {
        MixingRecipe bestRecipe;
        
        // 中間色からの候補をチェック
        for (const auto& intermediate : intermediates) {
            double error = target.distanceSquared(intermediate.color);
            if (error < bestRecipe.expectedError) {
                bestRecipe = intermediate.recipe;
                bestRecipe.expectedColor = intermediate.color;
                bestRecipe.expectedError = error;
            }
        }
        
        // 従来の最適化も実行
        MixingRecipe directRecipe = findDirectOptimalRecipe(target);
        if (directRecipe.expectedError < bestRecipe.expectedError) {
            bestRecipe = directRecipe;
        }
        
        bestRecipe.normalize();
        return bestRecipe;
    }
    
private:
    // 直接最適化（高精度版）
    MixingRecipe findDirectOptimalRecipe(const Color& target) {
        MixingRecipe bestRecipe;
        
        // 1色最適化
        rep(i, K) {
            double error = target.distanceSquared(tubes[i]);
            if (error < bestRecipe.expectedError) {
                bestRecipe = MixingRecipe();
                bestRecipe.addTube(i, 1);
                bestRecipe.expectedColor = tubes[i];
                bestRecipe.expectedError = error;
            }
        }
        
        // 2色最適化（高精度）
        rep(i, K) rep(j, i+1) {
            for (int w1 = 1; w1 <= 8; w1++) {
                for (int w2 = 1; w2 <= 8; w2++) {
                    if (w1 + w2 > 10) continue;
                    
                    Color mixed = (tubes[i] * w1 + tubes[j] * w2) / (w1 + w2);
                    double error = target.distanceSquared(mixed);
                    
                    if (error < bestRecipe.expectedError) {
                        bestRecipe = MixingRecipe();
                        bestRecipe.addTube(i, w1);
                        bestRecipe.addTube(j, w2);
                        bestRecipe.expectedColor = mixed;
                        bestRecipe.expectedError = error;
                    }
                }
            }
        }
        
        // 3色最適化（必要な場合のみ）
        if (bestRecipe.expectedError > 1e-3) {
            rep(i, K) rep(j, i+1) rep(k, j+1) {
                for (int w1 = 1; w1 <= 4; w1++) {
                    for (int w2 = 1; w2 <= 4; w2++) {
                        for (int w3 = 1; w3 <= 4; w3++) {
                            if (w1 + w2 + w3 > 10) continue;
                            
                            Color mixed = (tubes[i] * w1 + tubes[j] * w2 + tubes[k] * w3) / (w1 + w2 + w3);
                            double error = target.distanceSquared(mixed);
                            
                            if (error < bestRecipe.expectedError) {
                                bestRecipe = MixingRecipe();
                                bestRecipe.addTube(i, w1);
                                bestRecipe.addTube(j, w2);
                                bestRecipe.addTube(k, w3);
                                bestRecipe.expectedColor = mixed;
                                bestRecipe.expectedError = error;
                            }
                        }
                    }
                }
            }
        }
        
        return bestRecipe;
    }
};

// 色クラスタリングクラス
class ColorClusterer {
private:
    vector<Color> targets;
    vector<vector<int>> clusters;
    
public:
    ColorClusterer(const vector<Color>& targets_) : targets(targets_) {}
    
    // K-means的なクラスタリング
    void createClusters(int numClusters = 10) {
        clusters.clear();
        clusters.resize(numClusters);
        
        // 初期クラスタ中心をランダムに選択
        vector<Color> centers;
        for (int i = 0; i < numClusters; i++) {
            centers.push_back(targets[i * targets.size() / numClusters]);
        }
        
        // 各目標色を最も近いクラスタに割り当て
        rep(targetIdx, targets.size()) {
            int bestCluster = 0;
            double bestDistance = 1e9;
            
            rep(clusterIdx, numClusters) {
                double dist = targets[targetIdx].distanceSquared(centers[clusterIdx]);
                if (dist < bestDistance) {
                    bestDistance = dist;
                    bestCluster = clusterIdx;
                }
            }
            
            clusters[bestCluster].push_back(targetIdx);
        }
    }
    
    const vector<vector<int>>& getClusters() const {
        return clusters;
    }
};

// 高度なパレット管理クラス
class AdvancedPalette {
public:
    vvi verticalWalls;
    vvi horizontalWalls;
    
    AdvancedPalette() {
        verticalWalls = vvi(N, vi(N-1, 1));
        horizontalWalls = vvi(N-1, vi(N, 1));
        createOptimalWells();
    }
    
    void printWalls() {
        rep(i, N) {
            rep(j, N-1) {
                cout << verticalWalls[i][j];
                if (j < N-2) cout << " ";
            }
            cout << "\n";
        }
        rep(i, N-1) {
            rep(j, N) {
                cout << horizontalWalls[i][j];
                if (j < N-1) cout << " ";
            }
            cout << "\n";
        }
    }
    
    // メインウェル（常に使用）
    pii getMainWell() {
        return {0, 0}; // 大ウェル1 (50マス)
    }
    
private:
    void createOptimalWells() {
        // メインの大ウェル: (0,0)-(4,9) = 50マス
        rep(i, 5) rep(j, 9) {
            verticalWalls[i][j] = 0;
        }
        rep(i, 4) rep(j, 10) {
            horizontalWalls[i][j] = 0;
        }
    }
};

// メインソルバークラス（高度版）
class AdvancedSolver {
public:
    vector<Color> tubes;
    vector<Color> targets;
    AdvancedPalette palette;
    AdvancedColorOptimizer* optimizer;
    ColorClusterer* clusterer;
    
    void solve() {
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
        
        // 初期化
        optimizer = new AdvancedColorOptimizer(tubes);
        clusterer = new ColorClusterer(targets);
        
        // 中間色分析
        optimizer->generateIntermediateColors(targets);
        
        // クラスタリング（将来の最適化用）
        clusterer->createClusters();
        
        // パレット設定を出力
        palette.printWalls();
        
        // 各色を順番に作成
        rep(targetIdx, _H) {
            createTargetColor(targetIdx);
        }
        
        delete optimizer;
        delete clusterer;
    }
    
private:
    void createTargetColor(int targetIdx) {
        Color target = targets[targetIdx];
        
        // 最適なレシピを計算
        MixingRecipe recipe = optimizer->findOptimalRecipe(target);
        
        // メインウェルを使用
        auto [cellRow, cellCol] = palette.getMainWell();
        
        // レシピに従ってチューブから絵の具を追加
        int totalGrams = 0;
        for (auto& [tubeId, grams] : recipe.tubes) {
            rep(g, grams) {
                cout << "1 " << cellRow << " " << cellCol << " " << tubeId << "\n";
                totalGrams++;
            }
        }
        
        // 1グラム取り出して画伯に渡す
        cout << "2 " << cellRow << " " << cellCol << "\n";
        
        // 残った塗料を廃棄（1回につき1グラムずつ）
        int remainingGrams = totalGrams - 1;
        rep(i, remainingGrams) {
            cout << "3 " << cellRow << " " << cellCol << "\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    AdvancedSolver solver;
    solver.solve();
    
    return 0;
}
