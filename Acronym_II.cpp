#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    set<string> skip = {"and","in","on","at","to","of","from","for","with"};
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        string A; cin >> A;
        int lenA = A.size();
        vector<string> words(N);
        vector<bool> canSkip(N);
        for (int i = 0; i < N; i++) {
            cin >> words[i];
            canSkip[i] = skip.count(words[i]) > 0;
        }
        vector<long long> dp(lenA + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < N; i++) {
            string s = words[i] + "#" + A;
            vector<int> z = zFunction(s);
            int wl = words[i].size();
            vector<long long> ndp(lenA + 1, 0);
            vector<long long> diff(lenA + 2, 0);
            for (int j = 0; j <= lenA; j++) {
                if (!dp[j]) continue;
                if (canSkip[i]) ndp[j] = (ndp[j] + dp[j]) % MOD;
                int L = (j < lenA) ? min(z[wl + 1 + j], wl) : 0;
                if (L > 0) {
                    diff[j + 1] = (diff[j + 1] + dp[j]) % MOD;
                    diff[j + L + 1] = (diff[j + L + 1] - dp[j] + MOD) % MOD;
                }
            }
            long long run = 0;
            for (int j = 0; j <= lenA; j++) {
                run = (run + diff[j]) % MOD;
                ndp[j] = (ndp[j] + run) % MOD;
            }
            dp = ndp;
        }
        cout << dp[lenA] << "\n";
    }
    return 0;
}