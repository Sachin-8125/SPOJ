#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double triangleArea(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    double areaSquared = s * (s - a) * (s - b) * (s - c);
    return sqrt(max(0.0, areaSquared));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    cout << fixed << setprecision(4);

    while (N--) {
        double a, b, c, d, e, f;
        // WX, WY, WZ, XY, XZ, YZ
        cin >> a >> b >> c >> d >> e >> f;

        // Coordinates: W = (0,0,0), X = (a,0,0), Y = (u,v,0)
        double u = (a * a + b * b - d * d) / (2.0 * a);
        double vSquared = b * b - u * u;
        double v = sqrt(max(0.0, vSquared));

        // Z = (p,q,r)
        double p = (a * a + c * c - e * e) / (2.0 * a);
        double q = (b * b + c * c - f * f - 2.0 * u * p) / (2.0 * v);
        double rSquared = c * c - p * p - q * q;
        double height = sqrt(max(0.0, rSquared));

        double volume = a * v * height / 6.0;

        double surfaceArea = triangleArea(a, b, d) + triangleArea(a, c, e) + 
            triangleArea(b, c, f) + triangleArea(d, e, f);

        double inradius = 3.0 * volume / surfaceArea;
        cout << inradius << '\n';
    }

    return 0;
}