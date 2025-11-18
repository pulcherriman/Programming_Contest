#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define rep(i, n) for(int i = 0; i < (int)(n); ++i)

const int N = 20, H = 1000;
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

// 16個のウェル管理
struct Well {
    Color currentColor;
    int currentGrams;
    pii position;
    
    Well() : currentGrams(0), position({-1, -1}) {}
    Well(pii pos) : currentGrams(0), position(pos) {}
    
    bool isEmpty() const { return currentGrams == 0; }
    bool isAvailable() const { return position.first >= 0; }
    
    // 新しい色を追加した場合の結果色を計算
    Color getResultColor(int tubeId, int addGrams) const {
        if (currentGrams == 0) {
            return tubes[tubeId];
        }
        
        Color total = currentColor * currentGrams + tubes[tubeId] * addGrams;
        return total / (currentGrams + addGrams);
    }
    
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
};

// パレット管理クラス
class SmartPalette {
public:
    vector<Well> wells;
    
    SmartPalette() {
        wells.resize(16);
        // 4x4グリッドに配置
        rep(i, 16) {
            int row = i / 4;
            int col = i % 4;
            wells[i] = Well({row * 5 + 2, col * 5 + 2}); // 5x5区画の中央
        }
    }
    
    // パレット設定を出力（正しい形式）
    void printPalette() {
        // 縦の壁 (N行, N-1列)
        rep(i, N) {
            rep(j, N-1) {
                cout << ((j % 5 == 4) ? 1 : 0);
                if (j < N-2) cout << " ";
            }
            cout << "\n";
        }
        
        // 横の壁 (N-1行, N列)
        rep(i, N-1) {
            rep(j, N) {
                cout << ((i % 5 == 4) ? 1 : 0);
                if (j < N-1) cout << " ";
            }
            cout << "\n";
        }
    }
    
    // 指定されたターゲット色に対して最適な行動を計算
    struct Action {
        int wellId;
        vector<pii> additions; // {tubeId, grams}
        double score; // D*(追加回数-1) + 10000*誤差
        Color resultColor;
        
        Action() : wellId(-1), score(1e9) {}
    };
    
    Action findBestAction(const Color& target) {
        Action bestAction;
        
        rep(wellId, 16) {
            Well& well = wells[wellId];
            
            // 1. 現在の色をそのまま使用
            if (!well.isEmpty()) {
                Action action;
                action.wellId = wellId;
                action.resultColor = well.currentColor;
                action.score = 10000.0 * target.distance(well.currentColor);
                
                if (action.score < bestAction.score) {
                    bestAction = action;
                }
            }
            
            // 2. 各チューブを1-3グラム追加してみる
            rep(tubeId, K) {
                for (int addGrams = 1; addGrams <= 3; addGrams++) {
                    Action action;
                    action.wellId = wellId;
                    action.additions.push_back({tubeId, addGrams});
                    action.resultColor = well.getResultColor(tubeId, addGrams);
                    action.score = D * (addGrams - 1) + 10000.0 * target.distance(action.resultColor);
                    
                    if (action.score < bestAction.score) {
                        bestAction = action;
                    }
                }
            }
            
            // 3. 2色混合（空のウェルの場合のみ）
            if (well.isEmpty()) {
                rep(tube1, K) {
                    rep(tube2, tube1 + 1) {
                        for (int g1 = 1; g1 <= 2; g1++) {
                            for (int g2 = 1; g2 <= 2; g2++) {
                                if (g1 + g2 > 4) continue;
                                
                                Color mixed = (tubes[tube1] * g1 + tubes[tube2] * g2) / (g1 + g2);
                                
                                Action action;
                                action.wellId = wellId;
                                action.additions.push_back({tube1, g1});
                                action.additions.push_back({tube2, g2});
                                action.resultColor = mixed;
                                action.score = D * (g1 + g2 - 1) + 10000.0 * target.distance(mixed);
                                
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
        
        // 絵の具を追加
        for (auto [tubeId, grams] : action.additions) {
            rep(g, grams) {
                cout << "1 " << well.position.first << " " << well.position.second 
                     << " " << tubeId << "\n";
            }
            well.addPaint(tubeId, grams);
        }
        
        // 1グラム消費
        cout << "2 " << well.position.first << " " << well.position.second << "\n";
        well.consume();
    }
};

// メインソルバー
class OptimalSolver {
public:
    SmartPalette palette;
    
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
        
        // パレット設定を出力
        palette.printPalette();
        
        // 各ターゲットを順次処理
        rep(i, _H) {
            SmartPalette::Action bestAction = palette.findBestAction(targets[i]);
            palette.executeAction(bestAction);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    OptimalSolver solver;
    solver.solve();
    
    return 0;
}
