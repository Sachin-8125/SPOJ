#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

static inline int readInt() {
    int c = getchar_unlocked();
    while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
    int sign = 1;
    if (c == '-') { 
        sign = -1; 
        c = getchar_unlocked(); 
    }
    int x = 0;
    while (c >= '0' && c <= '9') { 
        x = x * 10 + (c - '0'); 
        c = getchar_unlocked(); 
    }
    return x * sign;
}

static vector<ll> M, K;

static inline bool bad(int l1, int l2, int l3) {
    return (__int128)(K[l3] - K[l1]) * (M[l1] - M[l2]) <= (__int128)(K[l2] - K[l1]) * (M[l1] - M[l3]);
}

int main() {
    int T = readInt();
    while (T--) {
        int n = readInt();
        ll a = readInt(), b = readInt(), c = readInt();

        vector<ll> S(n + 1, 0);
        for (int i = 1; i <= n; i++) S[i] = S[i - 1] + readInt();

        M.assign(n + 1, 0);
        K.assign(n + 1, 0);
        int head = 0, tail = 0;

M[tail] = 0; K[tail] = 0; tail++;

        ll dp = 0;
        for (int i = 1; i <= n; i++) {
            ll x = S[i];

            while (tail - head >= 2 && M[head] * x + K[head] <= M[head + 1] * x + K[head + 1]) head++;

            dp = M[head] * x + K[head] + a * x * x + b * x + c;

            ll m = -2 * a * x;
            ll k = dp + a * x * x - b * x;
            M[tail] = m; K[tail] = k;
            while (tail - head >= 2 && bad(tail - 2, tail - 1, tail)) {
                M[tail - 1] = m; K[tail - 1] = k;
                tail--;
            }
            tail++;
        }
        printf("%lld\n", dp);
    }
    return 0;
}