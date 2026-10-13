#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    cout << fixed << setprecision(3);

    while (n--) {
        double a, da, db, dc;
        cin >> a >> da >> db >> dc;

        double area = 1.5 * a * da;
        double b = 2.0 * area / (3.0 * db);
        double c = 2.0 * area / (3.0 * dc);

        double h = 3.0 * da;
        double x = (a * a + c * c - b * b) / (2.0 * a);

        double centroidX = (x + a) / 3.0;
        double centroidY = h / 3.0;

        double orthocenterX = x;
        double orthocenterY = x * (a - x) / h;

        double distance = hypot(orthocenterX - centroidX, orthocenterY - centroidY);

        cout << area << ' ' << distance << '\n';
    }

    return 0;
}