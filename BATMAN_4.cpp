#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    const long long INF = numeric_limits<long long>::max();

    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<vector<long long>> h(n, vector<long long>(n));
        for (auto &row : h)
            for (auto &x : row) cin >> x;

        vector<vector<vector<long long>>> dp(
            n, vector<vector<long long>>(n, vector<long long>(m, INF)));

        long long firstJump = llabs(h[0][0]);
        if (firstJump < m)
            dp[0][0][static_cast<int>(firstJump)] = firstJump;

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                for (int t = 0; t < m; ++t) {
                    if (dp[r][c][t] == INF) continue;

                    for (int direction = 0; direction < 2; ++direction) {
                        int nextRow = r + (direction == 0);
                        int nextCol = c + (direction == 1);
                        if (nextRow >= n || nextCol >= n) continue;

                        long long jump = llabs(h[nextRow][nextCol] - h[r][c]);
                        if (jump >= m - t) continue;

                        int nt = t + static_cast<int>(jump);
                        dp[nextRow][nextCol][nt] = min(
                            dp[nextRow][nextCol][nt],
                            max(dp[r][c][t], jump));
                    }
                }
            }
        }

        long long bestJump = INF;
        int bestTime = -1;
        for (int t = 0; t < m; ++t) {
            if (dp[n - 1][n - 1][t] < bestJump) {
                bestJump = dp[n - 1][n - 1][t];
                bestTime = t;
            }
        }

        if (bestTime == -1)
            cout << "NO\n";
        else
            cout << "YES : " << bestJump << ' ' << m - bestTime << '\n';
    }
    return 0;
}