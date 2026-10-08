#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; tc++) {
        int m, n, ci, cj;
        cin >> m >> n >> ci >> cj;
        
        if (tc > 0)
            cout << '\n';
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (abs(i - ci) == abs(j - cj))
                    cout << '*';
                else
                    cout << '.';
            }
            cout << '\n';
        }
    }
    
    return 0;
}