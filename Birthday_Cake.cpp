#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int H, W, K;
        cin >> H >> W >> K;

        vector<string> grid(H);
        for (int i = 0; i < H; ++i) {
            cin >> grid[i];
        }

        vector<vector<int>> pref(H + 1, vector<int>(W + 1, 0));
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                pref[r + 1][c + 1] = pref[r][c + 1] + pref[r + 1][c] - pref[r][c] + (grid[r][c] == 'C');
            }
        }

        const int INF = 1e9;
        int best_area = INF;

        for (int r1 = 0; r1 < H; ++r1) {
            for (int r2 = r1; r2 < H; ++r2) {
                int height = r2 - r1 + 1;
                if (height > best_area) break;

                int c1 = 0;
                for (int c2 = 0; c2 < W; ++c2) {
                    auto count_chips = [&](int left_col, int right_col) {
                        return pref[r2 + 1][right_col + 1] - pref[r1][right_col + 1]
                             - pref[r2 + 1][left_col] + pref[r1][left_col];
                    };

                    while (c1 < c2 && count_chips(c1, c2) > K) {
                        ++c1;
                    }
                    while (c1 < c2 && count_chips(c1 + 1, c2) == K) {
                        ++c1;
                    }

                    if (count_chips(c1, c2) == K) {
                        int area = height * (c2 - c1 + 1);
                        best_area = min(best_area, area);
                    }
                }
            }
        }

        if (best_area == INF) {
            cout << -1 << '\n';
        } else {
            cout << best_area << '\n';
        }
    }

    return 0;
}