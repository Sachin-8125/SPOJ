#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int a[16], b[16];
int dp[1 << 16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        int limit = 1 << n;
        fill(dp + 1, dp + limit, 1e9);
        dp[0] = 0;
        for (int mask = 0; mask < limit - 1; ++mask) {
            int r = __builtin_popcount(mask);
            int rem = (limit - 1) ^ mask;
            while (rem) {
                int bit = rem & -rem;
                int c = __builtin_ctz(bit);
                int cost = abs(r - c) + abs(a[r] - b[c]);
                int next_mask = mask | bit;
                if (dp[mask] + cost < dp[next_mask]) {
                    dp[next_mask] = dp[mask] + cost;
                }
                rem -= bit;
            }
        }
        cout << dp[limit - 1] << "\n";
    }
    return 0;
}