#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect {
    long long w, l;
};

struct Line {
    long long m, c;
    long long eval(long long x) { return m * x + c; }
};

bool is_bad(Line l1, Line l2, Line l3) {
    return (double)(l2.c - l1.c) * (l2.m - l3.m) >= (double)(l3.c - l2.c) * (l1.m - l2.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Rect> raw(n);
    for (int i = 0; i < n; i++) {
        cin >> raw[i].w >> raw[i].l;
    }

    sort(raw.begin(), raw.end(), [](Rect a, Rect b) {
        if (a.w != b.w) return a.w < b.w;
        return a.l < b.l;
    });

    vector<Rect> rects;
    for (int i = 0; i < n; i++) {
        while (!rects.empty() && rects.back().l <= raw[i].l) {
            rects.pop_back();
        }
        rects.push_back(raw[i]);
    }

    int m = rects.size();
    vector<long long> dp(m + 1, 0);
    vector<Line> hull;
    int ptr = 0;

    hull.push_back({rects[0].l, 0});

    for (int i = 1; i <= m; i++) {
        long long x = rects[i - 1].w;
        while (ptr + 1 < hull.size() && hull[ptr].eval(x) >= hull[ptr + 1].eval(x)) {
            ptr++;
        }

        dp[i] = hull[ptr].eval(x);

        if (i < m) {
            Line newLine = {rects[i].l, dp[i]};
            while (hull.size() >= 2 && is_bad(hull[hull.size() - 2], hull.back(), newLine)) {
                hull.pop_back();
            }
            hull.push_back(newLine);
            if (ptr >= hull.size()) ptr = hull.size() - 1;
        }
    }

    cout << dp[m] << endl;

    return 0;
}
