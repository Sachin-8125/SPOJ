//  Land Acquisition

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Plot {
    ll width, length;
};
bool cmp(const Plot &a, const Plot &b) {
    if (a.width == b.width) return a.length > b.length;
    return a.width < b.width;
}
int main() {
    int n;
    cin >> n;
    vector<Plot> plots(n);
    for (int i = 0; i < n; ++i) {
        cin >> plots[i].width >> plots[i].length;
    }

    // Remove plots dominated by another (width >=, length >=)
    sort(plots.begin(), plots.end(), cmp);
    vector<Plot> filtered;
    for (const auto &p : plots) {
        while (!filtered.empty() && filtered.back().length <= p.length) filtered.pop_back();
        filtered.push_back(p);
    }

    // Convex Hull DP
    int sz = filtered.size();
    vector<ll> dp(sz + 1, 0); // dp[i]: min cost up to i-th plot

    // For CHT, keep lines in the form: y = a * x + b
    vector<ll> a; // slope = length
    vector<ll> b; // intercept = dp[j]
    int ptr = 0;

    // Helper to check if middle line is unnecessary
    auto bad = [&](int l1, int l2, int l3) {
        return (b[l3] - b[l1]) * (a[l1] - a[l2]) < (b[l2] - b[l1]) * (a[l1] - a[l3]);
    };

    for (int i = 0; i < sz; ++i) {
        ll W = filtered[i].width;
        ll L = filtered[i].length;

        if (i == 0) {
            dp[i] = W * L;
        } else {
            // Query minimum for current width W
            while (ptr + 1 < a.size() && a[ptr + 1] * W + b[ptr + 1] < a[ptr] * W + b[ptr])
                ++ptr;
            dp[i] = a[ptr] * W + b[ptr];
        }

        // Add new line: y = L * x + dp[i]
        a.push_back(L);
        b.push_back(dp[i]);
        while ((int)a.size() >= 3 && bad(a.size() - 3, a.size() - 2, a.size() - 1)) {
            a.erase(a.end() - 2);
            b.erase(b.end() - 2);
        }
    }

    cout << dp[sz - 1] << endl;
    return 0;
}
