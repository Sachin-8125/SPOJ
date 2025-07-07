#include<iostream>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long count = 0;
        // Count factors of 5
        for(long long i = 5; i <= n; i *= 5){
            count += n/i;
        }
        cout<<count<<endl;
    }
    return 0;
}