//  Iterated sums

#include<bits/stdc++.h>

using namespace std;

int main() {
    int a,b;
    cin>>a>>b;
    int aSum = a*(a-1)*(2*a-1)/6;
    int bSum = b*(b+1)*(2*b+1)/6;
    cout<<bSum-aSum<<endl;
    return 0;
}
