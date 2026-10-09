#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> queries(t);
    int maxN = 0;

    for (int& n : queries) {
        cin >> n;
        if (n > maxN) maxN = n;
    }

    const int limit = 500000;
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<long long> primes;
    for (int i = 2; i <= limit && primes.size() < 3ULL * maxN; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    for (int n : queries) {
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << ' ';

            long long term =
                primes[3 * i] * primes[3 * i + 1] + primes[3 * i + 2];

            cout << term;
        }
        cout << '\n';
    }

    return 0;
}