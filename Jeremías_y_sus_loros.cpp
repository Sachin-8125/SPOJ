#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    int first = INT_MAX;
    int second = INT_MAX;

    vector<int> arr(n);

    for(int i=0; i<n; i++){
        cin>>arr[i];
        if(arr[i]<first){
            second = first;
            first = arr[i];
        } else if(arr[i]<second){
            second = arr[i];
        }
    }

    cout<< abs(first-second)<<endl;

}