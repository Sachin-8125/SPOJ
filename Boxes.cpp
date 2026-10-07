#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MOD = 10007;
int comb[105][105];

void precompute() {
    for (int i = 0; i <= 100; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}

void solve(int tc) {
    int n, W;
    if (!(cin >> n >> W)) return;
    
    map<int, int> freq;
    int total_w = 0;
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        freq[w]++;
        total_w += w;
    }

    vector<pair<int, int>> items;
    for (auto it = freq.rbegin(); it != freq.rend(); ++it) {
        items.push_back({it->first, it->second});
    }

    int K = items.size();
    vector<int> S_cnt(K), S_w(K), S_perms(K);
    int suf_cnt = 0, suf_w = 0, suf_perms = 1;
    
    for (int m = K - 1; m >= 0; --m) {
        S_cnt[m] = suf_cnt;
        S_w[m] = suf_w;
        S_perms[m] = suf_perms;
        suf_cnt += items[m].second;
        suf_w += items[m].second * items[m].first;
        suf_perms = (suf_perms * comb[suf_cnt][items[m].second]) % MOD;
    }

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    dp[0][0] = 1;
    long long ans = 0;
    int cur_cnt = 0, cur_w = 0;

    for (int m = 0; m < K; ++m) {
        int S = items[m].first;
        int C = items[m].second;

        for (int c = 0; c < C; ++c) {
            int cnt_fixed = S_cnt[m] + c;
            int w_fixed = S_w[m] + c * S;
            if (w_fixed > W) continue;

            long long P = (S_perms[m] * comb[cnt_fixed][c]) % MOD;

            for (int cnt = 0; cnt <= min(n - cnt_fixed, cur_cnt); ++cnt) {
                for (int w = 0; w <= min(W - w_fixed, cur_w); ++w) {
                    if (dp[cnt][w] > 0) {
                        int W_tot = w + w_fixed;
                        int C_tot = cnt + cnt_fixed;
                        
                        if (W_tot <= W && W - S < W_tot) {
                            long long ways = (dp[cnt][w] * P) % MOD;
                            ways = (ways * comb[C_tot][cnt_fixed]) % MOD;
                            ans = (ans + ways) % MOD;
                        }
                    }
                }
            }
        }

        vector<vector<int>> next_dp(n + 1, vector<int>(W + 1, 0));
        for (int c = 0; c <= C; ++c) {
            for (int cnt = 0; cnt <= cur_cnt && cnt + c <= n; ++cnt) {
                for (int w = 0; w <= cur_w && w + c * S <= W; ++w) {
                    if (dp[cnt][w] > 0) {
                        long long ways = (dp[cnt][w] * comb[cnt + c][c]) % MOD;
                        next_dp[cnt + c][w + c * S] = (next_dp[cnt + c][w + c * S] + ways) % MOD;
                    }
                }
            }
        }
        
        dp = next_dp;
        cur_cnt += C;
        cur_w = min(W, cur_w + C * S);
    }

    if (total_w <= W) {
        ans = (ans + dp[n][total_w]) % MOD;
    }

    cout << "Case " << tc << ": " << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    
    return 0;
}