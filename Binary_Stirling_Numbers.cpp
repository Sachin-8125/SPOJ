#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d;
    if (!(cin >> d)) return 0;
    while (d--) {
        unsigned long long n, m;
        cin >> n >> m;
        unsigned long long overlap = (n - m) & ((m - 1) >> 1);
        cout << (overlap == 0 ? 1 : 0) << '\n';
    }
    return 0;
}