#include <bits/stdc++.h>
using namespace std;

static inline int inc_digit(int value, int pos) {
    static const int pw[4] = {1000, 100, 10, 1};
    int d = (value / pw[pos]) % 10;
    int nd = (d + 1) % 10;
    int delta = (nd - d) * pw[pos];         
    return value + delta;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        string s;      
        int M;
        cin >> s >> M;
        int N = stoi(s);
        
        vector<array<char, 10000>> win(M + 1);
        
        for (int cur = 0; cur < 10000; ++cur)
            win[0][cur] = (cur > N);
        
        for (int r = 1; r <= M; ++r) {
            bool adaTurn = ((M - r) % 2 == 0);   
            for (int cur = 0; cur < 10000; ++cur) {
                if (adaTurn) {
                    char canWin = 0;
                    for (int p = 0; p < 4 && !canWin; ++p) {
                        int nxt = inc_digit(cur, p);
                        if (win[r-1][nxt]) canWin = 1;
                    }
                    win[r][cur] = canWin;
                } else {
                    char allWin = 1;
                    for (int p = 0; p < 4 && allWin; ++p) {
                        int nxt = inc_digit(cur, p);
                        if (!win[r-1][nxt]) allWin = 0;
                    }
                    win[r][cur] = allWin;
                }
            }
        }
        
        cout << (win[M][N] ? "Ada" : "Vinit") << '\n';
    }
    return 0;
}