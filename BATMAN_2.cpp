#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> h(n + 1);
        for (int i = 1; i <= n; ++i) cin >> h[i];
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        dp[0][0] = 0;
        int best = 0;
        for (int k = 1; k <= n; ++k) {
            for (int i = 0; i < k; ++i) {
                for (int j = 0; j < k; ++j) {
                    if (dp[i][j] < 0) continue;
                    if (i != 0 && j != 0 && i == j) continue;
                    int v = dp[i][j] + 1;
                    if (i == 0 || h[k] > h[i]) dp[k][j] = max(dp[k][j], v);
                    if (j == 0 || h[k] < h[j]) dp[i][k] = max(dp[i][k], v);
                }
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) best = max(best, dp[i][j]);
        }
        cout << best << "\n";
    }
    return 0;
}