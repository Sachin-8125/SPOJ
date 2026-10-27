#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int m, k;
        scanf("%d %d", &m, &k);
        vector<ll> p(m);
        ll lo = 0, hi = 0;
        for (auto& x : p) {
            scanf("%lld", &x);
            lo = max(lo, x);
            hi += x;
        }
        auto parts = [&](ll lim) {
            int c = 1;
            ll s = 0;
            for (ll x : p) {
                if (s + x > lim) {
                    c++;
                    s = x;
                } else {
                    s += x;
                }
            }
            return c;
        };
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (parts(mid) <= k) hi = mid;
            else lo = mid + 1;
        }
        ll lim = lo;
        vector<bool> sep(m, false);
        int left = k - 1;
        ll s = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (left > 0 && (s + p[i] > lim || i + 1 == left)) {
                sep[i] = true;
                left--;
                s = p[i];
            } else {
                s += p[i];
            }
        }
        string out;
        for (int i = 0; i < m; i++) {
            if (i) out += ' ';
            out += to_string(p[i]);
            if (sep[i]) out += " /";
        }
        puts(out.c_str());
    }
    return 0;
}