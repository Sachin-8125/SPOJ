#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    int masks[500005];
    long long cnt[1024] = {0}; 
    
    for (int i = 0; i < n; i++) {
        long long num;
        cin >> num;
        
        int mask = 0;
        while (num > 0) {
            int digit = num % 10;
            mask |= (1 << digit);
            num /= 10;
        }
        masks[i] = mask;
        cnt[mask]++;
    }
    
    long long result = 0;
    
    for (int i = 0; i < 1024; i++) {
        if (cnt[i] == 0) continue;
        
        result += cnt[i] * (cnt[i] - 1) / 2;
        
        for (int j = i + 1; j < 1024; j++) {
            if (cnt[j] > 0 && (i & j) != 0) {
                result += cnt[i] * cnt[j];
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}