#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

static const int WORDS = 16;

int R, C, D, W;
static ull lockRow[10005][WORDS];
static vector<array<ull, WORDS>> keyShift;
static char vis[10105][1005];

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    static char buf[2005];

    while (T--) {
        scanf("%d %d", &R, &C);
        vector<string> key(R);
        for (int i = 0; i < R; i++) {
            scanf("%s", buf);
            key[i] = buf;
        }

        scanf("%d %d", &D, &W);
        for (int r = 0; r < D; r++) {
            scanf("%s", buf);
            memset(lockRow[r], 0, sizeof(lockRow[r]));
            for (int c = 0; c < W; c++)
                if (buf[c] == '#') lockRow[r][c >> 6] |= 1ULL << (c & 63);
        }

        if (C > W) {
            printf("The key falls to depth 0.\n");
            continue;
        }

        int nx = W - C + 1;
        keyShift.assign((size_t)R * nx, array<ull, WORDS>());
        for (int i = 0; i < R; i++) {
            for (int x = 0; x < nx; x++) {
                array<ull, WORDS> &a = keyShift[(size_t)i * nx + x];
                a.fill(0);
                for (int j = 0; j < C; j++)
                    if (key[i][j] == '#') {
                        int c = x + j;
                        a[c >> 6] |= 1ULL << (c & 63);
                    }
            }
        }

        int maxD = D + R;
        for (int d = 0; d <= maxD; d++) memset(vis[d], 0, nx);

        auto valid = [&](int d, int x) -> bool {
            int lo = max(0, R - d), hi = min(R - 1, D - 1 - (d - R));
            int w0 = x >> 6, w1 = (x + C - 1) >> 6;
            for (int i = lo; i <= hi; i++) {
                const ull *lr = lockRow[d - R + i];
                const array<ull, WORDS> &a = keyShift[(size_t)i * nx + x];
                for (int w = w0; w <= w1; w++)
                    if (lr[w] & a[w]) return false;
            }
            return true;
        };

        vector<pair<int, int>> q;
        q.reserve(1 << 16);
        for (int x = 0; x < nx; x++) {
            vis[0][x] = 1;
            q.push_back({0, x});
        }

        int best = 0;
        bool through = false;

        while (!q.empty()) {
            auto [d, x] = q.back();
            q.pop_back();
            if (d > best) best = d;
            if (d >= maxD) {
                through = true;
                break;
            }

            int nd[3] = {d, d, d + 1}, nxs[3] = {x - 1, x + 1, x};
            for (int k = 0; k < 3; k++) {
                int dd = nd[k], xx = nxs[k];
                if (xx < 0 || xx >= nx || dd > maxD) continue;
                if (vis[dd][xx]) continue;
                if (!valid(dd, xx)) continue;
                vis[dd][xx] = 1;
                q.push_back({dd, xx});
            }
        }

        if (through)
            printf("The key can fall through.\n");
        else
            printf("The key falls to depth %d.\n", best);
    }

    return 0;
}