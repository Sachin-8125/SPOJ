#include <bits/stdc++.h>
using namespace std;

int w, h;
char grid[25][25];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// BFS from (sx, sy); returns distance grid (-1 = unreachable)
vector<vector<int>> bfs(int sx, int sy) {
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int,int>> q;
    dist[sy][sx] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            if (grid[ny][nx] == 'x') continue;
            if (dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({nx, ny});
        }
    }
    return dist;
}

int main() {
    while (scanf("%d %d", &w, &h) == 2 && (w || h)) {
        int rx = 0, ry = 0;
        vector<pair<int,int>> dirty; // (x, y)
        for (int y = 0; y < h; y++) {
            scanf("%s", grid[y]);
            for (int x = 0; x < w; x++) {
                if (grid[y][x] == 'o') { rx = x; ry = y; }
                else if (grid[y][x] == '*') dirty.push_back({x, y});
            }
        }
        int n = dirty.size();
        // d[i][j]: distance between point i and j (index n = robot)
        vector<vector<int>> d(n + 1, vector<int>(n + 1, -1));
        bool impossible = false;
        // BFS from robot
        {
            auto dist = bfs(rx, ry);
            for (int j = 0; j < n; j++) {
                d[n][j] = d[j][n] = dist[dirty[j].second][dirty[j].first];
                if (d[n][j] == -1) impossible = true;
            }
        }
        // BFS from each dirty tile
        for (int i = 0; i < n; i++) {
            auto dist = bfs(dirty[i].first, dirty[i].second);
            for (int j = 0; j < n; j++) {
                d[i][j] = dist[dirty[j].second][dirty[j].first];
                if (d[i][j] == -1) impossible = true;
            }
        }
        if (impossible) { printf("-1\n"); continue; }
        if (n == 0) { printf("0\n"); continue; }
        // TSP DP: dp[mask][i] = min moves, cleaned set mask, standing on tile i
        const int INF = 1e9;
        int full = (1 << n) - 1;
        vector<vector<int>> dp(1 << n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) dp[1 << i][i] = d[n][i];
        for (int mask = 1; mask <= full; mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i)) || dp[mask][i] == INF) continue;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;
                    int nmask = mask | (1 << j);
                    dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + d[i][j]);
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++) ans = min(ans, dp[full][i]);
        printf("%d\n", ans);
    }
    return 0;
}