#include <bits/stdc++.h>
using namespace std;

int hashKey(const string& s) {
    long long h = 0;
    for (size_t i = 0; i < s.size(); ++i)
        h += (long long)(unsigned char)s[i] * (long long)(i + 1);
    return (int)((19 * h) % 101);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n;
        cin >> n;

        vector<string> table(101);
        vector<bool> used(101, false);

        for (int i = 0; i < n; ++i) {
            string line;
            cin >> line;

            string op = line.substr(0, 3);
            string key = line.substr(4);

            int h = hashKey(key);
            int found = -1;

            for (int j = 0; j < 20; ++j) {
                int p = (h + j * j + 23 * j) % 101;
                if (used[p] && table[p] == key) {
                    found = p;
                    break;
                }
            }

            if (op == "ADD") {
                if (found != -1) continue;

                for (int j = 0; j < 20; ++j) {
                    int p = (h + j * j + 23 * j) % 101;
                    if (!used[p]) {
                        used[p] = true;
                        table[p] = key;
                        break;
                    }
                }
            } else if (found != -1) {
                used[found] = false;
                table[found].clear();
            }
        }

        int cnt = 0;
        for (int i = 0; i < 101; ++i)
            if (used[i]) ++cnt;

        cout << cnt << '\n';

        for (int i = 0; i < 101; ++i)
            if (used[i]) cout << i << ':' << table[i] << '\n';
    }

    return 0;
}