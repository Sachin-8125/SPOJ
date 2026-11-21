#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int SMALL_PRIMES[12] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
};

int memo[1 << 12][10];
long long prod_mask[1 << 12];

int compute_direct(int mask, int r) {
    long long m = prod_mask[mask];
    int limit = static_cast<int>(m / 2) + 200;
    vector<uint8_t> is_comp(limit + 1, 0);

    for (int i = 0; i < 12; ++i) {
        if (mask & (1 << i)) {
            int p = SMALL_PRIMES[i];
            for (int j = p; j <= limit; j += p) {
                is_comp[j] = 1;
            }
        }
    }
                                                                       
    int first_r[16];
    int found = 0;
    for (int x = 1; x <= limit && found < r; ++x) {
        if (!is_comp[x]) {
            first_r[found++] = x;
        }
    }
                                              
    int ring[16];
    for (int i = 0; i < r; ++i) {
        ring[i] = -first_r[r - 1 - i];
    }

    int idx = 0;
    int max_gap = 0;
    for (int x = 1; x <= limit; ++x) {
        if (!is_comp[x]) {
            int gap = x - ring[idx];
            if (gap > max_gap) max_gap = gap;
            ring[idx] = x;
            if (++idx == r) idx = 0;
        }
    }
    return max_gap;
}

int get_g(int mask, int r) {
    if (mask == 0) return r;
    if (memo[mask][r]) return memo[mask][r];

    int k = 31 - __builtin_clz(mask);
    int p = SMALL_PRIMES[k];
    int sub = mask ^ (1 << k);

    int v = get_g(sub, r + 1);
    if (p >= v) {
        return memo[mask][r] = v;
    }
    return memo[mask][r] = compute_direct(mask, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    vector<int> queries(T);
    int maxN = 1;
    for (int i = 0; i < T; ++i) {
        cin >> queries[i];
        if (queries[i] > maxN) maxN = queries[i];
    }
                                         
    prod_mask[0] = 1;
    for (int mask = 1; mask < (1 << 12); ++mask) {
        int bit = __builtin_ctz(mask);
        long long prev = prod_mask[mask ^ (1 << bit)];
        if (prev > maxN) {
            prod_mask[mask] = maxN + 1LL;
        } else {
            prod_mask[mask] = prev * SMALL_PRIMES[bit];
        }
    }                                                                
                                                                                
    vector<uint16_t> state(maxN + 1, 0);
                               
    for (int i = 0; i < 12; ++i) {
        int p = SMALL_PRIMES[i];
        uint16_t bit = static_cast<uint16_t>(1u << i);
        for (int j = p; j <= maxN; j += p) {
            state[j] |= bit;
        }
    }
                                                                    
    vector<uint8_t> is_comp(maxN + 1, 0);
    for (int i = 2; 1LL * i * i <= maxN; ++i) {
        if (!is_comp[i]) {
            for (int j = i * i; j <= maxN; j += i) {
                is_comp[j] = 1;
            }
        }
    }

    for (int p = 41; p <= maxN; ++p) {
        if (!is_comp[p]) {
            for (int j = p; j <= maxN; j += p) {
                state[j] += (1u << 12);
            }
        }
    }
                                                                            
    static uint8_t G[1 << 12][5];
    static constexpr long long LARGE_THRESH[5] = {
        1LL, 41LL, 41LL * 43, 41LL * 43 * 47, 41LL * 43 * 47 * 53
    };
    for (int mask = 0; mask < (1 << 12); ++mask) {
        if (prod_mask[mask] > maxN) continue;
        for (int t = 0; t < 5; ++t) {
            if (prod_mask[mask] <= maxN / LARGE_THRESH[t]) {
                G[mask][t] = static_cast<uint8_t>(get_g(mask, t + 1));
            }
        }
    }
                             
    vector<uint32_t> pref(maxN + 1, 0);
    for (int n = 1; n <= maxN; ++n) {
        uint16_t st = state[n];
        pref[n] = pref[n - 1] + G[st & 4095u][st >> 12];
    }

    for (int n : queries) {
        cout << pref[n] << '\n';
    }

    return 0;
}