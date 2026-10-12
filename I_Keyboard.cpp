#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int n, m;
        cin >> n >> m;  

        vector<char> keys(n), letters(m);
        for (char &key : keys) cin >> key;
        for (char &letter : letters) cin >> letter;

        vector<long long> freq(m);
        for (long long &f : freq) cin >> f;

        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
        vector<vector<int>> choice(n, vector<int>(m + 1, 0));
        dp[n][m] = 0;

        for (int j = n - 1; j >= 0; --j) {
            for (int i = m - 1; i >= 0; --i) {
                int keysAfter = n - j - 1;
                int maxTake = m - i - keysAfter; 
                for (int len = 1; len <= maxTake; ++len) {
                    long long cost = 0;
                    for (int q = 0; q < len; ++q)
                        cost += freq[i + q] * (q + 1LL);

                    if (dp[j + 1][i + len] != INF &&
                        cost + dp[j + 1][i + len] < dp[j][i]) {
                        dp[j][i] = cost + dp[j + 1][i + len];
                        choice[j][i] = len;
                    }
                }
            }
        }

        cout << "Keypad #" << tc << ":\n";
        int pos = 0;
        for (int j = 0; j < n; ++j) {
            cout << keys[j] << ": ";
            int len = choice[j][pos];
            for (int q = 0; q < len; ++q)
                cout << letters[pos + q];
            cout << '\n';
            pos += len;
        }
        cout << '\n';
    }

    return 0;
}