#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    vector<int> T(N);
    for (int i = 0; i < N; ++i) cin >> T[i];

    unordered_map<int, int> pos; // value -> 1-based index
    const int TARGET = 100;

    for (int i = 0; i < N; ++i) {
        int x = T[i];
        int need = TARGET - x;
        auto it = pos.find(need);
        if (it != pos.end()) {
            int a = it->second;    // index of 'need' (1-based)
            int b = i + 1;         // current index (1-based)
            if (a > b) swap(a, b); // ensure ascending order
            cout << a << "\n" << b << "\n";
            return 0;
        }
        // store first occurrence only to keep earliest index
        if (!pos.count(x)) pos[x] = i + 1;
    }
    return 0; // per problem, a solution always exists
}
