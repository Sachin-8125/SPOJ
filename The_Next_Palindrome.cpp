#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string findNextPalindrome(string n) {
    int len = n.length();
    if (len == 1 && n[0] == '9') return "11";
    string res = n;
    bool allNines = true;
    for (char c : n) {
        if (c != '9') {
            allNines = false;
            break;
        }
    }
    if (allNines) {
        res = "1";
        for (int i = 0; i < len - 1; ++i) {
            res += "0";
        }
        res += "1";
        return res;
    }

    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        res[j] = res[i];
    }

    if (res > n) return res;

    int mid = (len + 1) / 2;
    int carry = 1;
    for (int i = mid - 1; i >= 0; --i) {
        int digit = (res[i] - '0') + carry;
        carry = digit / 10;
        res[i] = (digit % 10) + '0';
        res[len - 1 - i] = res[i];
        if (carry == 0) break;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string n;
        cin >> n;
        cout << findNextPalindrome(n) << endl;
    }
    return 0;
}
