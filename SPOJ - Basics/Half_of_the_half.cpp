//  Half of the half

#include<bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--) {
        string s;
        cin>>s;
        s = s.substr(0,s.length()/2);
        int i=0;
        string temp = "";
        while (i<s.length()) {
            temp += s[i];
            i += 2;
        }
        cout<<temp<<endl;
    }
    
    return 0;
}
