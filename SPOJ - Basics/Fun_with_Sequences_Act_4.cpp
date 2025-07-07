#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> S(n), Q(n);
    for (int i = 0; i < n; ++i) cin >> S[i];
    for (int i = 0; i < n; ++i) cin >> Q[i];
    vector<int> SQ;

    for (int i = 0; i < n; ++i) {
        for (int j = max(0, i - x); j <= min(n - 1, i + x); ++j) {
            if (S[i] == Q[j]) {
                SQ.push_back(i + 1); // +1 for 1-based index
                break;
            }
        }
    }

    for (int i = 0; i < SQ.size(); ++i) {
        cout << SQ[i];
        if (i != SQ.size() - 1) cout << " ";
    }
    cout << endl;
    return 0;
}