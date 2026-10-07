#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int h, w;
        cin >> h >> w;
        vector<vector<int>> a(h, vector<int>(w));
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                cin >> a[i][j];

        vector<int> prev(w), cur(w);
        for (int j = 0; j < w; ++j) prev[j] = a[0][j];

        for (int i = 1; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int best = prev[j];                     
                if (j > 0)   best = max(best, prev[j-1]); 
                if (j + 1 < w) best = max(best, prev[j+1]); 
                cur[j] = a[i][j] + best;
            }
            swap(prev, cur);
        }

        int answer = *max_element(prev.begin(), prev.end());
        cout << answer << '\n';
    }
    return 0;
}