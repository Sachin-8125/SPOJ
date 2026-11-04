#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    while (N--) {
        string s;
        cin >> s;
        long long totalK = 0;
        for (char c : s) if (c == 'K') ++totalK;
        long long kBefore = 0;
        long long ans = 0;
        for (char c : s) {
            if (c == 'K') {
                ++kBefore;
            } else if (c == 'E') {
                long long kAfter = totalK - kBefore;
                ans += kBefore * kAfter;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}