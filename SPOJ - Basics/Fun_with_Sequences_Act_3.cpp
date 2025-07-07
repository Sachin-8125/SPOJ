//  Fun with Sequences (Act 3)

#include <iostream>
using namespace std;

int main() {
    int n, m;
    int s[101], q[101];

    // Read n and sequence S
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    // Read m and sequence Q
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i];
    }

    // For each number in S, check if it is not present in Q
    for (int i = 0; i < n && i<m; i++) {
        if (s[i] == q[i]) {
            cout << i+1 << " ";
        }
    }

    return 0;
}
