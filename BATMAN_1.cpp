#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> opening(n);
        for (int &x : opening) cin >> x;

        vector<vector<int>> cost(n, vector<int>(m));
        vector<vector<int>> power(n, vector<int>(m));
        for (auto &row : cost)
            for (int &x : row) cin >> x;
        for (auto &row : power)
            for (int &x : row) cin >> x;

        vector<int> dp(k + 1, 0);
        const int NEG = -1000000000;
        for (int i = 0; i < n; ++i) {
            vector<int> opened(k + 1, NEG);
            for (int b = opening[i]; b <= k; ++b)
                opened[b] = dp[b - opening[i]];

            for (int j = 0; j < m; ++j) {
                int c = cost[i][j], p = power[i][j];
                for (int b = c; b <= k; ++b) {
                    if (opened[b - c] != NEG)
                        opened[b] = max(opened[b], opened[b - c] + p);
                }
            }
            for (int b = 0; b <= k; ++b)
                dp[b] = max(dp[b], opened[b]);
        }
        cout << dp[k] << '\n';
    }
    return 0;
}