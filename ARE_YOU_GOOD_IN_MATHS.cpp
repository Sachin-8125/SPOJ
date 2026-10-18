#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    cout << fixed << setprecision(6);

    while (T--) {
        long long H;
        long long A;

        cin >> H >> A;

        long double h = static_cast<long double>(H);
        long double area = static_cast<long double>(A);

        long double discriminant = h * h - 4.0L * area;

        long double tolerance = 1e-18L * max(1.0L, h * h);

        if (discriminant < -tolerance) {
            cout << "-1\n";
            continue;
        }

        if (discriminant < 0) {
            discriminant = 0;
        }

        long double sumOfLegs = sqrtl(h * h + 4.0L * area);
        long double differenceOfLegs = sqrtl(discriminant);

        long double leg1 = (sumOfLegs - differenceOfLegs) / 2.0L;
        long double leg2 = (sumOfLegs + differenceOfLegs) / 2.0L;

        cout << leg1 << ' ' << leg2 << ' ' << h << '\n';
    }

    return 0;
}