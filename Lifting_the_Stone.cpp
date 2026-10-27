#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

static char buf[1 << 25];
int bufLen = 0, bufPos = 0;
inline int readChar() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1;
    }
    return buf[bufPos++];
}
inline bool readInt(ll &out) {
    int c = readChar();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = readChar();
    if (c == -1) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = readChar(); }
    ll v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = readChar(); }
    out = neg ? -v : v;
    return true;
}

void printRounded(lll num, lll den) {
    if (den < 0) { den = -den; num = -num; }
    bool neg = num < 0;
    lll a = neg ? -num : num;
    lll r = (a * 200 + den) / (2 * den);
    if (r == 0) neg = false;
    lll ip = r / 100, fp = r % 100;
    printf("%s%lld.%02lld", neg ? "-" : "", (ll)ip, (ll)fp);
}

int main() {
    ll T;
    if (!readInt(T)) return 0;
    while (T--) {
        ll n;
        readInt(n);
        vector<ll> x(n), y(n);
        for (ll i = 0; i < n; i++) readInt(x[i]), readInt(y[i]);
        ll ox = x[0], oy = y[0];
        lll A2 = 0, Sx = 0, Sy = 0;
        for (ll i = 0; i < n; i++) {
            ll j = (i + 1) % n;
            ll xi = x[i] - ox, yi = y[i] - oy;
            ll xj = x[j] - ox, yj = y[j] - oy;
            ll cr = xi * yj - xj * yi;
            A2 += cr;
            Sx += (lll)(xi + xj) * cr;
            Sy += (lll)(yi + yj) * cr;
        }
        lll den = 3 * A2;
        lll nx = Sx + (lll)ox * den;
        lll ny = Sy + (lll)oy * den;
        printRounded(nx, den);
        printf(" ");
        printRounded(ny, den);
        printf("\n");
    }
    return 0;
}