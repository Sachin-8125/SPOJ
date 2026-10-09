#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int caseNumber = 1; caseNumber <= T; ++caseNumber) {
        int N;
        cin >> N;

        int farthestIndex = 1;
        long long farthestDistanceSquared = -1;

        for (int i = 1; i <= N; ++i) {
            long long x, y;
            cin >> x >> y;

            long long distanceSquared = x * x + y * y;

            if (distanceSquared > farthestDistanceSquared) {
                farthestDistanceSquared = distanceSquared;
                farthestIndex = i;
            }
        }

        cout << "Case " << caseNumber << ": " << farthestIndex << '\n';
    }

    return 0;
}
