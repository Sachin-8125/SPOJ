#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    int r, c;
};

int P, Q;
int Z[205][205];           // Terrain height
int dist_map[205][205];    // Distance from start
int vis_memo[205][205][2]; 

int R1, C1, R2, C2; 

bool check_los(int r_start, int c_start, int r_end, int c_end) {
    if (r_start == r_end && c_start == c_end) return true;

    double z_start = Z[r_start][c_start];
    double z_end = Z[r_end][c_end];
    
    int dr = r_end - r_start;
    int dc = c_end - c_start;
    
    int cur_r = r_start;
    int cur_c = c_start;
    
    // Determine step direction
    int step_r = (dr > 0) ? 1 : ((dr < 0) ? -1 : 0);
    int step_c = (dc > 0) ? 1 : ((dc < 0) ? -1 : 0);
    
    double t_curr = 0.0;
    
    double t_next_r = 1e9;
    double t_next_c = 1e9;
    double dt_r = 1e9;
    double dt_c = 1e9;
    
    if (step_r != 0) {
        dt_r = 1.0 / abs(dr);
        t_next_r = 0.5 * dt_r; 
    }
    if (step_c != 0) {
        dt_c = 1.0 / abs(dc);
        t_next_c = 0.5 * dt_c;
    }
    
    const double EPS = 1e-9;
    
    // Grid Traversal
    while (t_curr < 1.0 - EPS) {
        double t_exit;
        int next_r_inc = 0;
        int next_c_inc = 0;
        
        // Find which boundary is closer
        if (abs(t_next_r - t_next_c) < EPS) {
            // Corner crossing: pass through vertex
            t_exit = t_next_r;
            next_r_inc = step_r;
            next_c_inc = step_c;
            t_next_r += dt_r;
            t_next_c += dt_c;
        } else if (t_next_r < t_next_c) {
            // Crossing horizontal boundary (row change)
            t_exit = t_next_r;
            next_r_inc = step_r;
            t_next_r += dt_r;
        } else {
            // Crossing vertical boundary (column change)
            t_exit = t_next_c;
            next_c_inc = step_c;
            t_next_c += dt_c;
        }
        
        // Clamp to 1.0
        if (t_exit > 1.0 - EPS) t_exit = 1.0;
        if (!((cur_r == r_start && cur_c == c_start) || (cur_r == r_end && cur_c == c_end))) {
             // Calculate ray height at entry (t_curr) and exit (t_exit) of the cell
             double h1 = (z_start + 0.5) + t_curr * (z_end - z_start);
             double h2 = (z_start + 0.5) + t_exit * (z_end - z_start);
             
             // Since the segment is linear, the minimum height is at one of the endpoints.
             double min_h = min(h1, h2);
             if (min_h < Z[cur_r][cur_c] - EPS) return false;
        }
        
        // Advance to next cell
        cur_r += next_r_inc;
        cur_c += next_c_inc;
        t_curr = t_exit;
    }
    
    return true;
}

// Helper to check visibility to specific BTS with memoization
bool can_see(int r, int c, int target_idx) {
    if (vis_memo[r][c][target_idx] != -1) return vis_memo[r][c][target_idx];
    
    int tr = (target_idx == 0) ? R1 : R2;
    int tc = (target_idx == 0) ? C1 : C2;
    
    bool res = check_los(r, c, tr, tc);
    vis_memo[r][c][target_idx] = res ? 1 : 0;
    return res;
}

void solve() {
    cin >> P >> Q;
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < Q; ++j) {
            cin >> Z[i][j];
            dist_map[i][j] = -1;
            vis_memo[i][j][0] = -1;
            vis_memo[i][j][1] = -1;
        }
    }
    cin >> R1 >> C1 >> R2 >> C2;
    // Convert 1-based input to 0-based
    R1--; C1--; R2--; C2--;
    
    queue<Point> q;
    q.push({R1, C1});
    dist_map[R1][C1] = 0;
    
    // Direction arrays: N, S, W, E
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(!q.empty()){
        Point curr = q.front();
        q.pop();
        
        // If we reached the second BTS
        if (curr.r == R2 && curr.c == C2) {
            cout << "The shortest path is " << dist_map[curr.r][curr.c] << " steps long." << endl;
            return;
        }
        
        int d = dist_map[curr.r][curr.c];
        
        for(int i=0; i<4; ++i){
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            // Bounds check
            if (nr >= 0 && nr < P && nc >= 0 && nc < Q) {
                // If not visited
                if (dist_map[nr][nc] == -1) {
                    int diff = Z[nr][nc] - Z[curr.r][curr.c];
                    if (diff <= 1 && diff >= -3) {
                        if (can_see(nr, nc, 0) || can_see(nr, nc, 1)) {
                            dist_map[nr][nc] = d + 1;
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }
    }
    
    cout << "Mission impossible!" << endl;
}

int main() {
    // Fast I/O is crucial for large number of test cases
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}