//  Painting Hat

#include<bits/stdc++.h>

using namespace std;

double solve(double R, double H) {
    double s = sqrt(R*R + H*H);
    double full_volume = (1.0/3.0) * R * R * H;
    double full_area = R * s;

    if (full_volume < full_area) {
        return H;
    }

    double total_area = 2.0 * M_PI * R * s;
    double low = 0.0;
    double high = H;

    for (int i = 0; i < 100; i++) {
        double mid = (low + high) / 2.0;
        double r = R * mid / H;
        double l = sqrt(r*r + mid*mid);
        double paint_volume = (1.0/3.0) * M_PI * r * r * mid;
        double submerged_area = M_PI * r * l;
        double paint_area = total_area - submerged_area;
        double f = paint_volume - paint_area;

        if (f < 0) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return (low + high) / 2.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    cout << fixed << setprecision(6);
    for (int i = 0; i < N; i++) {
        double R, H;
        cin >> R >> H;
        double h = solve(R, H);
        cout << h << endl;
    }

    return 0;
}

