//  Sums to calculate

#include<bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--) {
        long n;
        cin>>n;
        cout<<n*(n+1)/2<<" "<<n*(n+1)<<" "<<n*n<<" "<<n*(n+1)*(2*n+1)/6<<" "<<(n*n)*((n+1)*(n+1))/4<<endl;
    }
    
    return 0;
}
