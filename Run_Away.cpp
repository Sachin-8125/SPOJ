#include <cstdio>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

static double HX[1005], HY[1005];
static int M;
static double RX, RY;

inline double mindist2(double px, double py) {
    double best = 1e300;
    for (int i = 0; i < M; ++i) {
        double dx = px - HX[i], dy = py - HY[i];
        double d = dx * dx + dy * dy;
        if (d < best) best = d;
    }
    return best;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    mt19937 rng(random_device{}());
    uniform_real_distribution<double> ur(0.0, 1.0);

    const int NP = 30;
    static double px[NP], py[NP];

    while (T--) {
        scanf("%lf %lf %d", &RX, &RY, &M);
        for (int i = 0; i < M; ++i)
            scanf("%lf %lf", &HX[i], &HY[i]);

        double seeds[][2] = {
            {0, 0}, {RX, 0}, {0, RY}, {RX, RY},
            {RX / 2, 0}, {RX / 2, RY}, {0, RY / 2}, {RX, RY / 2},
            {RX / 2, RY / 2}
        };

        int idx = 0;
        for (auto &s : seeds) {
            px[idx] = s[0];
            py[idx] = s[1];
            ++idx;
        }
        while (idx < NP) {
            px[idx] = ur(rng) * RX;
            py[idx] = ur(rng) * RY;
            ++idx;
        }

        double step = max(RX, RY);
        while (step > 1e-4) {
            for (int i = 0; i < NP; ++i) {
                double d = mindist2(px[i], py[i]);
                for (int k = 0; k < 25; ++k) {
                    double a = 2.0 * M_PI * ur(rng);
                    double nx = px[i] + cos(a) * step;
                    double ny = py[i] + sin(a) * step;
                    if (nx < 0 || nx > RX || ny < 0 || ny > RY) continue;
                    double nd = mindist2(nx, ny);
                    if (nd > d) {
                        d = nd;
                        px[i] = nx;
                        py[i] = ny;
                    }
                }
            }
            step *= 0.85;
        }

        int bi = 0;
        double bd = mindist2(px[0], py[0]);
        for (int i = 1; i < NP; ++i) {
            double d = mindist2(px[i], py[i]);
            if (d > bd) {
                bd = d;
                bi = i;
            }
        }

        double bx = floor(px[bi] * 10.0 + 0.5) / 10.0;
        double by = floor(py[bi] * 10.0 + 0.5) / 10.0;
        printf("The safest point is (%.1f, %.1f).\n", bx, by);
    }

    return 0;
}