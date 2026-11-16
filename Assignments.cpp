#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        vector<long long> dp(1 << n, 0);
        dp[0] = 1;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (!dp[mask]) continue;
            int i = __builtin_popcount(mask);
            if (i >= n) continue;
            for (int j = 0; j < n; ++j) {
                if (a[i][j] && !(mask >> j & 1)) {
                    dp[mask | (1 << j)] += dp[mask];
                }
            }
        }
        printf("%lld\n", dp[(1 << n) - 1]);
    }
    return 0;
}