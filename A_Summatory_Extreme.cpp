#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

static const int64 MOD = 1234567891LL;
static const int MAX_K = 10000000;

int64 modPow(int64 a, int64 e) {
    int64 result = 1;

    while (e > 0) {
        if (e & 1) {
            result = (int64)((i128)result * a % MOD);
        }

        a = (int64)((i128)a * a % MOD);
        e >>= 1;
    }

    return result;
}

struct Query {
    int64 n;
    int k;
    int id;
};

struct AnswerData {
    vector<int64> values;
    vector<int64> prefixFactorial;
    vector<int64> inverseFactorial;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<Query> queries(T);
    unordered_map<int, vector<Query>> grouped;

    grouped.reserve(T * 2);

    for (int i = 0; i < T; ++i) {
        int64 n;
        int k;

        cin >> n >> k;

        queries[i] = {n, k, i};
        grouped[k].push_back(queries[i]);
    }

    vector<int64> answer(T);

    for (auto &entry : grouped) {
        int k = entry.first;
        vector<Query> &tests = entry.second;

        int degree = k + 2;
        int points = degree + 1;

        vector<int64> y(points, 0);

        int64 currentPower = 0;
        int64 currentF = 0;
        int64 currentG = 0;

        y[0] = 0;

        for (int x = 1; x <= degree; ++x) {
            currentPower = modPow(x, k);
            currentF += currentPower;

            if (currentF >= MOD) {
                currentF -= MOD;
            }

            currentG += currentF;

            if (currentG >= MOD) {
                currentG -= MOD;
            }

            y[x] = currentG;
        }

        vector<int64> factorial(points);
        vector<int64> inverseFactorial(points);

        factorial[0] = 1;

        for (int i = 1; i < points; ++i) {
            factorial[i] =
                (int64)((i128)factorial[i - 1] * i % MOD);
        }

        inverseFactorial[degree] =
            modPow(factorial[degree], MOD - 2);

        for (int i = degree; i >= 1; --i) {
            inverseFactorial[i - 1] =
                (int64)((i128)inverseFactorial[i] * i % MOD);
        }

        for (const Query &query : tests) {
            int64 n = query.n;

            if (n <= degree) {
                answer[query.id] = y[n];
                continue;
            }

            int64 x = n % MOD;

            vector<int64> prefix(points + 1, 1);
            vector<int64> suffix(points + 1, 1);

            for (int i = 0; i <= degree; ++i) {
                prefix[i + 1] =
                    (int64)((i128)prefix[i] * ((x - i + MOD) % MOD) % MOD);
            }

            for (int i = degree; i >= 0; --i) {
                suffix[i] =
                    (int64)((i128)suffix[i + 1] * ((x - i + MOD) % MOD) % MOD);
            }

            int64 result = 0;

            for (int i = 0; i <= degree; ++i) {
                int64 numerator =
                    (int64)((i128)prefix[i] * suffix[i + 1] % MOD);

                int64 denominator =
                    (int64)((i128)inverseFactorial[i] *
                            inverseFactorial[degree - i] % MOD);

                int64 term =
                    (int64)((i128)y[i] * numerator % MOD);
                term =
                    (int64)((i128)term * denominator % MOD);

                if ((degree - i) & 1) {
                    result -= term;

                    if (result < 0) {
                        result += MOD;
                    }
                } else {
                    result += term;

                    if (result >= MOD) {
                        result -= MOD;
                    }
                }
            }

            answer[query.id] = result;
        }
    }

    for (int i = 0; i < T; ++i) {
        cout << answer[i] << '\n';
    }

    return 0;
}