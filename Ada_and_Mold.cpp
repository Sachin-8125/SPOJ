#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> A(N);
    for (long long &x : A) {
        cin >> x;
    }

    // cost[l][r] = sum of A[i] XOR A[j] over all l <= i < j <= r
    vector<vector<long long>> cost(N, vector<long long>(N, 0));

    for (int r = 0; r < N; ++r) {
        long long addedPairs = 0;

        for (int l = r - 1; l >= 0; --l) {
            addedPairs += (A[l] ^ A[r]);
            cost[l][r] = cost[l][r - 1] + addedPairs;
        }
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> previous(N + 1, INF);
    vector<long long> current(N + 1, INF);
    previous[0] = 0;

    const int segments = K + 1;

    for (int s = 1; s <= segments; ++s) {
        fill(current.begin(), current.end(), INF);

        function<void(int, int, int, int)> compute =
            [&](int leftI, int rightI, int optLeft, int optRight) {
                if (leftI > rightI) return;

                int mid = (leftI + rightI) / 2;
                long long bestValue = INF;
                int bestSplit = -1;

                int start = max(optLeft, s - 1);
                int end = min(optRight, mid - 1);

                for (int j = start; j <= end; ++j) {
                    if (previous[j] == INF) continue;

                    long long candidate =
                        previous[j] + cost[j][mid - 1];

                    if (candidate < bestValue) {
                        bestValue = candidate;
                        bestSplit = j;
                    }
                }

                current[mid] = bestValue;

                if (bestSplit == -1) return;

                compute(leftI, mid - 1, optLeft, bestSplit);
                compute(mid + 1, rightI, bestSplit, optRight);
            };

        compute(s, N, s - 1, N - 1);
        swap(previous, current);
    }

    cout << previous[N] << '\n';
    return 0;
}
