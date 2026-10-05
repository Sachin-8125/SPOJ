#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MOD = 100'000'000;
    int n;

    while (cin >> n && n != -1) {
        vector<pair<long long, long long>> intervals(n); 
        for (auto &[start, end] : intervals) {
            cin >> start >> end;
        }

        sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });

        vector<long long> ends(n);
        vector<int> prefix(n + 1, 0);
        long long total = 0;

        for (int i = 0; i < n; ++i) {
            const auto [start, end] = intervals[i];
            ends[i] = end;

            int compatible = upper_bound(ends.begin(), ends.begin() + i, start) - ends.begin();

            int ways = (1 + prefix[compatible]) % MOD;
            total = (total + ways) % MOD;
            prefix[i + 1] = (prefix[i] + ways) % MOD;
        }

        cout << setw(8) << setfill('0') << total << '\n';
    }

    return 0;
}