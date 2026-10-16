#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u, v, strength;
};

struct Query {
    int start, weight, index;
};

class DSU {
private:
    vector<int> parent;
    vector<int> size;

public:
    explicit DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (size[a] < size[b]) {
            swap(a, b);
        }

        parent[b] = a;
        size[a] += size[b];
    }

    int componentSize(int x) {
        return size[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;

    while (cin >> N >> M >> Q) {
        vector<Edge> edges(M);

        for (Edge& edge : edges) {
            cin >> edge.u >> edge.v >> edge.strength;
        }

        vector<Query> queries(Q);

        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].start >> queries[i].weight;
            queries[i].index = i;
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.strength > b.strength;
        });

        sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
            return a.weight > b.weight;
        });

        DSU dsu(N);
        vector<int> answer(Q);
        int edgeIndex = 0;

        for (const Query& query : queries) {
            while (edgeIndex < M &&
                   edges[edgeIndex].strength >= query.weight) {
                dsu.unite(edges[edgeIndex].u, edges[edgeIndex].v);
                ++edgeIndex;
            }

            answer[query.index] = dsu.componentSize(query.start);
        }

        for (int result : answer) {
            cout << result << '\n';
        }
    }

    return 0;
}