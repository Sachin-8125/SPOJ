#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int E, F;
        cin >> E >> F;
        int N;
        cin >> N;
        int totalW = F - E;
        vector<int> P(N), W(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i] >> W[i];
        }
        const int INF = 1e9;
        vector<int> dp(totalW + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int w = W[i]; w <= totalW; ++w) {
                if (dp[w - W[i]] != INF) {
                    dp[w] = min(dp[w], dp[w - W[i]] + P[i]);
                }
            }
        }
        if (totalW < 0) {
            cout << "This is impossible.\n";
        } else if (dp[totalW] == INF) {
            cout << "This is impossible.\n";
        } else {
            cout << "The minimum amount of money in the piggy-bank is " << dp[totalW] << ".\n";
        }
    }
    return 0;
}