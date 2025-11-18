/**
* C++23 Template @ AtCoder
* AHC048 Solution
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

class Random {
public:
    typedef uint_fast32_t result_type;
    constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
    static constexpr result_type max(){return numeric_limits<result_type>::max();}
    static constexpr result_type min(){return 0;}
    constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){ }
    constexpr int operator()(int a,int b){return next()%(b-a)+a;}
    constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
    constexpr double operator()(double a,double b){
        double scale = (double)next() / (double)std::numeric_limits<uint_fast32_t>::max();
        return scale*(b - a) + a;
    }
private:
    result_type y;
    constexpr result_type next(){
        y ^= (y << 13);
        y ^= (y >> 17);
        y ^= (y << 5);
        return y;
    }
};

class Timer {
    #ifdef _DEBUG
    static constexpr uint64_t ClocksPerMsec = 3587000;
    #else
    static constexpr uint64_t ClocksPerMsec = 2987000;
    #endif
    const uint64_t start,limit;
    uint64_t getClocks() const{
        unsigned int lo,hi;
        __asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
        return((uint64_t)hi<<32)|lo;
    }
public:
    Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
    uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
    operator bool() const { return getClocks()<limit; }
    float persentile() const { return (float)get()/((float)limit/ClocksPerMsec); }
};

#ifdef _DEBUG
Random rnd(1); // デバッグ時は固定シード
#else
Random rnd(0); // 本番用は可変シード
#endif

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
};

// ウェルを表現する構造体
struct Well {
    Color color;
    double volume;
    set<pii> cells;
    
    Well() : color(), volume(0) {}
    
    // 絵の具を追加（混合）
    void addPaint(const Color& newColor, double amount) {
        if (volume < EPS) {
            // 空のウェルの場合
            color = newColor;
            volume = amount;
        } else {
            // 既存の絵の具と混合
            Color mixedColor = (color * volume + newColor * amount) / (volume + amount);
            volume += amount;
            color = mixedColor;
        }
    }
    
    // 容量制限を考慮した追加
    double addPaintWithCapacity(const Color& newColor, double amount) {
        double capacity = cells.size();
        double availableSpace = capacity - volume;
        double actualAmount = min(amount, availableSpace);
        
        if (actualAmount > EPS) {
            addPaint(newColor, actualAmount);
        }
        
        return actualAmount; // 実際に追加された量を返す
    }
    
    // 絵の具を取り出す
    Color removePaint(double amount) {
        if (volume < 1.0 - 1e-6) {
            return Color(); // 取り出せない
        }
        
        Color result = color;
        if (volume >= 1.0) {
            // ちょうど1グラム取り出す
            volume -= amount;
        } else {
            // 全量取り出す
            volume = 0;
        }
        
        return result;
    }
    
    bool canRemove() const {
        return volume >= 1.0 - 1e-6;
    }
};

// パレットを管理するクラス
class Palette {
public:
    vvi verticalWalls;  // 縦の仕切り (i,j)-(i,j+1)
    vvi horizontalWalls; // 横の仕切り (i,j)-(i+1,j)
    vector<Well> wells;
    vvi cellToWell; // 各セルがどのウェルに属するか
      Palette() {
        // 後で初期化
    }
    
    void initialize() {
        verticalWalls = vvi(N, vi(N-1, 1));    // 初期は全て仕切りあり
        horizontalWalls = vvi(N-1, vi(N, 1));  // 初期は全て仕切りあり
        cellToWell = vvi(N, vi(N, -1));
        
        // 初期状態では各セルが個別のウェル
        wells.resize(N * N);
        rep(i, N) rep(j, N) {
            int wellId = i * N + j;
            cellToWell[i][j] = wellId;
            wells[wellId].cells.insert({i, j});
        }
    }
    
    // ウェルを再構築（Union-Find的に）
    void rebuildWells() {
        wells.clear();
        cellToWell = vvi(N, vi(N, -1));
        
        vvb visited(N, vb(N, false));
        int wellId = 0;
        
        rep(i, N) rep(j, N) {
            if (!visited[i][j]) {
                Well newWell;
                queue<pii> q;
                q.push({i, j});
                visited[i][j] = true;
                
                while (!q.empty()) {
                    auto [ci, cj] = q.front();
                    q.pop();
                    
                    cellToWell[ci][cj] = wellId;
                    newWell.cells.insert({ci, cj});
                    
                    // 右隣をチェック
                    if (cj + 1 < N && !visited[ci][cj+1] && verticalWalls[ci][cj] == 0) {
                        visited[ci][cj+1] = true;
                        q.push({ci, cj+1});
                    }
                    
                    // 下隣をチェック
                    if (ci + 1 < N && !visited[ci+1][cj] && horizontalWalls[ci][cj] == 0) {
                        visited[ci+1][cj] = true;
                        q.push({ci+1, cj});
                    }
                    
                    // 左隣をチェック
                    if (cj - 1 >= 0 && !visited[ci][cj-1] && verticalWalls[ci][cj-1] == 0) {
                        visited[ci][cj-1] = true;
                        q.push({ci, cj-1});
                    }
                    
                    // 上隣をチェック
                    if (ci - 1 >= 0 && !visited[ci-1][cj] && horizontalWalls[ci-1][cj] == 0) {
                        visited[ci-1][cj] = true;
                        q.push({ci-1, cj});
                    }
                }
                
                wells.push_back(newWell);
                wellId++;
            }
        }
    }
    
    // 仕切りを操作
    void toggleWall(int i1, int j1, int i2, int j2) {
        if (i1 == i2 && abs(j1 - j2) == 1) {
            // 縦の仕切り
            int i = i1;
            int j = min(j1, j2);
            verticalWalls[i][j] = 1 - verticalWalls[i][j];
        } else if (j1 == j2 && abs(i1 - i2) == 1) {
            // 横の仕切り
            int i = min(i1, i2);
            int j = j1;
            horizontalWalls[i][j] = 1 - horizontalWalls[i][j];
        }
        rebuildWells();
    }
    
    // 初期仕切り配置を出力
    void printInitialWalls() {
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
};

// 最適な混合比を計算する関数（貪欲法）
vector<double> findOptimalWeights(const Color& target, const vector<Color>& tubes) {
    int k = tubes.size();
    vector<double> weights(k, 0);
    
    // 最も近い色を見つける貪欲法
    double bestDist = 1e9;
    int bestTube = 0;
    
    rep(i, k) {
        double dist = target.distanceSquared(tubes[i]);
        if (dist < bestDist) {
            bestDist = dist;
            bestTube = i;
        }
    }
    
    weights[bestTube] = 1.0;
    return weights;
}

// より高度な最適化（2色混合）
vector<double> findOptimalWeightsTwoColor(const Color& target, const vector<Color>& tubes) {
    int k = tubes.size();
    vector<double> bestWeights(k, 0);
    double bestError = 1e9;
    
    // 単色での最適解をベースライン
    rep(i, k) {
        double error = target.distanceSquared(tubes[i]);
        if (error < bestError) {
            bestError = error;
            bestWeights = vector<double>(k, 0);
            bestWeights[i] = 1.0;
        }
    }
    
    // 2色混合を試す
    rep(i, k) rep(j, i+1) {
        // w*tubes[i] + (1-w)*tubes[j] = target を満たすwを求める
        for (double w = 0.0; w <= 1.0; w += 0.1) {
            Color mixed = tubes[i] * w + tubes[j] * (1.0 - w);
            double error = target.distanceSquared(mixed);
            
            if (error < bestError) {
                bestError = error;
                bestWeights = vector<double>(k, 0);
                bestWeights[i] = w;
                bestWeights[j] = 1.0 - w;
            }
        }
    }
    
    return bestWeights;
}

// メインの解法
class Solver {
public:
    vector<Color> tubes;
    vector<Color> targets;
    Palette palette;
    vector<string> operations;    void solve() {
        // 入力読み込み（N=20, H=1000は固定なので読み飛ばす）
        int _N, _H;
        cin >> _N >> K >> _H >> T >> D;
        
        tubes.resize(K);
        rep(i, K) {
            cin >> tubes[i].c >> tubes[i].m >> tubes[i].y;
        }
        
        targets.resize(H);
        rep(i, H) {
            cin >> targets[i].c >> targets[i].m >> targets[i].y;
        }
        
        // パレットを初期化
        palette.initialize();
        
        // 初期パレット設定（全て個別ウェル）
        palette.printInitialWalls();
        
        // 各色を順番に作成
        rep(targetIdx, H) {
            createColor(targetIdx);
        }
    }
    
private:    void createColor(int targetIdx) {
        Color target = targets[targetIdx];
        
        // 最も近い単色を選ぶ（簡単な貪欲法）
        int bestTube = 0;
        double bestDist = 1e9;
        rep(i, K) {
            double dist = target.distanceSquared(tubes[i]);
            if (dist < bestDist) {
                bestDist = dist;
                bestTube = i;
            }
        }
        
        // セル(0,0)を使用（簡単のため）
        int wellId = 0;
        
        // チューブから1グラム追加
        operations.push_back("1 0 0 " + to_string(bestTube));
        palette.wells[wellId].addPaintWithCapacity(tubes[bestTube], 1.0);
        
        // 1グラム取り出して画伯に渡す
        operations.push_back("2 0 0");
        palette.wells[wellId].removePaint(1.0);
        
        // 操作を出力
        for (const string& op : operations) {
            cout << op << "\n";
        }
        operations.clear();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(0);
    
    Solver solver;
    solver.solve();
    
    return 0;
}
