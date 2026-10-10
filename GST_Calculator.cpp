#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

long long toCents(const string& price) {
    size_t dot = price.find('.');
    long long ringgit = stoll(price.substr(0, dot));
    long long sen = stoll(price.substr(dot + 1));

    // Prices are stated to have exactly two decimal places.
    return ringgit * 100 + sen;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;

        long long totalBaseCents = 0;
        long long standardRatedCents = 0;

        for (int i = 0; i < N; ++i) {
            string name, price, rate;
            int quantity;

            cin >> name >> quantity >> price >> rate;

            long long baseCents = quantity * toCents(price);
            totalBaseCents += baseCents;

            if (rate == "SR") {
                standardRatedCents += baseCents;
            }
        }

        long long gstCents = (standardRatedCents * 6 + 50) / 100;
        long long totalCents = totalBaseCents + gstCents;

        cout << "Case #" << tc << ":\n";
        cout << "Total Amount Include GST: "
             << totalCents / 100 << '.'
             << setw(2) << setfill('0') << totalCents % 100
             << setfill(' ') << '\n';

        cout << "Total Amount GST Paid: "
             << gstCents / 100 << '.'
             << setw(2) << setfill('0') << gstCents % 100
             << setfill(' ') << '\n';
    }

    return 0;
}