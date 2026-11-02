#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long p;
    cin >> p;

    unsigned long long operations = 0;

    while (p != 1) {
        if (p & 1ULL) {
            p = (p << 1) ^ p ^ 1ULL;
        } else {
            p >>= 1;
        }

        ++operations;
    }

    cout << operations << '\n';
    return 0;
}