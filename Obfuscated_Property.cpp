#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll fib[93];

void precompute_fibonacci() {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 93; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

ll find_max_fusc(int bit, ll a, ll b, bool is_less, ll n) {
    if (bit < 0) {
        return a;
    }
    
    if (is_less) {
        ll m = bit + 1;
        return max(a, b) * fib[m + 1] + min(a, b) * fib[m];
    }

    int n_bit = (n >> bit) & 1;
    
    if (n_bit == 0) {
        return find_max_fusc(bit - 1, a, a + b, false, n);
    } else {
        ll option_zero = find_max_fusc(bit - 1, a, a + b, true, n);
        ll option_one = find_max_fusc(bit - 1, a + b, b, false, n);
        
        return max(option_zero, option_one);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    precompute_fibonacci();

    int high_bit = 0;
    for (int i = 62; i >= 0; i--) {
        if ((n >> i) & 1) {
            high_bit = i;
            break;
        }
    }

    cout << find_max_fusc(high_bit, 0, 1, false, n) << endl;

    return 0;
}