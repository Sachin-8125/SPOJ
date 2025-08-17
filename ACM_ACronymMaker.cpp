#include <bits/stdc++.h>
using namespace std;

long long countSubseq(const string& A, int l, int r, const string& w) {
    // Count ways A[l..r] as subsequence in w (A uppercase, w lowercase)
    int m = r - l + 1, n = (int)w.size();
    if (m <= 0) return 0;
    vector<long long> dp(n + 1, 1), prev(n + 1, 0);
    // dp0: i=0 row is 1s
    for (int i = 1; i <= m; ++i) {
        prev.assign(n + 1, 0);
        char c = A[l + i - 1];
        for (int j = 1; j <= n; ++j) {
            prev[j] = prev[j - 1];
            if (toupper(w[j - 1]) == c) {
                prev[j] += dp[j - 1];
            }
        }
        dp.swap(prev);
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while ( (cin >> n) ) {
        if (n == 0) break;
        string dummy;
        string ign;
        unordered_set<string> stop;
        stop.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            cin >> ign;
            stop.insert(ign);
        }
        string line;
        getline(cin, line); // consume endline
        while (true) {
            if (!getline(cin, line)) return 0;
            if (line == "LAST CASE") break;
            // split first token (abbr) and the rest (phrase)
            stringstream ss(line);
            string abbr;
            ss >> abbr;
            string rest;
            vector<string> words;
            string token;
            // collect remaining as phrase then split by spaces
            vector<string> raw;
            while (ss >> token) raw.push_back(token);
            for (auto& w : raw) {
                if (!stop.count(w)) words.push_back(w);
            }
            int k = (int)words.size();
            int L = (int)abbr.size();

            vector<vector<long long>> ways(k, vector<long long>(L * L, -1));
            auto getWays = [&](int wi, int l, int r) -> long long {
                if (l > r) return 0;
                int idx = l * L + r;
                if (ways[wi][idx] != -1) return ways[wi][idx];
                return ways[wi][idx] = countSubseq(abbr, l, r, words[wi]);
            };
            // f[i][p]: first i words, first p letters used
            vector<vector<long long>> f(k + 1, vector<long long>(L + 1, 0));
            f[0] = 1;
            for (int i = 1; i <= k; ++i) {
                for (int p = 1; p <= L; ++p) {
                    long long sum = 0;
                    for (int t = 1; t <= p; ++t) {
                        long long left = f[i - 1][p - t];
                        if (left == 0) continue;
                        long long right = getWays(i - 1, p - t, p - 1);
                        if (right == 0) continue;
                        sum += left * right;
                    }
                    f[i][p] = sum;
                }
            }
            long long ans = f[k][L];
            if (ans == 0) {
                cout << abbr << " is not a valid abbreviation\n";
            } else {
                cout << abbr << " can be formed in " << ans << " ways\n";
            }
        }
    }
    return 0;
}
