#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Helper function to add two big integers represented as strings
string add(string a, string b) {
    string result = "";
    int carry = 0, sum = 0;
    int n1 = a.size(), n2 = b.size();
    if (n1 < n2) swap(a, b), swap(n1, n2);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < n2; i++) {
        sum = (a[i] - '0') + (b[i] - '0') + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
    }
    for (int i = n2; i < n1; i++) {
        sum = (a[i] - '0') + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry) result += carry + '0';
    reverse(result.begin(), result.end());
    return result;
}

// Helper function to subtract two big integers represented as strings (a >= b)
string subtract(string a, string b) {
    string result = "";
    int n1 = a.size(), n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int borrow = 0, diff = 0;
    for (int i = 0; i < n2; i++) {
        diff = (a[i] - '0') - (b[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;
        result += diff + '0';
    }
    for (int i = n2; i < n1; i++) {
        diff = (a[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;
        result += diff + '0';
    }
    while (result.size() > 1 && result.back() == '0')
        result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

// Helper function to divide a big integer by 2
string divide_by_2(string a) {
    string result = "";
    int idx = 0, temp = a[idx] - '0';
    while (temp < 2 && idx + 1 < a.size())
        temp = temp * 10 + (a[++idx] - '0');
    while (a.size() > idx) {
        result += (temp / 2) + '0';
        temp = (temp % 2) * 10 + ((++idx < a.size()) ? a[idx] - '0' : 0);
    }
    if (result.empty())
        return "0";
    // Remove leading zeros
    int pos = 0;
    while (pos < result.size() - 1 && result[pos] == '0') pos++;
    return result.substr(pos);
}

int main() {
    for (int t = 0; t < 10; t++) {
        string A, B;
        cin >> A >> B;
        string sum = add(A, B);
        string K = divide_by_2(sum);
        string N = subtract(A, K);
        cout << K << endl;
        cout << N << endl;
    }
    return 0;
}
