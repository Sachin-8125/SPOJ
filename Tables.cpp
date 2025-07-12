#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n,k,s,i;
    cin>>n>>k>>s;
    int a[n];
    for(i=0;i<n;i++){
        cin>>a[i];
    }
    int tables=k*s;
    sort(a,a+n,greater<int>());
    int sum=0,c=0;
    for(i=0;i<n;i++){
        sum+=a[i];
        c++;
        if(sum>=tables) break;
    }
    cout<<c<<endl;
}