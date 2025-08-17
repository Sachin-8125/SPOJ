#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n);
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    vector<int> lhs; // Stores values of (a * b + c)
    vector<int> rhs; // Stores values of (d * (e + f)), with d ≠ 0

    for (int a : S)
        for (int b : S)
            for (int c : S)
                lhs.push_back(a * b + c);

    for (int d : S) {
        if (d == 0) continue;
        for (int e : S)
            for (int f : S)
                rhs.push_back(d * (e + f));
    }

    // Counting frequencies in rhs
    unordered_map<int, int> rhs_count;
    for (int val : rhs)
        ++rhs_count[val];

    long long result = 0;
    for (int val : lhs)
        result += rhs_count[val];

    cout << result << endl;
    return 0;
}
