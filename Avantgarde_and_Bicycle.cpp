#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> grid(N);
    int sr = -1, sc = -1;
    vector<int> friends;

    for (int i = 0; i < N; ++i) {
        cin >> grid[i];

        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    vector<vector<int>> altitude(N, vector<int>(N));
    vector<int> values;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> altitude[i][j];
            values.push_back(altitude[i][j]);
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<pair<int, int>> directions;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            directions.push_back({dr, dc});
        }
    }

    auto can = [&](int low, int high) -> bool {
        if (altitude[sr][sc] < low || altitude[sr][sc] > high) {
            return false;
        }

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<pair<int, int>> q;

        q.push({sr, sc});
        visited[sr][sc] = true;

        int required = 0;
        int reached = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 'F') {
                    ++required;
                }
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (grid[r][c] == 'F') {
                ++reached;
            }

            for (auto [dr, dc] : directions) {
                int nr = r + dr;
                int nc = c + dc;

                if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
                    continue;
                }

                if (visited[nr][nc]) {
                    continue;
                }

                if (altitude[nr][nc] < low || altitude[nr][nc] > high) {
                    continue;
                }

                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }

        return reached == required;
    };

    int answer = INT_MAX;

    for (int left = 0; left < static_cast<int>(values.size()); ++left) {
        int low = values[left];

        int lo = left;
        int hi = static_cast<int>(values.size()) - 1;
        int bestRight = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (can(low, values[mid])) {
                bestRight = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        if (bestRight != -1) {
            answer = min(answer, values[bestRight] - low);
        }
    }

    cout << answer << '\n';

    return 0;
}
