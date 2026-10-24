#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    for (int tc = 0; tc < T; ++tc) {
        string a, b;
        cin >> a >> b;
        int n = (int)a.size(), m = (int)b.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (a[i] == b[j])
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }

        vector<array<int, 26>> nextA(n + 1), nextB(m + 1);
        nextA[n].fill(n);
        for (int i = n - 1; i >= 0; --i) {
            nextA[i] = nextA[i + 1];
            nextA[i][a[i] - 'a'] = i;
        }
        nextB[m].fill(m);
        for (int j = m - 1; j >= 0; --j) {
            nextB[j] = nextB[j + 1];
            nextB[j][b[j] - 'a'] = j;
        }

        if (tc > 0) cout << '\n';
        string current;
        function<void(int, int)> generate = [&](int i, int j) {
            int remaining = dp[i][j];
            if (remaining == 0) {
                cout << current << '\n';
                return;
            }

            for (int c = 0; c < 26; ++c) {
                int p = nextA[i][c];
                int q = nextB[j][c];
                if (p < n && q < m && dp[p + 1][q + 1] == remaining - 1) {
                    current.push_back(char('a' + c));
                    generate(p + 1, q + 1);
                    current.pop_back();
                }
            }
        };

        generate(0, 0);
    }
    return 0;
}