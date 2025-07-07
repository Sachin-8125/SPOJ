#include <bits/stdc++.h>
using namespace std;
void print(int r,int c){
    for(int i=1;i<=r;++i){
        for(int j=1;j<=c;++j){
            if(i%2!=0){
                if(j%2!=0)cout<<"*";
                else cout<<".";
            }else{
                if(j%2!=0) cout<<".";
                else cout<<"*";
            } 
        }
        cout<<endl;
    }
}

int main() {
    int t;
    cin>>t;
    while(t--){
        int r,c;
        cin>>r>>c;
        print(r,c);
        cout<<endl;
    }
    return 0;
}