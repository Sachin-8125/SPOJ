#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        cin >> N >> M;

        vector<int> A(N);
        for (int &x : A) {
            cin >> x;
        }

        vector<bool> bad(1024, false);
        for (int i = 0; i < M; ++i) {
            int x;
            cin >> x;
            bad[x] = true;
        }

        vector<int> dp(1024, 0), next_dp(1024, 0);

        dp[0] = 1;

        for (int value : A) {
            next_dp = dp;

            for (int x = 0; x < 1024; ++x) {
                int new_xor = x ^ value;
                next_dp[new_xor] =
                    (next_dp[new_xor] + dp[x]) % MOD;
            }

            dp.swap(next_dp);
        }

        int answer = 0;

        for (int x = 0; x < 1024; ++x) {
            if (!bad[x]) {
                answer = (answer + dp[x]) % MOD;
            }
        }

        cout << "Case " << tc << ": " << answer << '\n';
    }

    return 0;
}