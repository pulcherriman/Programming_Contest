#include <bits/stdc++.h>
using namespace std;

struct Color {
    double r, g, b;
    Color() : r(0), g(0), b(0) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}
};

// 2つの色を混合
Color mix(const Color& c1, const Color& c2) {
    return Color((c1.r + c2.r) / 2.0, (c1.g + c2.g) / 2.0, (c1.b + c2.b) / 2.0);
}

// 色の距離（二乗誤差）を計算
double distance(const Color& c1, const Color& c2) {
    return (c1.r - c2.r) * (c1.r - c2.r) + 
           (c1.g - c2.g) * (c1.g - c2.g) + 
           (c1.b - c2.b) * (c1.b - c2.b);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <output_file>" << endl;
        return 1;
    }
    
    string outputFile = argv[1];
    
    // 入力データを読み込み
    int K, D, T;
    cin >> K >> D >> T;
    
    vector<Color> paints(K);
    for (int i = 0; i < K; i++) {
        cin >> paints[i].r >> paints[i].g >> paints[i].b;
    }
    
    vector<Color> targets(D);
    for (int i = 0; i < D; i++) {
        cin >> targets[i].r >> targets[i].g >> targets[i].b;
    }
    
    // 出力ファイルを読み込み
    ifstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return 1;
    }
    
    double totalCost = 0.0;
    int totalTurns = 0;
    int mixingOperations = 0;
    
    for (int d = 0; d < D; d++) {
        string line;
        getline(out, line);
        istringstream iss(line);
        
        int numPaints;
        iss >> numPaints;
        
        if (numPaints <= 0 || numPaints > 2) {
            cerr << "Error: Invalid number of paints at target " << d << ": " << numPaints << endl;
            return 1;
        }
        
        totalTurns += numPaints;
        
        if (numPaints == 1) {
            // 単色での塗装
            int paintId;
            iss >> paintId;
            paintId--; // 1-indexedから0-indexedに変換
            
            if (paintId < 0 || paintId >= K) {
                cerr << "Error: Invalid paint ID at target " << d << ": " << (paintId + 1) << endl;
                return 1;
            }
            
            double cost = distance(targets[d], paints[paintId]);
            totalCost += cost;
        } else if (numPaints == 2) {
            // 混色での塗装
            int paintId1, paintId2;
            iss >> paintId1 >> paintId2;
            paintId1--; paintId2--; // 1-indexedから0-indexedに変換
            
            if (paintId1 < 0 || paintId1 >= K || paintId2 < 0 || paintId2 >= K) {
                cerr << "Error: Invalid paint IDs at target " << d << ": " << (paintId1 + 1) << ", " << (paintId2 + 1) << endl;
                return 1;
            }
            
            Color mixed = mix(paints[paintId1], paints[paintId2]);
            double cost = distance(targets[d], mixed) + 1.0; // 混色ペナルティ +1
            totalCost += cost;
            mixingOperations++;
        }
    }
    
    out.close();
    
    // AtCoderスタイルのスコア計算: round(1e6 / (1000 + sqrt(cost)))
    long long score = (long long)round(1000000.0 / (1000.0 + sqrt(totalCost)));
    
    cout << "Score: " << score << endl;
    cout << "Total Cost: " << fixed << setprecision(6) << totalCost << endl;
    cout << "Total Turns: " << totalTurns << "/" << T << endl;
    cout << "Turn Usage: " << fixed << setprecision(2) << (100.0 * totalTurns / T) << "%" << endl;
    cout << "Mixing Operations: " << mixingOperations << endl;
    
    if (totalTurns > T) {
        cout << "WARNING: Turn limit exceeded!" << endl;
        return 1;
    }
    
    return 0;
}
