#include<bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(0);cin.tie(0);int t=10;string s;while(t--){cin>>s;int c=0;for(char i:s)c+=(i=='F'||i=='L'||i=='T'||i=='D');cout<<(1<<c)<<'\n';}return 0;}