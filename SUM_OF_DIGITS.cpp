#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string str;
        cin>>str;
        int n = str.size();
        int sum = 0;
        for(int i=0;i<n;++i){
            sum += str[i]-'0';
        }
        cout<<sum<<endl;
    }
    return 0;
}