#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353, ROOT = 3;

int modPow(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = 1LL * r * a % MOD;
        a = 1LL * a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<int>& a, bool inverse) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int root = modPow(ROOT, (MOD - 1) / len);
        if (inverse) root = modPow(root, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j];
                int v = 1LL * a[i + j + len / 2] * w % MOD;
                int sum = u + v, diff = u - v;
                if (sum >= MOD) sum -= MOD;
                if (diff < 0) diff += MOD;
                a[i + j] = sum;
                a[i + j + len / 2] = diff;
                w = 1LL * w * root % MOD;
            }
        }
    }
    if (inverse) {
        int invN = modPow(n, MOD - 2);
        for (int& x : a) x = 1LL * x * invN % MOD;
    }
}

// Little-endian base-100 digits, with leading zeros removed.
vector<int> parse(const string& s) {
    int start = (!s.empty() && (s[0] == '-' || s[0] == '+'));
    vector<int> a;
    for (int end = (int)s.size(); end > start; end -= 2) {
        int value = 0;
        for (int i = max(start, end - 2); i < end; ++i)
            value = value * 10 + s[i] - '0';
        a.push_back(value);
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

string multiply(const string& s, const string& t) {
    vector<int> a = parse(s), b = parse(t);
    if ((a.size() == 1 && a[0] == 0) ||
        (b.size() == 1 && b[0] == 0)) return "0";

    int need = (int)(a.size() + b.size() - 1);
    vector<int> c;
    if (a.size() * b.size() <= 4096) {
        c.assign(need, 0);
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)b.size(); ++j)
                c[i + j] += a[i] * b[j];
    } else {
        int n = 1;
        while (n < need) n <<= 1;
        a.resize(n); b.resize(n);
        ntt(a, false); ntt(b, false);
        for (int i = 0; i < n; ++i)
            a[i] = 1LL * a[i] * b[i] % MOD;
        ntt(a, true);
        c.assign(a.begin(), a.begin() + need);
    }

    long long carry = 0;
    for (int& x : c) {
        long long value = x + carry;
        x = value % 100;
        carry = value / 100;
    }
    while (carry) {
        c.push_back(carry % 100);
        carry /= 100;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();

    string result;
    if ((s[0] == '-') != (t[0] == '-')) result += '-';
    result += to_string(c.back());
    for (int i = (int)c.size() - 2; i >= 0; --i) {
        result += char('0' + c[i] / 10);
        result += char('0' + c[i] % 10);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        string a, b;
        cin >> a >> b;
        cout << multiply(a, b) << '\n';
    }
}