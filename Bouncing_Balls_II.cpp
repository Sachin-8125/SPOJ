#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

struct Ball {
    int64 x, y, vx, vy;
};

int64 position(int64 start, int64 velocity, int64 time, int64 length) {
    const i128 period = (i128)2 * length;
    i128 r = ((i128)start + (i128)velocity * time) % period;
    if (r < 0) r += period;
    if (r > length) r = period - r;
    return (int64)r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 width, height;
    if (!(cin >> width >> height)) return 0;

    int n;
    cin >> n;
    vector<Ball> balls(n);
    for (Ball &b : balls) {
        cin >> b.x >> b.y >> b.vx >> b.vy;
    }

    int queries;
    cin >> queries;
    vector<pair<int64, int64>> points(n);

    for (int q = 0; q < queries; ++q) {
        int64 time;
        cin >> time;

        for (int i = 0; i < n; ++i) {
            const Ball &b = balls[i];
            points[i] = {
                position(b.x, b.vx, time, width),
                position(b.y, b.vy, time, height)
            };
        }

        sort(points.begin(), points.end());
        if (q > 0) cout << '\n';
        for (const auto &p : points) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }
    return 0;
}