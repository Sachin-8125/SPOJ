#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Edge {
    int to;
    int cost;
};

vector<ll> dijkstra(int source, const vector<vector<Edge>>& graph) {
    int n = graph.size() - 1;
    vector<ll> dist(n + 1, INF);

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [currentDist, node] = pq.top();
        pq.pop();

        if (currentDist != dist[node]) {
            continue;
        }

        for (const Edge& edge : graph[node]) {
            ll newDist = currentDist + edge.cost;

            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                pq.push({newDist, edge.to});
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int P, Q;
        cin >> P >> Q;

        vector<vector<Edge>> graph(P + 1);
        vector<vector<Edge>> reversedGraph(P + 1);

        for (int i = 0; i < Q; ++i) {
            int from, to, cost;
            cin >> from >> to >> cost;

            graph[from].push_back({to, cost});
            reversedGraph[to].push_back({from, cost});
        }

        vector<ll> fromCCS = dijkstra(1, graph);

        vector<ll> toCCS = dijkstra(1, reversedGraph);

        ll answer = 0;

        for (int stop = 1; stop <= P; ++stop) {
            answer += fromCCS[stop] + toCCS[stop];
        }

        cout << answer << '\n';
    }

    return 0;
}