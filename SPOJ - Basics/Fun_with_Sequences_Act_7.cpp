//  Fun with Sequences (Act 7)

#include <iostream>
#include <numeric>
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
    //compare both array sum
    int sSum = accumulate(s, s + n, 0);
    int qSum = accumulate(q, q + m, 0);
    if (m*sSum>n*qSum) {
        for (int i = 0; i < n; i++) {
            cout << s[i] << " ";
        }
    }else {
        for (int i = 0; i < m; i++) {
            cout << q[i] << " ";
        }
    }
    return 0;
}
