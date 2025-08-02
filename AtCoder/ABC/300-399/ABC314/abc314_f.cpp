#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> C(N);
    vector<vector<int>> S(N);
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi >> C[i];

        S[i].resize(C[i]);
        for (int j = 0; j < C[i]; j++) {
            cin >> S[i][j];
        }
    }

    vector<double> dp(M + 1, 1e18);
    dp[0] = 0.0;

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            double expected_value = 0.0;
            for (int k = 0; k < S[j].size(); k++) {
                expected_value += min(i, S[j][k]) * 1.0 / S[j].size();
            }
            dp[i] = min(dp[i], dp[max(0, i - (int)expected_value)] + C[j]);
        }
    }

    cout << dp[M] << endl;

    return 0;
}
