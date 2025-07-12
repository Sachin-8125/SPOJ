#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int ar[n];
        for (int i = 0; i < n; i++) cin >> ar[i];
        sort(ar, ar + n);
        int ans = 1e9;
        if (k == 1) ans = 0;
        else {
            k--;
            for (int i = 0; i <= n - k - 1; i++)
                ans = min(ans, ar[i + k] - ar[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}