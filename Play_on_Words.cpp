#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int parent[26], size[26];
    DSU() {
        iota(parent, parent + 26, 0);
        fill(size, size + 26, 1);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int n;
        cin >> n;

        int indegree[26] = {}, outdegree[26] = {};
        bool active[26] = {};
        DSU dsu;

        for (int i = 0; i < n; ++i) {
            string word;
            cin >> word;
            int from = word.front() - 'a';
            int to = word.back() - 'a';
            ++outdegree[from];
            ++indegree[to];
            active[from] = active[to] = true;
            dsu.unite(from, to);
        }

        bool possible = true;
        int startCount = 0, endCount = 0;

        for (int c = 0; c < 26; ++c) {
            int diff = outdegree[c] - indegree[c];
            if (diff == 1) ++startCount;
            else if (diff == -1) ++endCount;
            else if (diff != 0) possible = false;
        }

        if (!((startCount == 0 && endCount == 0) ||
              (startCount == 1 && endCount == 1))) {
            possible = false;
        }

        int component = -1;
        for (int c = 0; c < 26; ++c) {
            if (active[c]) {
                if (component == -1) component = dsu.find(c);
                else if (dsu.find(c) != component) possible = false;
            }
        }

        cout << (possible ? "Ordering is possible.\n"
                          : "The door cannot be opened.\n");
    }

    return 0;
}