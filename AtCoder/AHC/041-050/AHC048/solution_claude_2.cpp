/**
* C++23 Template @ AtCoder
* AHC048 Solution - Fixed Version
* 容量とパフォーマンス問題を修正
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

// 混合レシピを表現する構造体（改良版）
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
            // 10グラム以下になるように調整
            for (auto& [tubeId, grams] : tubes) {
                grams = max(1, (grams * 10) / total);
            }
        }
    }
};

// 高精度色最適化クラス（効率改良版）
class EfficientColorOptimizer {
private:
    vector<Color> tubes;
    
public:
    EfficientColorOptimizer(const vector<Color>& tubes_) : tubes(tubes_) {}
    
    // 最適化のメインメソッド（効率重視）
    MixingRecipe findOptimalRecipe(const Color& target) {
        MixingRecipe bestRecipe;
        
        // 段階1: 単色での最適解
        MixingRecipe single = optimizeSingleColor(target);
        if (single.expectedError < bestRecipe.expectedError) {
            bestRecipe = single;
        }
        
        // 段階2: 2色混合での最適解（重みを制限）
        MixingRecipe dual = optimizeTwoColorsEfficient(target);
        if (dual.expectedError < bestRecipe.expectedError) {
            bestRecipe = dual;
        }
        
        // 段階3: 3色混合での最適解（軽量版）
        if (bestRecipe.expectedError > 1e-4) { // エラーが大きい場合のみ実行
            MixingRecipe triple = optimizeThreeColorsEfficient(target);
            if (triple.expectedError < bestRecipe.expectedError) {
                bestRecipe = triple;
            }
        }
        
        // 正規化して返す
        bestRecipe.normalize();
        return bestRecipe;
    }
    
private:
    // 1色での最適化
    MixingRecipe optimizeSingleColor(const Color& target) {
        MixingRecipe recipe;
        double bestError = 1e9;
        int bestTube = 0;
        
        rep(i, K) {
            double error = target.distanceSquared(tubes[i]);
            if (error < bestError) {
                bestError = error;
                bestTube = i;
            }
        }
        
        recipe.addTube(bestTube, 1);
        recipe.expectedColor = tubes[bestTube];
        recipe.expectedError = bestError;
        
        return recipe;
    }
    
    // 2色混合での効率的最適化
    MixingRecipe optimizeTwoColorsEfficient(const Color& target) {
        MixingRecipe bestRecipe = optimizeSingleColor(target);
        
        rep(i, K) rep(j, i+1) {
            // 重みを1-5の範囲で試す（効率化）
            for (int w1 = 1; w1 <= 5; w1++) {
                for (int w2 = 1; w2 <= 5; w2++) {
                    if (w1 + w2 > 10) continue; // 容量制限
                    
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
        
        return bestRecipe;
    }
    
    // 3色混合での効率的最適化（軽量版）
    MixingRecipe optimizeThreeColorsEfficient(const Color& target) {
        MixingRecipe bestRecipe = optimizeTwoColorsEfficient(target);
        
        rep(i, K) rep(j, i+1) rep(k, j+1) {
            // 重みを1-3の範囲で試す（計算量削減）
            for (int w1 = 1; w1 <= 3; w1++) {
                for (int w2 = 1; w2 <= 3; w2++) {
                    for (int w3 = 1; w3 <= 3; w3++) {
                        if (w1 + w2 + w3 > 9) continue; // 容量制限
                        
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
        
        return bestRecipe;
    }
};

// 効率的パレット管理クラス
class EfficientPalette {
public:
    vvi verticalWalls;
    vvi horizontalWalls;
    
    EfficientPalette() {
        // 最適化された仕切り配置
        verticalWalls = vvi(N, vi(N-1, 1));
        horizontalWalls = vvi(N-1, vi(N, 1));
        
        // 大きなウェルを作成（容量確保）
        createLargeWells();
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
      // 目標インデックスに応じて適切なウェルを取得
    pii getWellForTarget(int targetIdx) {
        // 毎回ウェルを空にするので、常に大きなウェルの1つを使用
        return {0, 0}; // 大ウェル1 (50マス) を常に使用
    }
    
private:
    void createLargeWells() {
        // 大ウェル1: (0,0)-(4,9) = 50マス
        rep(i, 5) rep(j, 9) {
            verticalWalls[i][j] = 0;
        }
        rep(i, 4) rep(j, 10) {
            horizontalWalls[i][j] = 0;
        }
        
        // 大ウェル2: (0,10)-(4,19) = 50マス
        for (int i = 0; i < 5; i++) {
            for (int j = 10; j < 19; j++) {
                verticalWalls[i][j] = 0;
            }
        }
        rep(i, 4) {
            for (int j = 10; j < 20; j++) {
                horizontalWalls[i][j] = 0;
            }
        }
        
        // 中ウェル1: (5,0)-(9,4) = 25マス
        for (int i = 5; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                verticalWalls[i][j] = 0;
            }
        }
        for (int i = 5; i < 9; i++) {
            for (int j = 0; j < 5; j++) {
                horizontalWalls[i][j] = 0;
            }
        }
        
        // 中ウェル2: (5,10)-(9,14) = 25マス
        for (int i = 5; i < 10; i++) {
            for (int j = 10; j < 14; j++) {
                verticalWalls[i][j] = 0;
            }
        }
        for (int i = 5; i < 9; i++) {
            for (int j = 10; j < 15; j++) {
                horizontalWalls[i][j] = 0;
            }
        }
    }
};

// メイン解法クラス（効率重視版）
class EfficientSolver {
public:
    vector<Color> tubes;
    vector<Color> targets;
    EfficientPalette palette;
    EfficientColorOptimizer* optimizer;
    
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
        optimizer = new EfficientColorOptimizer(tubes);
        
        // パレット設定を出力
        palette.printWalls();
        
        // 各色を順番に作成
        rep(targetIdx, _H) {
            createTargetColor(targetIdx);
        }
        
        delete optimizer;
    }
    
private:    void createTargetColor(int targetIdx) {
        Color target = targets[targetIdx];
        
        // 最適なレシピを計算
        MixingRecipe recipe = optimizer->findOptimalRecipe(target);
        
        // 適切なウェルを取得
        auto [cellRow, cellCol] = palette.getWellForTarget(targetIdx);
        
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
    
    EfficientSolver solver;
    solver.solve();
    
    return 0;
}
