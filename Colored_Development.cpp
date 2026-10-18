#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int64 MOD = 1'000'000'007LL;

int64 modPow(int64 base, int64 exponent) {
    int64 result = 1;

    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % MOD;
        }

        base = base * base % MOD;
        exponent >>= 1;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int64 N, M;
        cin >> N >> M;

        int64 invN = modPow(N, MOD - 2);
        int64 probabilityNeverUsed =
            modPow((N - 1) * invN % MOD, M);

        int64 answer =
            N % MOD * ((1 - probabilityNeverUsed + MOD) % MOD) % MOD;

        cout << "Case " << tc << ": " << answer << '\n';
    }

    return 0;
}