#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 1000000007LL;
static constexpr int MAX_N = 200000;

long long modpow(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> factorial(MAX_N + 1, 1);
    for (int i = 1; i <= MAX_N; ++i)
        factorial[i] = factorial[i - 1] * i % MOD;

    vector<long long> answer(MAX_N + 1, -1);
    int n;
    while (cin >> n) {
        if (answer[n] == -1) {
            long long sum = 0;
            for (int i = 1; i <= n / 2; ++i) {
                int j = n - i;
                long long trees = modpow(i, j - 1) * modpow(j, i - 1) % MOD;
                sum = (sum + (i == j ? trees : 2 * trees)) % MOD;
            }
            answer[n] = factorial[n] * sum % MOD;
        }
        cout << answer[n] << '\n';
    }
}