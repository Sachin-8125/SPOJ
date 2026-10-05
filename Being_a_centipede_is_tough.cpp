#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll power(ll b, ll e) {
    ll r = 1; b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ll n;
    if (!(cin >> n)) return 0;

    ll fact2n = 1;
    for (ll i = 1; i <= 2 * n; i++) fact2n = fact2n * i % MOD;

    ll factn = 1;
    for (ll i = 1; i <= n; i++) factn = factn * i % MOD;

    ll inv2n = power(power(2, n), MOD - 2);   

    ll ans = fact2n * inv2n % MOD;
    ans = ans * factn % MOD;
    ans = ans * factn % MOD;

    cout << ans << endl;
    return 0;
}