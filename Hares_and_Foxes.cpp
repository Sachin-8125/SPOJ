#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-12L;

enum Result {
    BALANCE,
    HARES_DIE_FOXES_GROW,
    HARES_GROW_FOXES_DIE,
    BOTH_DIE,
    BOTH_GROW,
    CHAOS
};

bool isZero(long double x) {
    return fabsl(x) < EPS;
}

Result classifySigns(long double h, long double f) {
    bool hPos = h > EPS;
    bool fPos = f > EPS;
    bool hNeg = h < -EPS;
    bool fNeg = f < -EPS;

    if (hNeg && fPos)
        return HARES_DIE_FOXES_GROW;

    if (hPos && fNeg)
        return HARES_GROW_FOXES_DIE;

    if (hNeg && fNeg)
        return BOTH_DIE;

    if (hPos && fPos)
        return BOTH_GROW;

    return CHAOS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long double a, b, c, d, h0, f0;
        cin >> a >> b >> c >> d >> h0 >> f0;

        if (isZero(h0) && isZero(f0)) {
            cout << "Ecological balance will develop.\n";
            continue;
        }

        long double trace = a + c;
        long double determinant = a * c + b * d;

        long double discriminant =
            trace * trace - 4.0L * determinant;

        if (discriminant < -EPS) {
            long double radius = sqrtl(determinant);

            if (radius < 1.0L - EPS) {
                cout << "Ecological balance will develop.\n";
            } else {
                cout << "Chaos will develop.\n";
            }
            continue;
        }

        if (discriminant < 0)
            discriminant = 0;

        long double sqrtDiscriminant = sqrtl(discriminant);
        long double lambda1 = (trace + sqrtDiscriminant) / 2.0L;
        long double lambda2 = (trace - sqrtDiscriminant) / 2.0L;

        long double r1 = fabsl(lambda1);
        long double r2 = fabsl(lambda2);
        long double dominant = max(r1, r2);

        if (dominant < 1.0L - EPS) {
            cout << "Ecological balance will develop.\n";
            continue;
        }

        if (lambda1 < -1.0L + EPS || lambda2 < -1.0L + EPS) {
            cout << "Chaos will develop.\n";
            continue;
        }

        if (isZero(lambda1 - lambda2)) {
            if (lambda1 > 1.0L + EPS) {
                long double x, y;

                if (isZero(b) && !isZero(a - lambda1)) {
                    x = 1;
                    y = (lambda1 - a) / (-b == 0 ? 1 : -b);
                } else if (!isZero(b)) {
                    x = b;
                    y = a - lambda1;
                } else if (!isZero(d)) {
                    x = lambda1 - c;
                    y = d;
                } else {
                    x = h0;
                    y = f0;
                }

                long double coefficient =
                    h0 * x + f0 * y;

                if (isZero(coefficient)) {
                    cout << "Chaos will develop.\n";
                } else {
                    cout << "Chaos will develop.\n";
                }
            } else {
                cout << "Chaos will develop.\n";
            }
            continue;
        }

        long double lambda = (r1 > r2 ? lambda1 : lambda2);

        if (lambda < 1.0L - EPS) {
            cout << "Ecological balance will develop.\n";
            continue;
        }

        long double vx, vy;

        if (!isZero(b)) {
            vx = b;
            vy = a - lambda;
        } else if (!isZero(d)) {
            vx = lambda - c;
            vy = d;
        } else {
            vx = 1;
            vy = 0;
        }

        long double coefficient;

        if (!isZero(vx) || !isZero(vy)) {
            long double other = (lambda == lambda1 ? lambda2 : lambda1);

            long double ux, uy;
            if (!isZero(b)) {
                ux = b;
                uy = a - other;
            } else if (!isZero(d)) {
                ux = other - c;
                uy = d;
            } else {
                ux = 0;
                uy = 1;
            }

            long double det = vx * uy - ux * vy;

            if (isZero(det)) {
                coefficient = 0;
            } else {
                coefficient = (h0 * uy - f0 * ux) / det;
            }
        } else {
            coefficient = 0;
        }

        if (isZero(coefficient)) {
            lambda = (lambda == lambda1 ? lambda2 : lambda1);

            if (fabsl(lambda) < 1.0L - EPS) {
                cout << "Ecological balance will develop.\n";
            } else if (lambda < -1.0L + EPS) {
                cout << "Chaos will develop.\n";
            } else {
                cout << "Chaos will develop.\n";
            }
            continue;
        }

        long double finalH = coefficient * vx;
        long double finalF = coefficient * vy;

        Result result = classifySigns(finalH, finalF);

        switch (result) {
            case HARES_DIE_FOXES_GROW:
                cout << "Hares will die out while foxes will overgrow.\n";
                break;

            case HARES_GROW_FOXES_DIE:
                cout << "Hares will overgrow while foxes will die out.\n";
                break;

            case BOTH_DIE:
                cout << "Both hares and foxes will die out.\n";
                break;

            case BOTH_GROW:
                cout << "Both hares and foxes will overgrow.\n";
                break;

            default:
                cout << "Chaos will develop.\n";
                break;
        }
    }

    return 0;
}
