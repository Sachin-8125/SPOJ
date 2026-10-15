#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int test = 0; test < t; ++test) {
        int n;
        cin >> n;

        map<string, int> counts;

        for (int i = 0; i < n; ++i) {
            string control, bank, owner1, owner2, owner3, owner4;
            cin >> control >> bank >> owner1 >> owner2 >> owner3 >> owner4;

            string account = control + bank + owner1 + owner2 + owner3 + owner4;
            ++counts[account];
        }

        for (const auto& [account, count] : counts) {
            cout << account.substr(0, 2) << ' '
                 << account.substr(2, 8) << ' '
                 << account.substr(10, 4) << ' '
                 << account.substr(14, 4) << ' '
                 << account.substr(18, 4) << ' '
                 << account.substr(22, 4) << ' '
                 << count << '\n';
        }

        if (test + 1 < t) {
            cout << '\n';
        }
    }

    return 0;
}
