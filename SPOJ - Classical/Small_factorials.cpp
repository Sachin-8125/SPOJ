//  Small factorials

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string multiply(string num, int n) {
    if (n == 0) {
        return "0";
    }
    string res = "";
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        int digit = num[i] - '0';
        int product = digit * n + carry;
        res.push_back('0' + (product % 10));
        carry = product / 10;
    }
    while (carry) {
        res.push_back('0' + (carry % 10));
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    string fact[101];
    fact[0] = "1";
    for (int i = 1; i <= 100; i++) {
        fact[i] = multiply(fact[i-1], i);
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << fact[n] << endl;
    }
    return 0;
}

