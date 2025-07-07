#include <bits/stdc++.h>
using namespace std;
void print(int r,int c){
    for(int i=0;i<r;++i){
        for(int j=0;j<c;++j){
            if(i%3==0||j%3==0)cout<<"*";
            else cout<<".";
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
        print(3*r+1,3*c+1);
        cout<<endl;
    }
    return 0;
}