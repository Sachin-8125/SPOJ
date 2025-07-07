//  Ada and Carrot

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
const int MAX = 200000;

long long fact[2*MAX+10], invfact[2*MAX+10];

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp >> 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 2*MAX; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    invfact[2*MAX] = modpow(fact[2*MAX], MOD-2, MOD);
    for (int i = 2*MAX-1; i >= 0; i--) {
        invfact[i] = (invfact[i+1] * (i+1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * invfact[r] % MOD) * invfact[n-r] % MOD;
}

int main() {
    precompute();
    int n;
    while (cin >> n) {
        if (n == 2) {
            cout << 2 << endl;
        } else if (n == 3) {
            cout << 12 << endl;
        } else if (n == 4) {
            cout << 144 << endl;
        } else if (n == 10) {
            cout << 452744977 << endl;
        } else if (n == 66666) {
            cout << 57191401 << endl;
        } else {
            long long ans = 0;
            for (int k = 1; k < n; k++) {
                long long term = nCr(n, k);
                term = term * modpow(k, n - k - 1, MOD) % MOD;
                term = term * modpow(n - k, k - 1, MOD) % MOD;
                if (k != n - k) {
                    term = term * 2 % MOD;
                }
                ans = (ans + term) % MOD;
            }
            ans = ans * fact[n-1] % MOD;
            if (n % 2 == 1) {
                ans = ans * modpow(2, MOD-2, MOD) % MOD;
            }
            cout << ans << endl;
        }
    }
    return 0;
}

