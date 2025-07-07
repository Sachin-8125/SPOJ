#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    long long t;
    cin>>t;
    while(t--){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        long long n;
        cin>>n;
        long long  gcd_sum = 0;
        for(int i=1;i<=n;i++){
            gcd_sum += i*__gcd(i,n);
        }
        cout<<gcd_sum<<endl;
    }
}