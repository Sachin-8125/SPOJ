#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int S, C;
        cin >> S >> C;
        vector<long long> a(S);
        for (int i = 0; i < S; ++i) cin >> a[i];
        vector<vector<long long>> diffs;
        diffs.push_back(a);
        while (diffs.back().size() > 1) {
            const auto &prev = diffs.back();
            vector<long long> cur;
            cur.reserve(prev.size() - 1);
            for (size_t i = 1; i < prev.size(); ++i)
                cur.push_back(prev[i] - prev[i - 1]);
            diffs.push_back(move(cur));
            bool constant = true;
            const auto &row = diffs.back();
            for (size_t i = 1; i < row.size(); ++i) {
                if (row[i] != row[0]) { constant = false; break; }
            }
            if (constant) break;
        }
        vector<long long> ans;
        ans.reserve(C);
        for (int step = 0; step < C; ++step) {
            long long bottom_next;
            if (diffs.back().empty()) {
                bottom_next = 0;
                diffs.back().push_back(bottom_next);
            } else {
                bottom_next = diffs.back().back();
                diffs.back().push_back(bottom_next);
            }
            for (int r = (int)diffs.size() - 2; r >= 0; --r) {
                long long next_val = diffs[r].back() + diffs[r + 1].back();
                diffs[r].push_back(next_val);
            }
            ans.push_back(diffs[0].back());
        }
        for (int i = 0; i < C; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}