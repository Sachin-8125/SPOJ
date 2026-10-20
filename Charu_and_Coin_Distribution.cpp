#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const ull MOD = 1000000007ULL;

ull pw(ull b, ull e) {
    ull r = 1;
    b %= MOD;
    while (e) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    int t;
    scanf("%d", &t);

    ull inv6 = pw(6, MOD - 2);

    while (t--) {
        ull n;
        scanf("%llu", &n);

        ull r = (n + 1) % MOD
              * ((n + 2) % MOD) % MOD
              * ((n + 3) % MOD) % MOD
              * inv6 % MOD;

        printf("%llu\n", r);
    }

    return 0;
}