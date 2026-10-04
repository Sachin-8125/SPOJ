#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        int N;
        scanf("%d", &N);
        vector<double> a(N), b(N), c(N), d(N), p(N);
        for (int i = 0; i < N; i++) {
            double x, y, z, pi;
            scanf("%lf %lf %lf %lf", &x, &y, &z, &pi);
            p[i] = pi;
            a[i] = x + y + z;
            b[i] = x + y - z;
            c[i] = x - y + z;
            d[i] = -x + y + z;
        }

        double lo = 0, hi = 3e6;
        for (int iter = 0; iter < 100; iter++) {
            double mid = (lo + hi) / 2.0;

            double Amin = -1e18, Amax = 1e18;
            double Bmin = -1e18, Bmax = 1e18;
            double Cmin = -1e18, Cmax = 1e18;
            double Dmin = -1e18, Dmax = 1e18;

            for (int i = 0; i < N; i++) {
                double r = mid * p[i];
                Amin = max(Amin, a[i] - r);
                Amax = min(Amax, a[i] + r);
                Bmin = max(Bmin, b[i] - r);
                Bmax = min(Bmax, b[i] + r);
                Cmin = max(Cmin, c[i] - r);
                Cmax = min(Cmax, c[i] + r);
                Dmin = max(Dmin, d[i] - r);
                Dmax = min(Dmax, d[i] + r);
            }

            bool feasible = (Amin <= Amax && Bmin <= Bmax && Cmin <= Cmax && Dmin <= Dmax);

            if (feasible) {
                double sumMin = Bmin + Cmin + Dmin;
                double sumMax = Bmax + Cmax + Dmax;
                if (sumMin > Amax || sumMax < Amin) feasible = false;
            }

            if (feasible) hi = mid;
            else lo = mid;
        }

        printf("Case #%d: %f\n", cas, hi);
    }
    return 0;
}