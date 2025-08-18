#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s;
    while (cin >> s && s != "0") {
        int n = s.length();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1; 

        for (int i = 1; i <= n; ++i) {
            // Single digit decoding
            if (s[i-1] != '0')
                dp[i] += dp[i-1];
            // Double digit decoding (valid if between 10 and 26)
            if (i > 1) {
                int val = (s[i-2] - '0') * 10 + (s[i-1] - '0');
                if (val >= 10 && val <= 26)
                    dp[i] += dp[i-2];
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}
