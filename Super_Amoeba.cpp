#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 1'000'000'007LL;

long long mod_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long M, N;
        cin >> M >> N;

        const long long mToN = mod_pow(M, N);
        const long long X = (mToN - 1 + MOD) % MOD * mod_pow(M - 1, MOD - 2) % MOD;
        const long long Y = mToN;

        cout << X << ' ' << Y << '\n';
    }
    return 0;
}