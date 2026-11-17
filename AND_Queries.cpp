#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

static const long long MOD_SEED = 2117566807LL;

static int pop[1 << 18];
static long long C[19][19];
static long long g[1 << 18];
static long long F[1 << 18];

void precompute() {
    pop[0] = 0;
    for (int i = 1; i < (1 << 18); i++) {
        pop[i] = pop[i >> 1] + (i & 1);
    }
    for (int i = 0; i <= 18; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

void solve(int tc) {
    long long seed;
    int N, Q, mod_A, mod_V, mod_K;
    if (!(cin >> seed >> N >> Q >> mod_A >> mod_V >> mod_K)) return;

    auto next_rnd = [&]() -> long long {
        seed = (seed * 997LL + 29LL) % MOD_SEED;
        return seed;
    };

    vector<int> A(N);
    int maxVal = 0;
    for (int i = 0; i < N; i++) {
        A[i] = (int)(next_rnd() % mod_A);
        if (A[i] > maxVal) maxVal = A[i];
    }

    int B = 0;
    while ((1 << B) <= maxVal) B++;
    int size = 1 << B;
    int mask_limit = size - 1;

    vector<vector<int>> queriesByK(mod_K);
    for (int i = 0; i < Q; i++) {
        int v = (int)(next_rnd() % mod_V);
        int k = (int)(next_rnd() % mod_K);
        if (k <= B) {
            queriesByK[k].push_back(v & mask_limit);
        }
    }

    fill(g, g + size, 0LL);
    for (int i = 0; i < N; i++) {
        g[A[i]]++;
    }

    for (int len = 1; len < size; len <<= 1) {
        for (int i = 0; i < size; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                g[i + j] += g[i + len + j];
            }
        }
    }

    long long total_ans = 0;

    for (int k = 0; k < mod_K; k++) {
        if (k > B || queriesByK[k].empty()) continue;

        for (int mask = 0; mask < size; mask++) {
            int p = pop[mask];
            if (p < k) {
                F[mask] = 0;
            } else {
                long long ways = C[p][k];
                if ((p - k) & 1) {
                    F[mask] = -ways * g[mask];
                } else {
                    F[mask] = ways * g[mask];
                }
            }
        }

        for (int len = 1; len < size; len <<= 1) {
            for (int i = 0; i < size; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    F[i + len + j] += F[i + j];
                }
            }
        }

        for (int v : queriesByK[k]) {
            total_ans += F[v];
        }
    }

    cout << "Case " << tc << ": " << total_ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int T;
    if (cin >> T) {
        for (int tc = 1; tc <= T; tc++) {
            solve(tc);
        }
    }

    return 0;
}