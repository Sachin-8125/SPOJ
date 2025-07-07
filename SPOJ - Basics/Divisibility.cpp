//  Divisibility

#include<bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin>>t;
    vector<int> v;
    v.clear();
    while (t--) {
        int n,x,y;
        cin>>n>>x>>y;
        for (int i=1;i<n;i++) {
            if (i%x==0 && i%y!=0) {
                v.push_back(i);
            }
        }
        for (int i=0;i<v.size();i++) {
            cout<<v[i]<<" ";
        }
        cout<<endl;
        v.clear();
    }
    return 0;
}
