#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n, k, m, pro;
        cin >> n >> k >> m;
        int i = 0;

        if (k <= m / n) {
            i++;
            pro = n * k;
            while (k <= m / pro) {
                i++;
                pro *= k;
            }
        }

        cout << i << '\n';
    }
    return 0;
}

