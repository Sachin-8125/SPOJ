#include <algorithm>
#include <iostream>

long long gcd(long long a, long long b) {
    while (b) { long long t = b; b = a % b; a = t; }
    return a;
}

using namespace std;

long long pour(int fromCapacity, int toCapacity, int target) {
    int from = 0;
    int to = 0;
    long long steps = 0;

    while (from != target && to != target) {
        if (from == 0) {
            from = fromCapacity;
        } else if (to == toCapacity) {
            to = 0;
        } else {
            int amount = min(from, toCapacity - to);
            from -= amount;
            to += amount;
        }

        ++steps;
    }

    return steps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (c > max(a, b) || c % gcd(a, b) != 0) {
            cout << -1 << '\n';
        } else {
            cout << min(pour(a, b, c), pour(b, a, c)) << '\n';
        }
    }

    return 0;
}