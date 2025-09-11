#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Plot {
    ll w, l;
    bool operator<(const Plot &other) const {
        if (w == other.w) return l > other.l;
        return w < other.w;
    }
};
vector<Plot> plots;

bool bad(pair<ll,ll> a, pair<ll,ll> b, pair<ll,ll> c) {
    // Returns true if middle line (b) is unnecessary
    // a, b, c: (slope, intercept)
    return (c.second-b.second)*(b.first-a.first) < (b.second-a.second)*(c.first-b.first);
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; ++i) {
        ll w, l;
        cin >> w >> l;
        plots.push_back({w, l});
    }
    sort(plots.begin(), plots.end());
    vector<Plot> filtered;
    for (auto& plot: plots) {
        while (!filtered.empty() && filtered.back().l <= plot.l) {
            filtered.pop_back();
        }
        filtered.push_back(plot);
    }
    vector<pair<ll,ll>> cht;  // Pair (slope, intercept)
    vector<ll> dp(filtered.size());
    dp[0] = filtered.w*filtered.l;
    cht.push_back({filtered.l, dp});
    int ptr = 0;
    for (int i=1; i<filtered.size(); ++i) {
        // Convex hull trick - find best line for current width
        while (ptr+1 < cht.size() && cht[ptr+1].first*filtered[i].w + cht[ptr+1].second <= cht[ptr].first*filtered[i].w + cht[ptr].second)
            ++ptr;
        dp[i] = cht[ptr].first*filtered[i].w + cht[ptr].second;
        // Add new plot as a line: y = l*x + dp[i]
        pair<ll,ll> newline = {filtered[i].l, dp[i]};
        while (cht.size()>=2 && bad(cht[cht.size()-2], cht.back(), newline))
            cht.pop_back();
        cht.push_back(newline);
    }
    cout << dp.back() << endl;
    return 0;
}
