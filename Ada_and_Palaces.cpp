#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr long long MOD = 1000000007LL;

    int T;
    cin >> T;

    vector<pair<int, int>> queries(T);
    for (int i = 0; i < T; ++i) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries.begin(), queries.end());

    vector<int> answer(T);

    long long dp[4] = {1, 1, 0, 0};
    int computed = 3;

    for (auto [n, index] : queries) {
        while (computed < n) {
            int k = ++computed;

            long long value = (k + 1LL) * dp[(k - 1) % 4] - (k - 2LL) * dp[(k - 2) % 4]
              - (k - 5LL) * dp[(k - 3) % 4] + (k - 3LL) * dp[(k - 4) % 4];

            value %= MOD;
            if (value < 0) value += MOD;

            dp[k % 4] = value;
        }

        answer[index] = static_cast<int>(dp[n % 4]);
    }

    for (int value : answer) {
        cout << value << '\n';
    }
}