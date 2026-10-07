#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        string a, b;
        int K;
        cin >> a >> b >> K;
        int n = (int)a.size();
        int m = (int)b.size();
        const int INF_NEG = -1e9;

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(K + 1, INF_NEG)));

        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                dp[i][j][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int l = 1; l <= K; ++l) {
                    int best = max(dp[i-1][j][l], dp[i][j-1][l]); 

                    if (a[i-1] == b[j-1]) {
                        int cand = dp[i-1][j-1][l-1];
                        if (cand != INF_NEG) {
                            cand += static_cast<int>(a[i-1]); 
                            best = max(best, cand);
                        }
                    }
                    dp[i][j][l] = best;
                }
            }
        }

        int ans = dp[n][m][K];
        if (ans < 0) ans = 0;
        cout << ans << "\n";
    }
    return 0;
}