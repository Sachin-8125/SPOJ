#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int A;
        long long B;
        cin >> A >> B;

        vector<int> people(A);
        for (int &x : people) {
            cin >> x;
        }

        long long currSum = 0;
        int left = 0;

        long long bestPeople = 0;
        int bestStations = 0;

        for (int right = 0; right < A; ++right) {
            currSum += people[right];

            while (left <= right && currSum > B) {
                currSum -= people[left++];
            }

            int stations = right - left + 1;

            if (stations > bestStations || (stations == bestStations && currSum < bestPeople)) {
                bestStations = stations;
                bestPeople = currSum;
            }
        }

        cout << bestPeople << ' ' << bestStations << '\n';
    }

    return 0;
}