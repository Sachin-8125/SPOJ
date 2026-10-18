#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solve(string s) {
    size_t first_non_zero = s.find_first_not_of("0 \t\r\n");
    if (first_non_zero == string::npos) {
        return "0";
    }
    s = s.substr(first_non_zero);
    size_t last = s.find_last_not_of(" \t\r\n");
    if (last != string::npos) {
        s = s.substr(0, last + 1);
    }

    if (s == "1") {
        return "1";
    }

    vector<int> digits;
    digits.reserve(s.size() + 2);
    int carry = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        int val = (s[i] - '0') * 2 + carry;
        digits.push_back(val % 10);
        carry = val / 10;
    }
    if (carry > 0) {
        digits.push_back(carry);
    }

    int borrow = 2;
    for (size_t i = 0; i < digits.size(); ++i) {
        int cur = digits[i] - borrow;
        if (cur < 0) {
            cur += 10;
            borrow = 1;
        } else {
            digits[i] = cur;
            borrow = 0;
            break;
        }
        digits[i] = cur;
    }

    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }

    string res;
    res.reserve(digits.size());
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        res.push_back(static_cast<char>('0' + digits[i]));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n_str;
    while (cin >> n_str) {
        cout << solve(n_str) << "\n";
    }

    return 0;
}