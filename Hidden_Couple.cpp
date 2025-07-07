#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    int j=1;
    while(j<=t){
        string s;
        cin>>s;
        int temp=0;
        for(int i=0;i<s.length();i++){
            temp += s[i];
        }
        cout<<"Case "<<j++<<": "<<(temp%3?"No":"Yes")<<endl;
    }
}