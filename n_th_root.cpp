#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using BigFloat = boost::multiprecision::number<
    boost::multiprecision::cpp_dec_float<500>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        unsigned int n;
        string xInput;
        cin >> n >> xInput;

        BigFloat x(xInput);
        BigFloat degree(n);
        BigFloat root = boost::multiprecision::pow(x, BigFloat(1) / degree);

        ostringstream formatted;
        formatted << scientific << setprecision(150) << root;
        string scientificForm = formatted.str();

        string digits;
        for (char c : scientificForm) {
            if (c >= '0' && c <= '9') {
                digits += c;
                if (digits.size() == 101) break;
            }
        }

        while (digits.size() > 1 && digits.back() == '0') {
            digits.pop_back();
        }

        cout << digits << '\n';
    }

    return 0;
}