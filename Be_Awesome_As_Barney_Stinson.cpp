#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int M, N;
    
    while (cin >> M >> N) {
        if (M == 0 && N == 0) break;
        
        int A[25], B[25];
        for (int i = 0; i < M; i++) {
            cin >> A[i] >> B[i];
        }
        
        long long dp[25][105];
        memset(dp, 0, sizeof(dp));
        
        dp[0][0] = 1;
        
        for (int i = 1; i <= M; i++) {
            for (int j = 0; j <= N; j++) {
                for (int k = A[i-1]; k <= B[i-1]; k++) {
                    if (j >= k) {
                        dp[i][j] += dp[i-1][j-k];
                    }
                }
            }
        }
        
        cout << dp[M][N] << endl;
    }
    
    return 0;
}