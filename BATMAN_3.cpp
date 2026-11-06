#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<long long> h(n);
        for (auto &x : h) cin >> x;

        vector<int> decEnd(n, 1), decStart(n, 1);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < i; ++k)
                if (h[k] > h[i]) decEnd[i] = max(decEnd[i], decEnd[k] + 1);

        for (int i = n - 1; i >= 0; --i)
            for (int k = i + 1; k < n; ++k)
                if (h[i] > h[k]) decStart[i] = max(decStart[i], decStart[k] + 1);

        int best = 0;
        for (int i = 0; i < n; ++i) best = max(best, decEnd[i]);

        if (m >= 0 && m < n) {
            int tail = 0;
            for (int j = m + 1; j < n; ++j) tail = max(tail, decStart[j]);
            best = max(best, decEnd[m] + tail);
        }
        cout << best << '\n';
    }
    return 0;
}