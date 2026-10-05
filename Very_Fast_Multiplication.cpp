#include <bits/stdc++.h>
using namespace std;

static const int P1 = 998244353, P2 = 1004535809, G = 3;
static const int BASE = 10000, CHUNK = 4;

long long mod_pow(long long a, long long e, int mod) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

template<int MOD>
void ntt(vector<int>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = (int)mod_pow(G, (MOD - 1) / len, MOD);
        if (invert) wlen = (int)mod_pow(wlen, MOD - 2, MOD);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j];
                int v = (int)(a[i + j + len / 2] * w % MOD);
                int x = u + v;
                if (x >= MOD) x -= MOD;
                int y = u - v;
                if (y < 0) y += MOD;
                a[i + j] = x;
                a[i + j + len / 2] = y;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = (int)mod_pow(n, MOD - 2, MOD);
        for (int& x : a) x = (int)((long long)x * inv_n % MOD);
    }
}

template<int MOD>
vector<int> convolution_mod(const vector<int>& a, const vector<int>& b, int n) {
    vector<int> x(a.begin(), a.end()), y(b.begin(), b.end());
    x.resize(n); y.resize(n);
    ntt<MOD>(x, false);
    ntt<MOD>(y, false);
    for (int i = 0; i < n; ++i) x[i] = (long long)x[i] * y[i] % MOD;
    ntt<MOD>(x, true);
    return x;
}

vector<int> parse(const string& s) {
    int first = (!s.empty() && (s[0] == '+' || s[0] == '-')) ? 1 : 0;
    vector<int> a;
    for (int r = (int)s.size(); r > first; r -= CHUNK) {
        int l = max(first, r - CHUNK), value = 0;
        for (int i = l; i < r; ++i) value = value * 10 + (s[i] - '0');
        a.push_back(value);
    }
    if (a.empty()) a.push_back(0);
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

string multiply(const string& sa, const string& sb) {
    vector<int> a = parse(sa), b = parse(sb);
    bool neg = ((!sa.empty() && sa[0] == '-') != (!sb.empty() && sb[0] == '-'));
    if (a.size() == 1 && a[0] == 0) return "0";
    if (b.size() == 1 && b[0] == 0) return "0";

    int need = (int)a.size() + (int)b.size() - 1;
    vector<long long> c(need);
    if ((long long)a.size() * b.size() <= 4096) {
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)b.size(); ++j)
                c[i + j] += (long long)a[i] * b[j];
    } else {
        int n = 1;
        while (n < need) n <<= 1;
        vector<int> r1 = convolution_mod<P1>(a, b, n);
        vector<int> r2 = convolution_mod<P2>(a, b, n);
        long long invP1modP2 = mod_pow(P1 % P2, P2 - 2LL, P2);
        for (int i = 0; i < need; ++i) {
            long long d = (r2[i] - (long long)r1[i]) % P2;
            if (d < 0) d += P2;
            long long k = d * invP1modP2 % P2;
            c[i] = r1[i] + (long long)P1 * k;
        }
    }

    long long carry = 0;
    for (long long& x : c) {
        x += carry;
        carry = x / BASE;
        x %= BASE;
    }
    while (carry) {
        c.push_back(carry % BASE);
        carry /= BASE;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();

    string ans = (neg ? "-" : "") + to_string(c.back());
    for (int i = (int)c.size() - 2; i >= 0; --i) {
        string part = to_string(c[i]);
        ans += string(CHUNK - part.size(), '0') + part;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        string a, b;
        cin >> a >> b;
        cout << multiply(a, b) << '\n';
    }
    return 0;
}