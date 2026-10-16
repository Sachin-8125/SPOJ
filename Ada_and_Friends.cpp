#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q, K;
    while (cin >> Q >> K) {
        unordered_map<string, long long> spending;
        spending.reserve(Q);

        for (int i = 0; i < Q; ++i) {
            string name;
            long long expense;
            cin >> name >> expense;
            spending[name] += expense;
        }

        vector<long long> totals;
        totals.reserve(spending.size());

        for (const auto& [name, amount] : spending) {
            totals.push_back(amount);
        }

        sort(totals.rbegin(), totals.rend());

        long long saved = 0;
        int count = min(K, static_cast<int>(totals.size()));
        for (int i = 0; i < count; ++i) {
            saved += totals[i];
        }

        cout << saved << '\n';
    }

    return 0;
}