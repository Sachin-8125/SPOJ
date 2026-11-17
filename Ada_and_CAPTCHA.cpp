#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    if (cin >> Q) {
        while (Q--) {
            long long N;
            cin >> N;
            
            long long k = N / 2;
            long long ans = 0;
            
            for (long long c = 0; (1LL << c) <= k; ++c) {
                long long count = (k >> c) - (k >> (c + 1));
                long long val = c + 2;
                ans += count * (val * val * val);
            }
            
            cout << ans << "\n";
        }
    }
    return 0;
}