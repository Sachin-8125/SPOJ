#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;

// Euler's Totient Function
ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Modular exponentiation: computes (base^exp) % mod
ll modpow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Modular tetration: computes X^^N mod M
ll tetration(ll X, ll N, ll M) {
    if (M == 1) return 0;
    if (N == 0) return 1;
    if (N == 1) return X % M;
    ll t = tetration(X, N - 1, phi(M));
    // If X and M are not coprime, exponent may need to be increased by phi(M)
    // to avoid zero exponentiation
    if (t < 0) t += phi(M);
    return modpow(X, t, M);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        ll X, N, M;
        cin >> X >> N >> M;
        cout << tetration(X, N, M) << endl;
    }
    return 0;
}
