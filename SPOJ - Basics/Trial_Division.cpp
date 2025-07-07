//  Trial Division

#include <iostream>
#include <vector>
using namespace std;

vector<int> factorize(int n) {
    vector<int> factors;
    if (n == 1) {
        return factors; // 1 has no prime factors
    }
    for (int p = 2; p * p <= n; ++p) {
        while (n % p == 0) {
            factors.push_back(p);
            n /= p;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> factors = factorize(n);
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i > 0) cout << " ";
            cout << factors[i];
        }
        cout << endl;
    }
    return 0;
}
