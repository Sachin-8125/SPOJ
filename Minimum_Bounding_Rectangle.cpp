#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int minX = 1 << 29, minY = 1 << 29;
        int maxX = -(1 << 29), maxY = -(1 << 29);

        for (int i = 0; i < n; ++i) {
            char obj;
            cin >> obj;
            if (obj == 'p') {
                int x, y;
                cin >> x >> y;
                minX = min(minX, x);
                maxX = max(maxX, x);
                minY = min(minY, y);
                maxY = max(maxY, y);
            } else if (obj == 'c') {
                int x, y, r;
                cin >> x >> y >> r;
                int left = x - r, right = x + r;
                int bottom = y - r, top = y + r;
                minX = min(minX, left);
                maxX = max(maxX, right);
                minY = min(minY, bottom);
                maxY = max(maxY, top);
            } else if (obj == 'l') {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                minX = min(minX, min(x1, x2));
                maxX = max(maxX, max(x1, x2));
                minY = min(minY, min(y1, y2));
                maxY = max(maxY, max(y1, y2));
            }
        }
        cout << minX << " " << minY << " " << maxX << " " << maxY << endl;
    }
    return 0;
}