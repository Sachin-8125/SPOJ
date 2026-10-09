#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BigInt {
private:
    static constexpr int BASE = 100;
    vector<int> digit; 

    void normalize() {
        while (digit.size() > 1 && digit.back() == 0) {
            digit.pop_back();
        }
    }

public:
    BigInt() : digit(1, 0) {}

    explicit BigInt(const string& s) {
        digit.clear();

        for (int end = static_cast<int>(s.size()); end > 0; end -= 2) {
            int start = max(0, end - 2);
            digit.push_back(stoi(s.substr(start, end - start)));
        }

        if (digit.empty()) digit.push_back(0);
        normalize();
    }

    bool isZero() const {
        return digit.size() == 1 && digit[0] == 0;
    }

    string toString() const {
        string result = to_string(digit.back());

        for (int i = static_cast<int>(digit.size()) - 2; i >= 0; --i) {
            string part = to_string(digit[i]);
            result += string(2 - part.size(), '0') + part;
        }

        return result;
    }

    int compare(const BigInt& other) const {
        if (digit.size() != other.digit.size()) {
            return digit.size() < other.digit.size() ? -1 : 1;
        }

        for (int i = static_cast<int>(digit.size()) - 1; i >= 0; --i) {
            if (digit[i] != other.digit[i]) {
                return digit[i] < other.digit[i] ? -1 : 1;
            }
        }

        return 0;
    }

    static BigInt add(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.digit.clear();

        int carry = 0;
        size_t n = max(a.digit.size(), b.digit.size());

        for (size_t i = 0; i < n || carry; ++i) {
            int sum = carry;
            if (i < a.digit.size()) sum += a.digit[i];
            if (i < b.digit.size()) sum += b.digit[i];

            result.digit.push_back(sum % BASE);
            carry = sum / BASE;
        }

        result.normalize();
        return result;
    }

    static BigInt subtract(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.digit = a.digit;

        int borrow = 0;
        for (size_t i = 0; i < result.digit.size(); ++i) {
            int value = result.digit[i] - borrow;
            if (i < b.digit.size()) value -= b.digit[i];

            if (value < 0) {
                value += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.digit[i] = value;
        }

        result.normalize();
        return result;
    }

    static BigInt multiply(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.digit.assign(a.digit.size() + b.digit.size() + 1, 0);

        for (size_t i = 0; i < a.digit.size(); ++i) {
            long long carry = 0;

            for (size_t j = 0; j < b.digit.size(); ++j) {
                long long value =
                    result.digit[i + j] +
                    static_cast<long long>(a.digit[i]) * b.digit[j] +
                    carry;

                result.digit[i + j] = static_cast<int>(value % BASE);
                carry = value / BASE;
            }

            size_t pos = i + b.digit.size();
            while (carry > 0) {
                long long value = result.digit[pos] + carry;
                result.digit[pos] = static_cast<int>(value % BASE);
                carry = value / BASE;
                ++pos;
            }
        }

        result.normalize();
        return result;
    }

    static pair<BigInt, BigInt> divide(const BigInt& a, const BigInt& b) {
        BigInt quotient;
        quotient.digit.assign(a.digit.size(), 0);

        BigInt remainder;

        for (int i = static_cast<int>(a.digit.size()) - 1; i >= 0; --i) {
            if (remainder.isZero()) {
                remainder.digit[0] = a.digit[i];
            } else {
                remainder.digit.insert(remainder.digit.begin(), a.digit[i]);
            }
            remainder.normalize();

            int low = 0;
            int high = BASE - 1;
            int best = 0;

            while (low <= high) {
                int mid = (low + high) / 2;
                BigInt product = multiplyByDigit(b, mid);

                if (product.compare(remainder) <= 0) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            quotient.digit[i] = best;
            if (best != 0) {
                remainder = subtract(remainder, multiplyByDigit(b, best));
            }
        }

        quotient.normalize();
        remainder.normalize();
        return {quotient, remainder};
    }

    static BigInt multiplyByDigit(const BigInt& a, int value) {
        BigInt result;
        result.digit.clear();

        int carry = 0;
        for (int d : a.digit) {
            int product = d * value + carry;
            result.digit.push_back(product % BASE);
            carry = product / BASE;
        }

        while (carry > 0) {
            result.digit.push_back(carry % BASE);
            carry /= BASE;
        }

        if (result.digit.empty()) result.digit.push_back(0);
        result.normalize();
        return result;
    }

    static BigInt truncatedMultiply(const BigInt& a, const BigInt& b, int M) {
        BigInt result;

        for (size_t i = 0; i < a.digit.size(); ++i) {
            for (size_t j = 0; j < b.digit.size(); ++j) {
                if (i + j < static_cast<size_t>(M)) continue;

                int product = a.digit[i] * b.digit[j];
                size_t pos = i + j - M;

                if (result.digit.size() <= pos) {
                    result.digit.resize(pos + 1, 0);
                }

                int carry = product;
                while (carry > 0) {
                    if (result.digit.size() <= pos) {
                        result.digit.push_back(0);
                    }

                    int value = result.digit[pos] + carry;
                    result.digit[pos] = value % BASE;
                    carry = value / BASE;
                    ++pos;
                }
            }
        }

        result.normalize();
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        char operation;
        string aInput, bInput;
        cin >> operation >> aInput >> bInput;

        BigInt a(aInput);
        BigInt b(bInput);

        if (operation == '<') {
            cout << (a.compare(b) < 0 ? 1 : a.compare(b) == 0 ? 0 : -1) << '\n';
        } else if (operation == '+') {
            cout << BigInt::add(a, b).toString() << '\n';
        } else if (operation == '-') {
            if (a.compare(b) < 0) {
                cout << "0\n";
            } else {
                cout << BigInt::subtract(a, b).toString() << '\n';
            }
        } else if (operation == '*') {
            cout << BigInt::multiply(a, b).toString() << '\n';
        } else if (operation == '/') {
            if (b.isZero()) {
                cout << "0 0\n";
            } else {
                auto [quotient, remainder] = BigInt::divide(a, b);
                cout << quotient.toString() << ' '
                     << remainder.toString() << '\n';
            }
        } else if (operation == '#') {
            int M;
            cin >> M;
            cout << BigInt::truncatedMultiply(a, b, M).toString() << '\n';
        }
    }

    return 0;
}