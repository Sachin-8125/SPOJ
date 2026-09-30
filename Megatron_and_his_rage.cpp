#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int P;
        long long M;
        cin >> P >> M;

        vector<int> autobots(P);
        for (int i = 0; i < P; ++i) {
            cin >> autobots[i];
        }

        long long currentSum = 0;
        long long bestSum = 0;
        int left = 0;
        int bestLength = 0;

        for (int right = 0; right < P; ++right) {
            currentSum += autobots[right];

            while (left <= right && currentSum > M) {
                currentSum -= autobots[left];
                ++left;
            }

            int currentLength = right - left + 1;

            if (currentLength > bestLength) {
                bestLength = currentLength;
                bestSum = currentSum;
            } else if (currentLength == bestLength && currentLength > 0 && currentSum < bestSum) {
                bestSum = currentSum;
            }
        }

        cout << bestSum << ' ' << bestLength << '\n';
    }

    return 0;
}