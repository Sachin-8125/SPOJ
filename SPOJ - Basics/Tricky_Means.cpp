#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<double> arr(n);
        
        for(int i = 0; i < n; i++) 
            cin >> arr[i];
            
        double AM = 0.0, GM = 1.0, HM = 0.0;  // Initialize GM to 1.0
        
        // Calculate AM and GM
        for(int i = 0; i < n; i++) {
            AM += arr[i];
            GM *= arr[i];
            HM += 1.0/arr[i];  // Add calculation for Harmonic Mean
        }
        
        AM /= n;
        GM = pow(GM, 1.0/n);
        HM = n/HM;  // Finalize Harmonic Mean calculation
        
        cout << fixed << setprecision(9) << AM << " " << GM << " " << HM << endl;
    }
    return 0;
}