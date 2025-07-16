#include <iostream>
#include <vector>
using namespace std;

// Function to count distinct prime factors
int countDistinctPrimeFactors(int n) {
    int count = 0;
    for (int i = 2; i * i <= n && n > 1; ++i) {
        if (n % i == 0) {
            ++count;
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1) ++count; // n is prime
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute first 1000 lucky numbers
    vector<int> lucky;
    for (int i = 2; lucky.size() < 1000; ++i) {
        if (countDistinctPrimeFactors(i) >= 3)
            lucky.push_back(i);
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << lucky[n - 1] << '\n';
    }

    return 0;
}
