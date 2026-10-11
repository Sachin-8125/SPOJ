#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long x, y, z;
        cin >> x >> y >> z;

        long long total = x + y + z;
        long long largest = max({x, y, z});

        cout << min(total / 3, total - largest) << '\n';
    }

    return 0;
}