#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    vector<int> queries(q);
    int maxN = 1;
    for (int &n : queries) {
        cin >> n;
        maxN = max(maxN, n);
    }

    vector<int> phi(maxN + 1);
    for (int i = 0; i <= maxN; ++i) phi[i] = i;
    for (int p = 2; p <= maxN; ++p) {
        if (phi[p] == p) { 
            for (int x = p; x <= maxN; x += p)
                phi[x] -= phi[x] / p;
        }
    }

    vector<long long> answer(maxN + 1);
    for (int n = 1; n <= maxN; ++n)
        answer[n] = 1LL * n * n;

    for (int m = 2; m <= maxN; ++m) {
        const long long coprimeSum = 1LL * m * phi[m] / 2;
        for (int d = 1; d <= maxN / m; ++d) {
            const int n = d * m;
            answer[n] += 1LL * d * d * coprimeSum;
        }
    }

    for (int n : queries)
        cout << answer[n] << '\n';

    return 0;
}