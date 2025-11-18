/**
* C++23 Template @ AtCoder
* AHC048 Solution - Paint Reuse Version
* 絵の具再利用とスマートクラスタリング最適化
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

// 絵の具ストック管理構造体
struct PaintStock {
    Color color;
    int remainingGrams;
    pii wellPosition;
    int lastUsedTurn;
    vector<int> plannedUse; // この絵の具を使用予定のターン番号
    
    PaintStock() : remainingGrams(0), wellPosition({-1, -1}), lastUsedTurn(-1) {}
    PaintStock(const Color& c, int grams, pii pos) 
        : color(c), remainingGrams(grams), wellPosition(pos), lastUsedTurn(-1) {}
    
    bool isEmpty() const { return remainingGrams <= 0; }
    bool isAvailable() const { return remainingGrams > 0 && wellPosition.first >= 0; }
    
    // 使用計画の最後のターン番号を取得
    int getLastPlannedTurn() const {
        return plannedUse.empty() ? lastUsedTurn : *max_element(plannedUse.begin(), plannedUse.end());
    }
};

// 色クラスタ管理
struct ColorCluster {
    vector<int> targetIndices;
    Color averageColor;
    pii assignedWell;
    bool processed;
    
    ColorCluster() : assignedWell({-1, -1}), processed(false) {}
    
    void calculateAverage(const vector<Color>& targets) {
        if (targetIndices.empty()) return;
        
        double totalC = 0, totalM = 0, totalY = 0;
        for (int idx : targetIndices) {
            totalC += targets[idx].c;
            totalM += targets[idx].m;
            totalY += targets[idx].y;
        }
        int count = targetIndices.size();
        averageColor = Color(totalC / count, totalM / count, totalY / count);
    }
};

// パレット管理クラス（再利用対応）
class SmartPalette {
public:
    vvi verticalWalls;
    vvi horizontalWalls;
    vector<PaintStock> stocks;
    vector<bool> wellOccupied; // ウェルの使用状況
    int currentTurn;
    
    SmartPalette() : currentTurn(0) {
        verticalWalls = vvi(N, vi(N-1, 1));
        horizontalWalls = vvi(N-1, vi(N, 1));
        wellOccupied = vector<bool>(N * N, false);
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
    
    // 空いているウェルを探す
    pii findAvailableWell(int minSize = 1) {
        // 大ウェル（50マス）をチェック
        if (!wellOccupied[0] && minSize <= 50) {
            return {0, 0};
        }
        
        // 中ウェル（25マス）をチェック
        if (!wellOccupied[1] && minSize <= 25) {
            return {0, 10};
        }
        
        // 小ウェル（1マス）をチェック
        rep(i, N) rep(j, N) {
            int wellId = i * N + j;
            if (!wellOccupied[wellId] && minSize <= 1) {
                return {i, j};
            }
        }
        
        return {-1, -1}; // 見つからない
    }
    
    // ウェルを占有
    void occupyWell(pii position) {
        if (position.first < 0) return;
        
        if (position == make_pair(0, 0)) {
            wellOccupied[0] = true; // 大ウェル
        } else if (position == make_pair(0, 10)) {
            wellOccupied[1] = true; // 中ウェル
        } else {
            int wellId = position.first * N + position.second;
            wellOccupied[wellId] = true;
        }
    }
    
    // ウェルを解放
    void releaseWell(pii position) {
        if (position.first < 0) return;
        
        if (position == make_pair(0, 0)) {
            wellOccupied[0] = false; // 大ウェル
        } else if (position == make_pair(0, 10)) {
            wellOccupied[1] = false; // 中ウェル
        } else {
            int wellId = position.first * N + position.second;
            wellOccupied[wellId] = false;
        }
    }
    
    // 絵の具ストックを追加
    int addPaintStock(const Color& color, int grams, const vector<int>& plannedTurns) {
        pii well = findAvailableWell(grams);
        if (well.first < 0) return -1; // ウェルが見つからない
        
        occupyWell(well);
        
        PaintStock stock(color, grams, well);
        stock.plannedUse = plannedTurns;
        stocks.push_back(stock);
        
        return stocks.size() - 1; // ストックID
    }
    
    // 絵の具を使用
    bool usePaint(int stockId) {
        if (stockId < 0 || stockId >= stocks.size()) return false;
        if (stocks[stockId].isEmpty()) return false;
        
        stocks[stockId].remainingGrams--;
        stocks[stockId].lastUsedTurn = currentTurn;
        
        // 空になったらウェルを解放
        if (stocks[stockId].isEmpty()) {
            releaseWell(stocks[stockId].wellPosition);
            stocks[stockId].wellPosition = {-1, -1};
        }
        
        return true;
    }
    
    // 期限切れの絵の具を廃棄
    void cleanupExpiredPaints() {
        for (auto& stock : stocks) {
            if (!stock.isAvailable()) continue;
            
            int lastPlannedTurn = stock.getLastPlannedTurn();
            if (lastPlannedTurn >= 0 && currentTurn > lastPlannedTurn + 10) { // 10ターン猶予
                // 廃棄処理
                int toDispose = stock.remainingGrams;
                rep(i, toDispose) {
                    cout << "3 " << stock.wellPosition.first << " " << stock.wellPosition.second << "\n";
                }
                releaseWell(stock.wellPosition);
                stock.remainingGrams = 0;
                stock.wellPosition = {-1, -1};
            }
        }
    }
    
private:
    void createOptimalWells() {
        // 大ウェル: (0,0)-(4,9) = 50マス
        rep(i, 5) rep(j, 9) {
            verticalWalls[i][j] = 0;
        }
        rep(i, 4) rep(j, 10) {
            horizontalWalls[i][j] = 0;
        }
        
        // 中ウェル: (0,10)-(4,14) = 25マス
        rep(i, 5) rep(j, 4) {
            if (j < 4) verticalWalls[i][10 + j] = 0;
        }
        rep(i, 4) rep(j, 5) {
            horizontalWalls[i][10 + j] = 0;
        }
    }
};

// スマートクラスタリングクラス
class SmartClusterer {
private:
    vector<Color> targets;
    vector<ColorCluster> clusters;
    
public:
    SmartClusterer(const vector<Color>& targets_) : targets(targets_) {}
    
    // 距離とターン制約を考慮したクラスタリング
    void createSmartClusters(int maxClusterSize = 5, int maxTurnDistance = 50) {
        clusters.clear();
        vector<bool> assigned(targets.size(), false);
        
        for (int startIdx = 0; startIdx < targets.size(); startIdx++) {
            if (assigned[startIdx]) continue;
            
            ColorCluster cluster;
            cluster.targetIndices.push_back(startIdx);
            assigned[startIdx] = true;
            
            // 近い色かつ近いターンの目標色を追加
            for (int checkIdx = startIdx + 1; 
                 checkIdx < targets.size() && checkIdx <= startIdx + maxTurnDistance; 
                 checkIdx++) {
                
                if (assigned[checkIdx]) continue;
                if (cluster.targetIndices.size() >= maxClusterSize) break;
                
                double colorDistance = targets[startIdx].distanceSquared(targets[checkIdx]);
                if (colorDistance < 0.01) { // 色が十分近い
                    cluster.targetIndices.push_back(checkIdx);
                    assigned[checkIdx] = true;
                }
            }
            
            cluster.calculateAverage(targets);
            clusters.push_back(cluster);
        }
    }
    
    const vector<ColorCluster>& getClusters() const {
        return clusters;
    }
    
    vector<ColorCluster>& getClusters() {
        return clusters;
    }
};

// 混合レシピ構造体（簡略版）
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
    
    int getTotalGrams() const {
        int total = 0;
        for (auto& [tubeId, grams] : tubes) {
            total += grams;
        }
        return total;
    }
};

// シンプル色最適化クラス
class SimpleColorOptimizer {
private:
    vector<Color> tubes;
    
public:
    SimpleColorOptimizer(const vector<Color>& tubes_) : tubes(tubes_) {}
    
    // シンプルな最適化（操作コストを抑制）
    MixingRecipe findOptimalRecipe(const Color& target) {
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
        
        // 2色最適化（軽量版）
        rep(i, K) rep(j, i+1) {
            for (int w1 = 1; w1 <= 3; w1++) {
                for (int w2 = 1; w2 <= 3; w2++) {
                    if (w1 + w2 > 5) continue; // 総量制限
                    
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
};

// メインソルバークラス（再利用版）
class PaintReuseSolver {
public:
    vector<Color> tubes;
    vector<Color> targets;
    SmartPalette palette;
    SimpleColorOptimizer* optimizer;
    SmartClusterer* clusterer;
    
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
        optimizer = new SimpleColorOptimizer(tubes);
        clusterer = new SmartClusterer(targets);
        
        // スマートクラスタリング実行
        clusterer->createSmartClusters();
        
        // パレット設定を出力
        palette.printWalls();
        
        // クラスタごとに処理
        processAllClusters();
        
        delete optimizer;
        delete clusterer;
    }
    
private:
    void processAllClusters() {
        auto& clusters = clusterer->getClusters();
        
        for (auto& cluster : clusters) {
            if (cluster.targetIndices.size() == 1) {
                // 単独処理
                createSingleColor(cluster.targetIndices[0]);
            } else {
                // バッチ処理
                processBatchCluster(cluster);
            }
            palette.currentTurn += cluster.targetIndices.size();
            palette.cleanupExpiredPaints();
        }
    }
    
    void createSingleColor(int targetIdx) {
        Color target = targets[targetIdx];
        
        // 既存の絵の具から利用可能なものを探す
        int bestStockId = findBestExistingPaint(target);
        
        if (bestStockId >= 0) {
            // 既存絵の具を使用
            auto& stock = palette.stocks[bestStockId];
            cout << "2 " << stock.wellPosition.first << " " << stock.wellPosition.second << "\n";
            palette.usePaint(bestStockId);
        } else {
            // 新規作成
            MixingRecipe recipe = optimizer->findOptimalRecipe(target);
            createNewPaint(recipe, {targetIdx});
        }
    }
    
    void processBatchCluster(ColorCluster& cluster) {
        // クラスタの平均色に近い絵の具を作成
        MixingRecipe recipe = optimizer->findOptimalRecipe(cluster.averageColor);
        
        // 必要量を計算（各色1グラム + 少し余裕）
        int requiredGrams = cluster.targetIndices.size();
        
        // レシピをスケールアップ
        int recipeGrams = recipe.getTotalGrams();
        int scale = (requiredGrams + recipeGrams - 1) / recipeGrams; // 切り上げ
        
        // 実際に絵の具を作成
        createNewPaint(recipe, cluster.targetIndices, scale);
    }
    
    int findBestExistingPaint(const Color& target) {
        int bestStockId = -1;
        double bestError = 1e9;
        
        rep(i, palette.stocks.size()) {
            auto& stock = palette.stocks[i];
            if (!stock.isAvailable()) continue;
            
            double error = target.distanceSquared(stock.color);
            if (error < bestError && error < 0.005) { // 許容誤差範囲内
                bestError = error;
                bestStockId = i;
            }
        }
        
        return bestStockId;
    }
    
    void createNewPaint(const MixingRecipe& recipe, const vector<int>& targetIndices, int scale = 1) {
        pii well = palette.findAvailableWell(recipe.getTotalGrams() * scale);
        if (well.first < 0) {
            // ウェルが見つからない場合は単独処理にフォールバック
            for (int targetIdx : targetIndices) {
                createSingleColor(targetIdx);
            }
            return;
        }
        
        palette.occupyWell(well);
        
        // 絵の具を混合
        int totalGrams = 0;
        for (auto& [tubeId, grams] : recipe.tubes) {
            rep(s, scale) {
                rep(g, grams) {
                    cout << "1 " << well.first << " " << well.second << " " << tubeId << "\n";
                    totalGrams++;
                }
            }
        }
        
        // 各ターンで1グラムずつ使用
        for (int targetIdx : targetIndices) {
            cout << "2 " << well.first << " " << well.second << "\n";
            totalGrams--;
        }
        
        // 残りを廃棄
        rep(i, totalGrams) {
            cout << "3 " << well.first << " " << well.second << "\n";
        }
        
        palette.releaseWell(well);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    PaintReuseSolver solver;
    solver.solve();
    
    return 0;
}
