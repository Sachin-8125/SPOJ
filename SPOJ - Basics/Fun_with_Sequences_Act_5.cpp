//  Fun with Sequences (Act 5)

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n);
    for(int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    bool descending_order = true;
    bool request_order = true;

    for(int i = 1; i < n; ++i) {
        if (S[i] < S[i - 1] && !descending_order) {
            request_order = false;
            break;
        } else if (S[i] == S[i - 1]) {
            if (descending_order) {
                descending_order = !descending_order;
            } else {
                request_order = false;
                break;
            }
        } else if (S[i] > S[i - 1] && descending_order) {
            descending_order = !descending_order;
        }
    }

    if (request_order && !descending_order) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
