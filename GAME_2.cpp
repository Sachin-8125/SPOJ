#include <bits/stdc++.h>
using namespace std;

bool matches(const string& L, const string& S) {
    int n = L.size(), m = S.size();

    vector<char> prev(m + 1, 0), cur(m + 1, 0);

    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        cur[0] = (L[i - 1] == '*') ? prev[0] : 0;

        for (int j = 1; j <= m; j++) {
            char c = L[i - 1];
            if (c == '*') {
                cur[j] = prev[j] || cur[j - 1];
            } else if (c == '?') {
                cur[j] = prev[j] || prev[j - 1];
            } else {
                cur[j] = prev[j - 1] && (S[j - 1] == c);
            }
        }
        swap(prev, cur);
    }
    return prev[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string L, S;
        cin >> L >> S;
        cout << (matches(L, S) ? "Yes" : "No") << '\n';
    }
    return 0;
}