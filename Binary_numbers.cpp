#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string normalize(const string& s) {
    size_t firstOne = s.find('1');
    if (firstOne == string::npos) return "0";
    return s.substr(firstOne);
}

string addBinary(const string& a, const string& b) {
    string result;
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int bitA = (i >= 0 && a[i] == '1');
        int bitB = (j >= 0 && b[j] == '1');

        int sumBit = bitA ^ bitB ^ carry;
        int nextCarry = (bitA & bitB) | ((bitA ^ bitB) & carry);

        result.push_back(sumBit ? '1' : '0');
        carry = nextCarry;
        --i;
        --j;
    }

    reverse(result.begin(), result.end());
    return normalize(result);
}

int compareBinary(const string& a, const string& b) {
    string x = normalize(a);
    string y = normalize(b);

    if (x.size() != y.size()) return x.size() > y.size() ? 1 : -1;
    if (x == y) return 0;
    return x > y ? 1 : -1;
}

string subtractBinary(const string& a, const string& b) {
    string result;
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int borrow = 0;

    while (i >= 0) {
        int bitA = a[i] - '0';
        int bitB = (j >= 0) ? b[j] - '0' : 0;

        int difference = bitA ^ bitB ^ borrow;
        int nextBorrow = ((!bitA) & (bitB | borrow)) | (bitB & borrow);

        result.push_back(difference ? '1' : '0');
        borrow = nextBorrow;
        --i;
        --j;
    }

    reverse(result.begin(), result.end());
    return normalize(result);
}

string multiplyBinary(const string& a, const string& b) {
    string result = "0";
    int shift = 0;

    for (int i = static_cast<int>(b.size()) - 1; i >= 0; --i, ++shift) {
        if (b[i] == '1') {
            string shifted = a + string(shift, '0');
            result = addBinary(result, shifted);
        }
    }

    return normalize(result);
}

pair<string, string> divideBinary(const string& a, const string& b) {
    string quotient;
    string remainder = "0";

    for (char bit : a) {
        remainder = normalize(remainder + bit);

        if (compareBinary(remainder, b) >= 0) {
            remainder = subtractBinary(remainder, b);
            quotient.push_back('1');
        } else {
            quotient.push_back('0');
        }
    }

    return {normalize(quotient), normalize(remainder)};
}

string wrappedSubtract(const string& a, const string& b) {
    int n = max(a.size(), b.size());

    string paddedA = string(n - a.size(), '0') + a;
    string paddedB = string(n - b.size(), '0') + b;

    string complementB = paddedB;
    for (char& bit : complementB) {
        bit = (bit == '0') ? '1' : '0';
    }

    string plusOne = addBinary(complementB, "1");
    string result = addBinary(paddedA, plusOne);

    if (result.size() > static_cast<size_t>(n)) {
        result = result.substr(result.size() - n);
    }

    return normalize(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string testCasesBinary;
    cin >> testCasesBinary;

    int testCases = 0;
    for (char bit : testCasesBinary) {
        testCases = testCases * 2 + (bit - '0');
    }

    while (testCases--) {
        string operation, a, b;
        cin >> operation >> a >> b;

        a = normalize(a);
        b = normalize(b);

        if (operation == "0") {
            cout << (compareBinary(a, b) > 0 ? "1" : "0") << '\n';
        } else if (operation == "1") {
            cout << addBinary(a, b) << '\n';
        } else if (operation == "10") {
            if (compareBinary(a, b) >= 0) {
                cout << subtractBinary(a, b) << '\n';
            } else {
                cout << wrappedSubtract(a, b) << '\n';
            }
        } else if (operation == "11") {
            cout << multiplyBinary(a, b) << '\n';
        } else if (operation == "100") {
            if (b == "0") {
                cout << "0 0\n";
            } else {
                auto [quotient, remainder] = divideBinary(a, b);
                cout << quotient << ' ' << remainder << '\n';
            }
        }
    }

    return 0;
}