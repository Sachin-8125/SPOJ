#include<iostream>
#include<vector>
#include<climits>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<long long>fact(2*n+2),res(2*n+1);
    fact[0]=0,fact[1]=1;
    for(int i=1;i<=n;i++){
        fact[2*i] = fact[i];
        fact[2*i+1] = fact[i]+fact[i+1];
    }
    long long maxi = LLONG_MIN;
    for(int i=0;i<2*n+1;i++){
        res[i] = fact[i]/fact[i+1];
        maxi = max(maxi,res[i]);
    }
    cout<<maxi;
}