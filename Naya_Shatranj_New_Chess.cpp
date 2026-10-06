#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        long long n;
        cin >> n;
        
        long long max_knights;
        
        if (n == 1) {
            max_knights = 1;
        } else if (n == 2) {
            max_knights = 4;
        } else {
            max_knights = (n * n + 1) / 2;
        }
        
        if (max_knights % 2 == 1) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    
    return 0;
}