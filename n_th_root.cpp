#include <iostream>
#include <iomanip>
#include <string>
#include <mpfr.h>
#include <cctype>

using namespace std;

void print_101_digits(mpfr_t result) {
    // Convert result to string with at least 110 digits for safety
    // We use base 10, scientific notation is off (exp = 0)
    char str[1200];
    mpfr_sprintf(str, "%.110Rf", result); // Sufficient digits

    string digits;
    for (int i = 0; str[i]; ++i) {
        if (isdigit(str[i])) digits += str[i];
    }

    // Remove leading zeros
    size_t first = digits.find_first_not_of('0');
    if (first == string::npos) {
        cout << "0\n";
        return;
    }

    digits = digits.substr(first);
    if (digits.size() > 101) digits = digits.substr(0, 101);
    cout << digits << '\n';
}

int main() {
    int T;
    cin >> T;

    // Set precision high enough to retain 110+ decimal digits
    mpfr_set_default_prec(400); // > log2(10^110) ≈ 365 bits
    
    while (T--) {
        int n;
        string x_str;
        cin >> n >> x_str;

        mpfr_t x, root;
        mpfr_init2(x, 400);
        mpfr_init2(root, 400);

        // Read string as base-10 float into x
        mpfr_set_str(x, x_str.c_str(), 10, MPFR_RNDN);

        // Compute nth root: x ** (1/n)
        mpfr_root(root, x, n, MPFR_RNDN);

        print_101_digits(root);

        mpfr_clear(x);
        mpfr_clear(root);
    }

    return 0;
}

