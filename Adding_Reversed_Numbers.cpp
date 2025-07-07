#include<iostream>
using namespace std;
int rev(int n){
    int r=0;
    while(n){
        r=r*10+n%10;
        n/=10;
    }
    return r;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
        int x = rev(a)+rev(b);
        cout<<rev(x)<<'\n';
    }
}