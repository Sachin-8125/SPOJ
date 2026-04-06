#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Direction constants for 4-way movement
const int DX[] = {1, -1, 0, 0};
const int DY[] = {0, 0, 1, -1};

struct Point {
    int r, c;
};

class MissionSolver {
    int Rows, Cols;
    vector<vector<int>> heights;
    Point start, end;

    // Helper math functions for visibility logic
    int calc(int dx, int dy, int i) {
        return dx == 0 ? 0 : (dy * i + dx - 1) / dx / 2;
    }

    int calcc(int dx, int dy, int i) {
        return dx == 0 ? 0 : (dy * i + dx) / dx / 2;
    }

    // Line-of-sight check between two points
    bool is_visible(int r1, int c1, int r2, int c2) {
        int z1 = heights[r1][c1] * 2 + 1;
        int dx = (r2 - r1) * 2, dy = (c2 - c1) * 2;
        int dz = (heights[r2][c2] - heights[r1][c1]) * 2;
        int sx = abs(dx), sy = abs(dy);
        int xsgn = (dx > 0) ? 1 : -1, ysgn = (dy > 0) ? 1 : -1;

        if (dx) {
            for (int i = 1; i < sx; i += 2) {
                int nx = r1 + (i / 2) * xsgn;
                int ny = c1 + calc(sx, sy, i) * ysgn;
                int ty = c1 + calcc(sx, sy, i) * ysgn;
                if (dz * i < (heights[nx][ny] * 2 - z1) * sx || 
                    dz * i < (heights[nx + xsgn][ty] * 2 - z1) * sx) return false;
            }
        }
        if (dy) {
            for (int i = 1; i < sy; i += 2) {
                int ny = c1 + (i / 2) * ysgn;
                int nx = r1 + calc(sy, sx, i) * xsgn;
                int tx = r1 + calcc(sy, sx, i) * xsgn;
                if (dz * i < (heights[nx][ny] * 2 - z1) * sy || 
                    dz * i < (heights[tx][ny + ysgn] * 2 - z1) * sy) return false;
            }
        }
        return true;
    }

    bool can_move(int r, int c, int dr, int dc) {
        int diff = heights[dr][dc] - heights[r][c];
        // Height constraint: max 1 unit up, max 3 units down
        if (diff < -3 || diff > 1) return false;
        // Must be visible from either start or end point
        return is_visible(dr, dc, start.r, start.c) || is_visible(dr, dc, end.r, end.c);
    }

public:
    void solve() {
        if (!(cin >> Rows >> Cols)) return;
        heights.assign(Rows, vector<int>(Cols));
        for (int i = 0; i < Rows; ++i)
            for (int j = 0; j < Cols; ++j)
                cin >> heights[i][j];

        cin >> start.r >> start.c >> end.r >> end.c;
        --start.r; --start.c; --end.r; --end.c; // 0-indexing

        if (start.r == end.r && start.c == end.c) {
            cout << "The shortest path is 0 steps long." << endl;
            return;
        }

        // BFS Setup
        queue<Point> q;
        vector<vector<int>> dist(Rows, vector<int>(Cols, -1));
        
        q.push(start);
        dist[start.r][start.c] = 0;

        while (!q.empty()) {
            Point curr = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + DX[i];
                int nc = curr.c + DY[i];

                if (nr >= 0 && nr < Rows && nc >= 0 && nc < Cols && dist[nr][nc] == -1) {
                    if (can_move(curr.r, curr.c, nr, nc)) {
                        dist[nr][nc] = dist[curr.r][curr.c] + 1;
                        if (nr == end.r && nc == end.c) {
                            cout << "The shortest path is " << dist[nr][nc] << " steps long." << endl;
                            return;
                        }
                        q.push({nr, nc});
                    }
                }
            }
        }
        cout << "Mission impossible!" << endl;
    }
};

int main() {
    // Faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    if (!(cin >> testCases)) return 0;
    while (testCases--) {
        MissionSolver solver;
        solver.solve();
    }
    return 0;
}