#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using Real = boost::multiprecision::number<
    boost::multiprecision::cpp_dec_float<300>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string input;
        cin >> input;

        Real x(input);

        if (x == 1) {
            cout << "0\n";
            continue;
        }

        Real value = log(x);

        ostringstream stream;
        stream << scientific << setprecision(160) << value;
        string scientificForm = stream.str();

        string digits;
        for (char c : scientificForm) {
            if (c >= '0' && c <= '9') {
                digits += c;
            } else if (c == 'e' || c == 'E') {
                break;
            }
        }

        cout << digits.substr(0, 101) << '\n';
    }

    return 0;
}