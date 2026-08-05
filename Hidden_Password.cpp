#include <iostream>
#include <string>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    string s1 = "";

    while (s1.length() < n * 6) {
        string temp;
        cin >> temp;
        s1 += temp;
    }
    
    string s2;
    cin >> s2;

    string password = "";
    
    for (int t = 0; t < n; ++t) {
        int a = 0;
        int b = 0;
        
        for (int i = 0; i < 6; ++i) {
            unsigned char c = s1[t * 6 + i];
            
            int bit_a = (c >> i) & 1;
            int bit_b = (c >> ((i + 3) % 6)) & 1;
            
            a |= (bit_a << i);
            b |= (bit_b << i);
        }
    
        password += s2[a];
        password += s2[b];
    }
    
    cout << password << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}