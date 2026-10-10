#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;

        long long totalCents = 0;
        long long gstCents = 0;

        for (int i = 0; i < N; ++i) {
            string name, rate;
            int quantity;
            long long priceCents;
            char dot;
            int dollars, cents;

            cin >> name >> quantity >> dollars >> dot >> cents;
            cin >> rate;

            priceCents = static_cast<long long>(dollars) * 100 + cents;
            long long baseCents = quantity * priceCents;

            long long itemGstCents = 0;
            if (rate == "SR") {
                itemGstCents = (baseCents * 6 + 50) / 100;
            }

            totalCents += baseCents + itemGstCents;
            gstCents += itemGstCents;
        }

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