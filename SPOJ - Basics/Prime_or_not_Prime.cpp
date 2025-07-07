//  Prime or not Prime!

#include<bits/stdc++.h>

using namespace std;

void isPrime(int n) {
    for (int i=2;i<n;i++) {
        if (n%i==0) {
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        isPrime(n);
    }
    return 0;
}
