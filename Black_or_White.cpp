#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 200;
static const int INF = 1000000000;
static int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != -1) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        for (int i = 0; i <= n; ++i)
            for (int lb = 0; lb <= n; ++lb)
                for (int lw = 0; lw <= n; ++lw)
                    dp[i][lb][lw] = INF;

        dp[0][0][0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int lb = 0; lb <= i; ++lb) {
                for (int lw = 0; lw <= i; ++lw) {
                    int cur = dp[i][lb][lw];
                    if (cur == INF) continue;

                    dp[i + 1][lb][lw] = min(dp[i + 1][lb][lw], cur + 1);

                    if (lb == 0 || a[i] > a[lb - 1])
                        dp[i + 1][i + 1][lw] = min(dp[i + 1][i + 1][lw], cur);

                    if (lw == 0 || a[i] < a[lw - 1])
                        dp[i + 1][lb][i + 1] = min(dp[i + 1][lb][i + 1], cur);
                }
            }
        }

        int ans = INF;
        for (int lb = 0; lb <= n; ++lb)
            for (int lw = 0; lw <= n; ++lw)
                ans = min(ans, dp[n][lb][lw]);
        cout << ans << '\n';
    }
    return 0;
}