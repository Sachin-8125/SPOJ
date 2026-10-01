#include <iostream>
using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    
    int arr[N];
    for(int i=0; i<N; i++){
        cin>>arr[i];
    }

    int sum = 0, left = 0, maxi = 0;

    for(int right=0; right<N; right++){
        sum += arr[right];
        while(sum>M){
            sum -= arr[left++];
        }
        maxi = max(maxi, sum);
    }

    cout<<maxi<<endl;

    return 0;
}