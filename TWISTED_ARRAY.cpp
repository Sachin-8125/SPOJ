#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if(!(cin >> n >> k)) return 0;

    vector<long long> A(n), B(k);
    for(int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    for(int j = 0; j < k; ++j) {
        cin >> B[j];
    }

    // Build prefix sums
    vector<long long> prefA(n+1, 0), prefB(k+1, 0);
    for(int i = 0; i < n; ++i) prefA[i+1] = prefA[i] + A[i];
    for(int j = 0; j < k; ++j) prefB[j+1] = prefB[j] + B[j];

    // Store all subarray sums of A in an unordered_set
    unordered_set<long long> sumsA;
    sumsA.reserve(n * 2);
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j <= n; ++j){
            sumsA.insert(prefA[j] - prefA[i]);
        }
    }

    // Check subarray sums of B against sumsA
    bool twisted = false;
    for(int r = 0; r < k && !twisted; ++r){
        for(int s = r+1; s <= k; ++s){
            if(sumsA.count(prefB[s] - prefB[r])){
                twisted = true;
                break;
            }
        }
    }

    cout << (twisted ? "Yes\n" : "No\n");
    return 0;
}
