#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 7340033;
    const long long INV3 = 2446678; 

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        long long n;
        cin >> n;
        long long answer = 0;
        if (n >= 3) {
            n %= MOD;
            long long p = 12;
            p = (p * n - 56 + MOD) % MOD;
            p = (p * n + 66) % MOD;
            p = (p * n + 554) % MOD;
            p = (p * n - 2292 + MOD) % MOD;
            p = (p * n + 2424) % MOD;
            answer = p * INV3 % MOD;
        }
        cout << "Case " << tc << ": " << answer << '\n';
    }
}