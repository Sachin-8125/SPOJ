#include <bits/stdc++.h>
using namespace std;

using Real = long double;
using Matrix = vector<Real>;

static Matrix multiply(const Matrix& a, const Matrix& b, int n) {
    Matrix c(n * n, 0);
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            Real x = a[i * n + k];
            if (x == 0) continue;
            for (int j = 0; j < n; ++j)
                c[i * n + j] += x * b[k * n + j];
        }
    }
    return c;
}

static vector<Real> multiplyVector(const vector<Real>& v, const Matrix& a, int n) {
    vector<Real> result(n, 0);
    for (int i = 0; i < n; ++i) {
        if (v[i] == 0) continue;
        for (int j = 0; j < n; ++j)
            result[j] += v[i] * a[i * n + j];
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    cout << fixed << setprecision(12);
    while (Q--) {
        int N, M, T;
        cin >> N >> M >> T;
        Real p[4], sum = 0;
        for (auto& x : p) {
            cin >> x;
            sum += x;
        }
        for (auto& x : p) x /= sum;
        vector<string> grid(N);
        for (auto& row : grid) cin >> row;

        const int dr[] = {-1, 0, 1, 0};
        const int dc[] = {0, 1, 0, -1};
        int start = -1;
        vector<int> demons;
        for (int r = 0; r < N; ++r) for (int c = 0; c < M; ++c) {
            if (grid[r][c] == '@') start = r * M + c;
            if (grid[r][c] == '*') demons.push_back(r * M + c);
        }
        int K = demons.size();
        vector<array<int, 4>> dest(N * M);
        for (int r = 0; r < N; ++r) for (int c = 0; c < M; ++c) {
            int u = r * M + c;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], col = c + dc[d];
                dest[u][d] = (nr < 0 || nr >= N || col < 0 || col >= M || grid[nr][col] == '#')
                    ? u : nr * M + col;
            }
        }

        Real answer = 1;
        for (int mask = 1; mask < (1 << K); ++mask) {
            vector<bool> forbidden(N * M, false);
            for (int j = 0; j < K; ++j) {
                if (mask & (1 << j)) forbidden[demons[j]] = true;
            }

            vector<int> id(N * M, -1), cells;
            id[start] = 0;
            cells.push_back(start);
            for (size_t i = 0; i < cells.size(); ++i) {
                int u = cells[i];
                for (int d = 0; d < 4; ++d) {
                    int v = dest[u][d];
                    if (p[d] > 0 && !forbidden[v] && id[v] == -1) {
                        id[v] = (int)cells.size();
                        cells.push_back(v);
                    }
                }
            }
            int n = cells.size();
            Matrix a(n * n, 0);
            for (int i = 0; i < n; ++i) {
                for (int d = 0; d < 4; ++d) {
                    int v = dest[cells[i]][d];
                    if (p[d] > 0 && !forbidden[v]) a[i * n + id[v]] += p[d];
                }
            }
            vector<Real> state(n, 0);
            state[0] = 1;
            int power = T;
            while (power > 0) {
                if (power & 1) state = multiplyVector(state, a, n);
                power >>= 1;
                if (power) a = multiply(a, a, n);
            }
            Real avoid = accumulate(state.begin(), state.end(), Real(0));
            if (__builtin_popcount((unsigned)mask) & 1) answer -= avoid;
            else answer += avoid;
        }
        answer = max(Real(0), min(Real(1), answer));
        cout << answer << '\n';
    }
}