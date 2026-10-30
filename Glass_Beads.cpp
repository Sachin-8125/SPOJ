#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int minimumRotation(const string& s) {
    int n = static_cast<int>(s.size());
    int i = 0, j = 1, k = 0;

    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n];
        char b = s[(j + k) % n];

        if (a == b) {
            ++k;
            continue;
        }

        if (a > b) {
            i += k + 1;
            if (i <= j) i = j + 1;
        } else {
            j += k + 1;
            if (j <= i) j = i + 1;
        }
        k = 0;
    }
    return min(i, j) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << minimumRotation(s) << '\n';
    }
    return 0;
}