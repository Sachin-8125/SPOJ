#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    while (getline(cin, line)) {
        if (line != "P")
            continue;

        long long x = 0, y = 0;
        long long twiceArea = 0;
        long long boundary = 0;

        while (getline(cin, line) && line != "K") {
            char move = line[0];

            long long nx = x;
            long long ny = y;

            if (move == 'N') {
                ++ny;
            } else if (move == 'S') {
                --ny;
            } else if (move == 'E') {
                ++nx;
            } else if (move == 'W') {
                --nx;
            }

            twiceArea += x * ny - nx * y;

            ++boundary;
            x = nx;
            y = ny;
        }

        long long area2 = llabs(twiceArea);

        long long answer = (area2 + boundary + 2) / 2;

        cout << answer << '\n';
    }

    return 0;
}