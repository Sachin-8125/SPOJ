#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
 
using namespace std;
 
const int INF = 1e9 + 7;
 
struct Edge {
    int to;
    int cost;
};
 
int dijkstra(int start, int target, int n, const vector<vector<Edge>>& adj) {
    if (start == target) return 0;
 
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
 
    dist[start] = 0;
    pq.push({0, start});
 
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
 
        if (u == target) {
            return d;
        }
 
        if (d > dist[u]) {
            continue;
        }
 
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.cost;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
 
    return dist[target];
}
 
void solve() {
    int n;
    if (!(cin >> n)) return;
 
    unordered_map<string, int> city_to_id;
    city_to_id.reserve(n * 2);
 
    vector<vector<Edge>> adj(n + 1);
 
    for (int i = 1; i <= n; ++i) {
        string name;
        cin >> name;
        city_to_id[name] = i;
 
        int p;
        cin >> p;
        adj[i].reserve(p);
        for (int j = 0; j < p; ++j) {
            int neighbor, cost;
            cin >> neighbor >> cost;
            adj[i].push_back({neighbor, cost});
        }
    }
 
    int q;
    cin >> q;
    while (q--) {
        string source_name, dest_name;
        cin >> source_name >> dest_name;
        int u = city_to_id[source_name];
        int v = city_to_id[dest_name];
        cout << dijkstra(u, v, n, adj) << "\n";
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int test_cases;
    if (cin >> test_cases) {
        while (test_cases--) {
            solve();
        }
    }
 
    return 0;
}