#include <iostream>
#include <vector>

using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int main() {
    fast_io();
    
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> prefA(n + 1, 0);
    vector<long long> prefB(k + 1, 0);

    for (int i = 1; i <= n; i++) {
        long long val;
        cin >> val;
        prefA[i] = prefA[i - 1] + val;
    }

    for (int j = 1; j <= k; j++) {
        long long val;
        cin >> val;
        prefB[j] = prefB[j - 1] + val;
    }

    bool twisted = false;

    int p = 0, q = 1;
    int r = 0, s = 1;
    
    while (q <= n && s <= k) {
        long long sumA = prefA[q] - prefA[p];
        long long sumB = prefB[s] - prefB[r];
        
        if (sumA == sumB) {
            twisted = true;
            break;
        } else if (sumA < sumB) {
            q++;
            if(q > n && p < n - 1) {
                p++;
                q = p + 1;
            }
        } else {
            s++;
            if(s > k && r < k - 1) {
                r++;
                s = r + 1;
            }
        }
    }

    if (twisted) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}