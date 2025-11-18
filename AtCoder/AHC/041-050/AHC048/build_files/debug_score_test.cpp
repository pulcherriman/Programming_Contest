#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <map>
#include <algorithm>
#include <stack>
#include <tuple>

using namespace std;

struct Color {
    double c, m, y;
    Color() : c(0), m(0), y(0) {}
    Color(double c, double m, double y) : c(c), m(m), y(y) {}
};

// AtCoder公式のmix関数と同等
Color mix(double v1, Color p1, double v2, Color p2) {
    double sum = v1 + v2;
    if (sum <= 0.0) {
        return Color(0, 0, 0);
    }
    return Color(
        (v1 * p1.c + v2 * p2.c) / sum,
        (v1 * p1.m + v2 * p2.m) / sum,
        (v1 * p1.y + v2 * p2.y) / sum
    );
}

// AtCoder公式と同等のget_ids関数
tuple<int, vector<vector<int>>, vector<int>> get_ids(
    const vector<vector<bool>>& wall_v,
    const vector<vector<bool>>& wall_h
) {
    int N = wall_v.size();
    vector<vector<int>> ids(N, vector<int>(N, -1));
    int ID = 0;
    vector<int> caps;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (ids[i][j] != -1) continue;
            
            stack<pair<int, int>> st;
            st.push({i, j});
            ids[i][j] = ID;
            int cap = 0;
            
            while (!st.empty()) {
                auto [ci, cj] = st.top();
                st.pop();
                cap++;
                
                // Right
                if (cj + 1 < N && !wall_v[ci][cj] && ids[ci][cj + 1] == -1) {
                    ids[ci][cj + 1] = ID;
                    st.push({ci, cj + 1});
                }
                // Down
                if (ci + 1 < N && !wall_h[ci][cj] && ids[ci + 1][cj] == -1) {
                    ids[ci + 1][cj] = ID;
                    st.push({ci + 1, cj});
                }
                // Left
                if (cj > 0 && !wall_v[ci][cj - 1] && ids[ci][cj - 1] == -1) {
                    ids[ci][cj - 1] = ID;
                    st.push({ci, cj - 1});
                }
                // Up
                if (ci > 0 && !wall_h[ci - 1][cj] && ids[ci - 1][cj] == -1) {
                    ids[ci - 1][cj] = ID;
                    st.push({ci - 1, cj});
                }
            }
            caps.push_back(cap);
            ID++;
        }
    }
    
    return std::make_tuple(ID, ids, caps);
}

class DebugScoreCalculator {
private:
    int N, K, H, T, D;
    vector<Color> tubeColors;
    vector<Color> targetColors;
    
    // AtCoder公式準拠の状態変数
    vector<vector<bool>> wall_v, wall_h;
    vector<vector<int>> ids;
    vector<int> caps;
    vector<double> vols;
    vector<Color> colors;
    vector<Color> delivered;
    int V; // tube operations count
    double E; // total error

public:
    void readInput(const string& filename) {
        ifstream file(filename);
        file >> N >> K >> H >> T >> D;
        
        cout << "DEBUG: Input parameters - N=" << N << ", K=" << K << ", H=" << H << ", T=" << T << ", D=" << D << endl;
        
        tubeColors.resize(K);
        for (int i = 0; i < K; i++) {
            file >> tubeColors[i].c >> tubeColors[i].m >> tubeColors[i].y;
        }
        
        targetColors.resize(H);
        for (int i = 0; i < H; i++) {
            file >> targetColors[i].c >> targetColors[i].m >> targetColors[i].y;
        }
        
        cout << "DEBUG: Successfully read " << K << " tube colors and " << H << " target colors" << endl;
    }

