#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    const int MAXV = 100000;                   
    vector<int> a(N);
    for (int &x : a) cin >> x;

    const int SZ = MAXV + 1;
    bitset<SZ> dp;
    dp[0] = 1;
    for (int x : a) {
        if (x > MAXV) continue;                  
        dp |= (dp << x);
    }

    vector<int> pref(SZ, 0);
    pref[0] = dp[0];
    for (int i = 1; i < SZ; ++i){
        pref[i] = pref[i-1] + (dp[i] ? 1 : 0);
    }
        
    for (int i = 0; i < Q; ++i) {
        int B, E;
        cin >> B >> E;
        if (B < 0) B = 0;
        if (E > MAXV) E = MAXV;
        int ans = pref[E] - (B > 0 ? pref[B-1] : 0);
        cout << ans << '\n';
    }
    return 0;
}