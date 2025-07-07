#include <iostream>
#include <cmath>
using namespace std;

bool check(int a, int b, int x, int y) {
    if (x < a && y < b) return true;
    if (x >= a && y >= b) return false;
    double beta = atan2(y, x);
    double alpha = asin(static_cast<double>(b) / hypot(x, y)) - beta;
    if (alpha < 0) return false;
    double p = y * sin(alpha), q = sqrt(x * x + y * y - b * b);
    return (2 * p + q - a < 0);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        if (check(max(a, b), min(a, b), max(x, y), min(x, y)))
            cout << "Escape is possible." << endl;
        else
            cout << "Box cannot be dropped." << endl;
    }
    return 0;
}
