#include <iostream>
using namespace std;

long long binomial(int n, int k) {
    k = min(k, n - k);
    long long result = 1;

    for (int i = 1; i <= k; ++i) {
        result = result * (n - k + i) / i;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;

    while (cin >> A >> B && !(A == -1 && B == -1)) {
        int total = A + B;
        long long possibilities = binomial(total, A);

        if (possibilities == total) {
            cout << A << "+" << B << "=" << total << '\n';
        } else {
            cout << A << "+" << B << "!=" << total << '\n';
        }
    }

    return 0;
}