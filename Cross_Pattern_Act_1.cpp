#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int m, n, ci, cj;
        cin >> m >> n >> ci >> cj;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == ci || j == cj)
                    cout << '*';
                else
                    cout << '.';
            }
            cout << endl;
        }
        
        if (t > 0)
            cout << endl;
    }
    
    return 0;
}