    void calculateScore(const string& outputFile) {
        ifstream out(outputFile);
        string line;
        
        cout << "DEBUG: Reading output file: " << outputFile << endl;
        
        // パレット設定の読み込み
        wall_v = vector<vector<bool>>(N, vector<bool>(N-1));
        wall_h = vector<vector<bool>>(N-1, vector<bool>(N));
        
        cout << "DEBUG: Reading wall_v (" << N << " x " << (N-1) << ")" << endl;
        for (int i = 0; i < N; i++) {
            if (!getline(out, line)) {
                cout << "ERROR: Failed to read wall_v line " << i << endl;
                return;
            }
            istringstream iss(line);
            for (int j = 0; j < N-1; j++) {
                int val;
                if (!(iss >> val)) {
                    cout << "ERROR: Failed to parse wall_v[" << i << "][" << j << "]" << endl;
                    return;
                }
                wall_v[i][j] = (val == 1);
            }
        }
        
        cout << "DEBUG: Reading wall_h (" << (N-1) << " x " << N << ")" << endl;
        for (int i = 0; i < N-1; i++) {
            if (!getline(out, line)) {
                cout << "ERROR: Failed to read wall_h line " << i << endl;
                return;
            }
            istringstream iss(line);
            for (int j = 0; j < N; j++) {
                int val;
                if (!(iss >> val)) {
                    cout << "ERROR: Failed to parse wall_h[" << i << "][" << j << "]" << endl;
                    return;
                }
                wall_h[i][j] = (val == 1);
            }
        }
        
        // ウェル情報の初期化
        auto [ID, _ids, _caps] = get_ids(wall_v, wall_h);
        ids = _ids;
        caps = _caps;
        vols = vector<double>(ID, 0.0);
        colors = vector<Color>(ID);
        delivered.clear();
        V = 0;
        E = 0.0;
        
        cout << "DEBUG: Well structure - " << ID << " wells found" << endl;
        if (ID > 0) {
            cout << "DEBUG: Well capacities: ";
            for (int i = 0; i < min(10, ID); i++) {
                cout << caps[i] << " ";
            }
            if (ID > 10) cout << "...";
            cout << endl;
        }
        
        int operationCount = 0;
        int tubeOperationCount = 0;
        
        // 操作の実行
        cout << "DEBUG: Reading operations..." << endl;
        while (getline(out, line) && !line.empty()) {
            istringstream iss(line);
            int op;
            if (!(iss >> op)) {
                cout << "DEBUG: Invalid operation line: " << line << endl;
                break;
            }
            
            if (operationCount < 10 || operationCount % 500 == 0) {
                cout << "DEBUG: Operation " << operationCount << ": " << line << endl;
            }
            
            if (op == 1) {
                int i, j, k;
                if (!(iss >> i >> j >> k)) {
                    cout << "ERROR: Invalid add operation: " << line << endl;
                    continue;
                }
                if (i < 0 || i >= N || j < 0 || j >= N || k < 0 || k >= K) {
                    cout << "ERROR: Invalid add parameters: i=" << i << ", j=" << j << ", k=" << k << endl;
                    continue;
                }
                applyAdd(i, j, k);
                tubeOperationCount++;
            } else if (op == 2) {
                int i, j;
                if (!(iss >> i >> j)) {
                    cout << "ERROR: Invalid deliver operation: " << line << endl;
                    continue;
                }
                if (i < 0 || i >= N || j < 0 || j >= N) {
                    cout << "ERROR: Invalid deliver parameters: i=" << i << ", j=" << j << endl;
                    continue;
                }
                applyDeliver(i, j);
            } else if (op == 3) {
                int i, j;
                if (!(iss >> i >> j)) {
                    cout << "ERROR: Invalid discard operation: " << line << endl;
                    continue;
                }
                if (i < 0 || i >= N || j < 0 || j >= N) {
                    cout << "ERROR: Invalid discard parameters: i=" << i << ", j=" << j << endl;
                    continue;
                }
                applyDiscard(i, j);
            } else if (op == 4) {
                int i1, j1, i2, j2;
                if (!(iss >> i1 >> j1 >> i2 >> j2)) {
                    cout << "ERROR: Invalid toggle operation: " << line << endl;
                    continue;
                }
                applyToggle(i1, j1, i2, j2);
            }
            operationCount++;
        }
        
        cout << "DEBUG: Total operations: " << operationCount << endl;
        cout << "DEBUG: Tube operations (V): " << V << endl;
        cout << "DEBUG: Colors delivered: " << delivered.size() << endl;
        cout << "DEBUG: Total error (E): " << E << endl;
        
        // スコア計算（Rust実装と完全一致）
        long long score;
        if (delivered.size() < H) {
            cout << "DEBUG: Not enough deliveries (" << delivered.size() << " < " << H << "), score = 0" << endl;
            score = 0;
        } else {
            score = 1 + (long long)D * (V - (long long)delivered.size()) + (long long)round(1e4 * E);
            cout << "DEBUG: Score calculation: 1 + " << D << " * (" << V << " - " << delivered.size() << ") + " << (long long)round(1e4 * E) << " = " << score << endl;
        }
        
        cout << "FINAL SCORE: " << score << endl;
    }

private:
    void applyAdd(int i, int j, int k) {
        V++;
        int id = ids[i][j];
        double w = caps[id] - vols[id];
        
        if (w <= 1.0) {
            colors[id] = mix(vols[id], colors[id], w, tubeColors[k]);
            vols[id] = caps[id];
        } else {
            colors[id] = mix(vols[id], colors[id], 1.0, tubeColors[k]);
            vols[id] += 1.0;
        }
    }
    
    void applyDeliver(int i, int j) {
        if (delivered.size() >= H) return;
        
        int id = ids[i][j];
        if (vols[id] < 1.0 - 1e-6) return;
        
        Color color = colors[id];
        Color target = targetColors[delivered.size()];
        
        double error = sqrt(
            pow(color.c - target.c, 2) +
            pow(color.m - target.m, 2) +
            pow(color.y - target.y, 2)
        );
        
        E += error;
        vols[id] = max(0.0, vols[id] - 1.0);
        delivered.push_back(color);
        
        if (delivered.size() <= 10 || delivered.size() % 100 == 0) {
            cout << "DEBUG: Delivered color " << delivered.size() << " - error: " << error << ", total E: " << E << endl;
        }
    }
    
    void applyDiscard(int i, int j) {
        int id = ids[i][j];
        vols[id] = max(0.0, vols[id] - 1.0);
    }
    
    void applyToggle(int i1, int j1, int i2, int j2) {
        // 壁の切り替え（簡略化版）
        if (i1 == i2) {
            int i = i1;
            int j = min(j1, j2);
            if (j >= 0 && j < N-1) {
                wall_v[i][j] = !wall_v[i][j];
            }
        } else {
            int i = min(i1, i2);
            int j = j1;
            if (i >= 0 && i < N-1) {
                wall_h[i][j] = !wall_h[i][j];
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <output_file>" << endl;
        return 1;
    }
    
    DebugScoreCalculator calculator;
    calculator.readInput("../in.txt");
    calculator.calculateScore(argv[1]);
    
    return 0;
}
