#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v;
    long long weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        while (i != parent[i]) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j])
                rank[root_i]++;
            return true;
        }
        return false;
    }
};

void solve() {
    int s;
    if (!(cin >> s)) return;

    while (s--) {
        int n;
        cin >> n;

        vector<Edge> edges;
        for (int i = 1; i <= n; ++i) {
            string name;
            int p;
            cin >> name >> p;
            for (int j = 0; j < p; ++j) {
                int neigh;
                long long cost;
                cin >> neigh >> cost;
                if (i < neigh) {
                    edges.push_back({i, neigh, cost});
                } else {
                    edges.push_back({neigh, i, cost});
                }
            }
        }

        sort(edges.begin(), edges.end());

        DSU dsu(n);
        long long mst_cost = 0;
        int edges_used = 0;

        for (const auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                mst_cost += edge.weight;
                edges_used++;
                if (edges_used == n - 1) break;
            }
        }

        cout << mst_cost << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}