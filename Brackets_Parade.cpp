#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int max_val = 2005;
    vector<long long> fact(max_val);
    vector<long long> invFact(max_val);

    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < max_val; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[max_val - 1] = power(fact[max_val - 1], MOD - 2);
    for (int i = max_val - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    int n;
    if (cin >> n) {
        while (n--) {
            int m;
            cin >> m;
            
            int total_k = 0;
            vector<int> k(m);
            for (int i = 0; i < m; i++) {
                cin >> k[i];
                total_k += k[i];
            }

            long long ans = fact[2 * total_k];
            ans = (ans * invFact[total_k + 1]) % MOD;

            for (int i = 0; i < m; i++) {
                ans = (ans * invFact[k[i]]) % MOD;
            }

            cout << ans << "\n";
        }
    }

    return 0;
}