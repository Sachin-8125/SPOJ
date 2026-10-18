#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

unsigned long long isqrt(unsigned long long n) {
    unsigned long long x = sqrt(n);
    while ((x + 1) * (x + 1) <= n) x++;
    while (x * x > n) x--;
    return x;
}

struct Matrix {
    long long m[3][3];
    Matrix() { memset(m, 0, sizeof(m)); }
};

Matrix mul(Matrix a, Matrix b, long long M) {
    Matrix res;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                res.m[i][j] = (res.m[i][j] + (a.m[i][k] % M) * (b.m[k][j] % M)) % M;
            }
        }
    }
    return res;
}

Matrix power(Matrix a, long long b, long long M) {
    Matrix res;
    res.m[0][0] = res.m[1][1] = res.m[2][2] = 1;
    while (b > 0) {
        if (b & 1) res = mul(res, a, M);
        a = mul(a, a, M);
        b >>= 1;
    }
    return res;
}

long long power_mod(long long a, long long b, long long M) {
    long long res = 1;
    a %= M;
    while (b > 0) {
        if (b & 1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

void solve(int tc) {
    long long N, B, M;
    cin >> N >> B >> M;

    long long S = 1LL * N * (N + 1) / 2;
    long long min_diff = S % 2;
    long long Target = S / 2;

    long long K = isqrt(2ULL * Target);
    if (K * (K + 1) / 2 > Target) {
        K--;
    }

    long long ans_p = -1, ans_x = -1, ans_c = -1;

    for (long long p = K; p >= 0; p--) {
        long long R = Target - p * (p + 1) / 2;
        long long c_exact = -1;
        
        long long D1 = (2 * N + 1) * (2 * N + 1) - 8 * R;
        if (D1 >= 0) {
            long long sqD1 = isqrt(D1);
            if (sqD1 * sqD1 == D1) {
                if ((2 * N + 1 - sqD1) % 2 == 0) {
                    long long c = (2 * N + 1 - sqD1) / 2;
                    if (c >= 0 && c <= N && p < N - c + 1) {
                        c_exact = c;
                    }
                }
            }
        }

        long long c_x = -1, x_val = -1;
        long long Rem = R - p - 1;
        if (Rem >= 0) {
            long long D2 = (2 * N + 1) * (2 * N + 1) - 8 * Rem;
            if (D2 >= 0) {
                long long sqD2 = isqrt(D2);
                long long c = (2 * N + 1 - sqD2) / 2;
                if (c > N) c = N;
                while (c >= 0) {
                    long long S_suff = c * N - c * (c - 1) / 2;
                    if (S_suff <= Rem) break;
                    c--;
                }
                if (c >= 0 && c <= N) {
                    long long S_suff = c * N - c * (c - 1) / 2;
                    long long x = R - S_suff;
                    if (x > p && x <= N - c) {
                        c_x = c;
                        x_val = x;
                    }
                }
            }
        }

        long long best_c = -1, best_x = -1, next_element = 2e18;

        if (c_exact != -1) {
            long long nxt = N - c_exact + 1;
            if (nxt < next_element) {
                next_element = nxt;
                best_c = c_exact;
                best_x = 0;
            }
        }

        if (c_x != -1) {
            long long nxt = x_val;
            if (nxt < next_element) {
                next_element = nxt;
                best_c = c_x;
                best_x = x_val;
            }
        }

        if (best_c != -1) {
            ans_p = p;
            ans_c = best_c;
            ans_x = best_x;
            break;
        }
    }

    long long hash_val = 0;

    if (ans_p > 0) {
        Matrix mat;
        mat.m[0][0] = B % M; mat.m[0][1] = 1; mat.m[0][2] = 0;
        mat.m[1][0] = 0;     mat.m[1][1] = 1; mat.m[1][2] = 1;
        mat.m[2][0] = 0;     mat.m[2][1] = 0; mat.m[2][2] = 1;

        mat = power(mat, ans_p, M);
        hash_val = (mat.m[0][1] + mat.m[0][2]) % M;
    }

    if (ans_x > 0) {
        hash_val = (hash_val * (B % M) + (ans_x % M)) % M;
    }

    if (ans_c > 0) {
        Matrix mat;
        mat.m[0][0] = B % M; mat.m[0][1] = 1; mat.m[0][2] = 0;
        mat.m[1][0] = 0;     mat.m[1][1] = 1; mat.m[1][2] = 1;
        mat.m[2][0] = 0;     mat.m[2][1] = 0; mat.m[2][2] = 1;

        mat = power(mat, ans_c, M);
        long long start_val = N - ans_c + 1;
        long long val = ((mat.m[0][1] * (start_val % M)) % M + mat.m[0][2]) % M;

        long long Bc = power_mod(B, ans_c, M);
        hash_val = ((hash_val * Bc) % M + val) % M;
    }

    cout << "Case " << tc << ": " << min_diff << " " << hash_val << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; i++) {
            solve(i);
        }
    }
    return 0;
}
