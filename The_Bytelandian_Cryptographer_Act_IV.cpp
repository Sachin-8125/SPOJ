#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct FastBitset {
    vector<uint64_t> a;
    int n_words;
    
    FastBitset() : n_words(0) {}
    
    FastBitset(int bits) {
        n_words = (bits + 63) / 64;
        a.assign(n_words, 0);
    }
    
    void set(int i) {
        a[i / 64] |= (1ULL << (i % 64));
    }
    
    bool test(int i) const {
        if (i / 64 >= n_words) return false;
        return (a[i / 64] >> (i % 64)) & 1;
    }
    
    void or_shift_right(const FastBitset& Y, int x) {
        int word_shift = x / 64;
        int bit_shift = x % 64;
        if (word_shift >= Y.n_words) return;
        
        int limit = Y.n_words - word_shift;
        if (limit > n_words) limit = n_words;
        
        if (bit_shift == 0) {
            for (int i = 0; i < limit; ++i) {
                a[i] |= Y.a[i + word_shift];
            }
        } else {
            int inv = 64 - bit_shift;
            for (int i = 0; i < limit; ++i) {
                uint64_t val = (Y.a[i + word_shift] >> bit_shift);
                if (i + word_shift + 1 < Y.n_words) {
                    val |= (Y.a[i + word_shift + 1] << inv);
                }
                a[i] |= val;
            }
        }
    }
};

void solve() {
    int m;
    if (!(cin >> m)) return;
    
    string x, y;
    cin >> x >> y;
    
    int len = min(x.length(), y.length());
    x.resize(len); 
    
    vector<int> P(len, -1);
    vector<int> pos[26];
    
    for (int i = 0; i < len; ++i) {
        if (x[i] != '*' && y[i] != '*') {
            int val = (y[i] - x[i]) % 26;
            if (val < 0) val += 26;
            
            P[i] = val;
            pos[P[i]].push_back(i);
        }
    }
    
    FastBitset B[26], B_rev[26];
    for (int c = 0; c < 26; ++c) {
        if (!pos[c].empty()) {
            B[c] = FastBitset(len);
            B_rev[c] = FastBitset(len);
            for (int i : pos[c]) {
                B[c].set(i);
                B_rev[c].set(len - 1 - i);
            }
        }
    }
    
    vector<bool> bad(len + 1, false);
    FastBitset bad_bits(len + 1);
    
    for (int c1 = 0; c1 < 26; ++c1) {
        if (pos[c1].empty()) continue;
        for (int c2 = c1 + 1; c2 < 26; ++c2) {
            if (pos[c2].empty()) continue;
            
            long long loop_cost = (long long)pos[c1].size() * pos[c2].size();
            long long shift_cost = (long long)min(pos[c1].size(), pos[c2].size()) * ((len + 63) / 64);
            
            if (loop_cost <= shift_cost * 8) {
                for (int i : pos[c1]) {
                    for (int j : pos[c2]) {
                        bad[abs(i - j)] = true;
                    }
                }
            } else {
                if (pos[c1].size() <= pos[c2].size()) {
                    for (int i : pos[c1]) {
                        bad_bits.or_shift_right(B[c2], i);
                        bad_bits.or_shift_right(B_rev[c2], len - 1 - i);
                    }
                } else {
                    for (int j : pos[c2]) {
                        bad_bits.or_shift_right(B[c1], j);
                        bad_bits.or_shift_right(B_rev[c1], len - 1 - j);
                    }
                }
            }
        }
    }
    
    for (int k = 1; k <= len; ++k) {
        if (!bad[k] && bad_bits.test(k)) {
            bad[k] = true;
        }
    }
    
    vector<bool> valid(m + 1, true);
    for (int n = 1; n <= m; ++n) {
        for (int k = n; k <= len; k += n) {
            if (bad[k]) {
                valid[n] = false;
                break;
            }
        }
    }
    
    vector<int> active;
    for (int i = 0; i < len; ++i) {
        if (x[i] == '*' && y[i] != '*') {
            active.push_back(i);
        }
    }
    
    vector<int> determined(len, -1);
    vector<int> cached_shift(m + 1, -2);
    
    for (int n = 1; n <= m; ++n) {
        if (!valid[n]) continue;
        if (active.empty()) break; 
        
        vector<int> next_active;
        vector<int> touched;
        
        for (int i : active) {
            int r = i % n;
            if (cached_shift[r] == -2) {
                int shift = -1;
                for (int j = r; j < len; j += n) {
                    if (P[j] != -1) {
                        shift = P[j];
                        break;
                    }
                }
                cached_shift[r] = shift;
                touched.push_back(r);
            }
            
            int shift = cached_shift[r];
            if (shift == -1) continue; 
            
            int char_val = ((y[i] - 'A' - shift) % 26 + 26) % 26;
            if (determined[i] == -1) {
                determined[i] = char_val;
                next_active.push_back(i);
            } else if (determined[i] == char_val) {
                next_active.push_back(i);
            }
        }
        
        for (int r : touched) {
            cached_shift[r] = -2;
        }
        active = move(next_active);
    }
    
    for (int i : active) {
        if (determined[i] != -1) {
            x[i] = determined[i] + 'A';
        }
    }
    
    cout << x << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}