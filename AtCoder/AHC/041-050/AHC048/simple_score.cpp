#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream input(argv[1]);
    ifstream output(argv[2]);
    
    int N, K, H, T, D;
    input >> N >> K >> H >> T >> D;
    
    vector<vector<int>> paints(K, vector<int>(3));
    for (int i = 0; i < K; i++) {
        input >> paints[i][0] >> paints[i][1] >> paints[i][2];
    }
    
    vector<vector<int>> targets(D, vector<int>(3));
    for (int i = 0; i < D; i++) {
        input >> targets[i][0] >> targets[i][1] >> targets[i][2];
    }
    
    long long total_score = 0;
    int total_turns = 0;
    
    for (int d = 0; d < D; d++) {
        int num_paints;
        output >> num_paints;
        
        total_turns += num_paints;
        
        if (num_paints == 0) {
            // 配送なし
            continue;
        }
        
        vector<int> paint_ids(num_paints);
        for (int i = 0; i < num_paints; i++) {
            output >> paint_ids[i];
            paint_ids[i]--; // 1-indexedから0-indexedに変換
        }
        
        // 混色計算
        vector<double> mixed = {0.0, 0.0, 0.0};
        for (int id : paint_ids) {
            for (int c = 0; c < 3; c++) {
                mixed[c] += paints[id][c];
            }
        }
        for (int c = 0; c < 3; c++) {
            mixed[c] /= num_paints;
        }
        
        // スコア計算
        long long delivery_score = 0;
        for (int c = 0; c < 3; c++) {
            double diff = mixed[c] - targets[d][c];
            delivery_score += (long long)(diff * diff);
        }
        
        total_score += delivery_score;
    }
    
    cout << "Total score: " << total_score << endl;
    cout << "Total turns used: " << total_turns << "/" << T << endl;
    cout << "Turn usage: " << (100.0 * total_turns / T) << "%" << endl;
    
    return 0;
}
