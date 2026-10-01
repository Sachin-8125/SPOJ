#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    map<int, int> firstOccurrence;
    firstOccurrence[0] = -1;

    long long prefixSum = 0;
    int minLength = INT_MAX;
    int resultLeft = -1, resultRight = -1;

    for (int i = 0; i < n; ++i) {
        prefixSum += a[i];
        int remainder = ((prefixSum % n) + n) % n;

        if (firstOccurrence.find(remainder) != firstOccurrence.end()) {
            int left = firstOccurrence[remainder] + 1;
            int right = i;
            int length = right - left + 1;

            if (length < minLength || (length == minLength && left < resultLeft)) {
                minLength = length;
                resultLeft = left;
                resultRight = right;
            }
        } else {
            firstOccurrence[remainder] = i;
        }
    }

    if (resultLeft == -1) {
        cout << -1 << '\n';
    } else {
        cout << resultLeft << ' ' << resultRight << '\n';
    }

    return 0;
}
