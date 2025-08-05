#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int C;
    cin >> C;
    
    while(C--) {
        int N, K;
        cin >> N >> K;
        
        vector<int> price(K + 1);
        for(int i = 1; i <= K; i++) {
            cin >> price[i];
        }
        vector<vector<int>> dp(K + 1, vector<int>(N + 1, INT_MAX));
        dp[0][0] = 0;
        //fill the dp table
        for(int packets = 1; packets <= N; packets++) {
            for(int wt = 1; wt <= K; wt++) {
                // Try all possible packet sizes for the current packet
                for(int size = 1; size <= min(wt, K); size++) {
                    if(price[size] != -1 && dp[wt - size][packets - 1] != INT_MAX) {
                        dp[wt][packets] = min(dp[wt][packets], dp[wt - size][packets - 1] + price[size]);
                    }
                }
            }
        }
        
        // Find minimum cost to buy exactly K kg using at most N packets
        int result = INT_MAX;
        for(int packets = 1; packets <= N; packets++) {
            result = min(result, dp[K][packets]);
        }
        
        if(result == INT_MAX) {
            cout << -1 << endl;
        } else {
            cout << result << endl;
        }
    }
    
    return 0;
}
