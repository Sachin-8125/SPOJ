#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x, y;
    int index; // 1-based input index
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

double distanceBetween(const Point& a, const Point& b) {
    double dx = static_cast<double>(a.x - b.x);
    double dy = static_cast<double>(a.y - b.y);
    return hypot(dx, dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--) {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
            points[i].index = i + 1;
        }

        sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            if (a.x != b.x) return a.x < b.x;
            if (a.y != b.y) return a.y < b.y;
            return a.index < b.index;
        });

        // Keep only the first input occurrence of each location.
        vector<Point> uniquePoints;
        for (const Point& p : points) {
            if (uniquePoints.empty() ||
                p.x != uniquePoints.back().x ||
                p.y != uniquePoints.back().y) {
                uniquePoints.push_back(p);
            }
        }

        vector<Point> hull;

        if (uniquePoints.size() <= 2) {
            hull = uniquePoints;
        } else {
            vector<Point> lower, upper;

            for (const Point& p : uniquePoints) {
                while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) <= 0) {
                    lower.pop_back();
                }
                lower.push_back(p);
            }

            for (int i = static_cast<int>(uniquePoints.size()) - 1; i >= 0; --i) {
                const Point& p = uniquePoints[i];
                while (upper.size() >= 2 &&
                       cross(upper[upper.size() - 2], upper.back(), p) <= 0) {
                    upper.pop_back();
                }
                upper.push_back(p);
            }

            lower.pop_back();
            upper.pop_back();
            hull = lower;
            hull.insert(hull.end(), upper.begin(), upper.end());
        }

        double perimeter = 0.0;
        if (hull.size() >= 2) {
            for (size_t i = 0; i < hull.size(); ++i) {
                perimeter += distanceBetween(hull[i], hull[(i + 1) % hull.size()]);
            }
        }

        // Start at the bottommost point; break ties by choosing the leftmost.
        auto start = min_element(hull.begin(), hull.end(), [](const Point& a, const Point& b) {
            if (a.y != b.y) return a.y < b.y;
            return a.x < b.x;
        });

        rotate(hull.begin(), start, hull.end());

        cout << fixed << setprecision(2) << perimeter << '\n';
        for (size_t i = 0; i < hull.size(); ++i) {
            if (i) cout << ' ';
            cout << hull[i].index;
        }
        cout << "\n\n";
    }

    return 0;
}
