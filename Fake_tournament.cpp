#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
private:
    int n;
    int timer;
    int componentCount;

    vector<vector<int>> graph;
    vector<int> discoveryTime;
    vector<int> lowLink;
    vector<int> component;
    vector<bool> inStack;
    stack<int> st;

    void dfs(int node) {
        discoveryTime[node] = lowLink[node] = ++timer;
        st.push(node);
        inStack[node] = true;

        for (int next : graph[node]) {
            if (discoveryTime[next] == 0) {
                dfs(next);
                lowLink[node] = min(lowLink[node], lowLink[next]);
            } else if (inStack[next]) {
                lowLink[node] = min(lowLink[node], discoveryTime[next]);
            }
        }

        // The node is the root of an SCC.
        if (lowLink[node] == discoveryTime[node]) {
            while (true) {
                int current = st.top();
                st.pop();

                inStack[current] = false;
                component[current] = componentCount;

                if (current == node) {
                    break;
                }
            }

            ++componentCount;
        }
    }

public:
    explicit TarjanSCC(const vector<vector<int>>& graph)
        : n(static_cast<int>(graph.size())),
          timer(0),
          componentCount(0),
          graph(graph),
          discoveryTime(n, 0),
          lowLink(n, 0),
          component(n, -1),
          inStack(n, false) {}

    vector<int> findComponents(int& numberOfComponents) {
        for (int node = 0; node < n; ++node) {
            if (discoveryTime[node] == 0) {
                dfs(node);
            }
        }

        numberOfComponents = componentCount;
        return component;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n;
        cin >> n;

        vector<vector<int>> graph(n);

        for (int participant = 0; participant < n; ++participant) {
            int betterCount;
            cin >> betterCount;

            for (int i = 0; i < betterCount; ++i) {
                int betterParticipant;
                cin >> betterParticipant;

                graph[betterParticipant - 1].push_back(participant);
            }
        }

        int componentCount;
        TarjanSCC sccFinder(graph);
        vector<int> component = sccFinder.findComponents(componentCount);

        vector<int> indegree(componentCount, 0);

        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                if (component[u] != component[v]) {
                    ++indegree[component[v]];
                }
            }
        }

        int sourceComponent = -1;
        int sourceCount = 0;

        for (int c = 0; c < componentCount; ++c) {
            if (indegree[c] == 0) {
                sourceComponent = c;
                ++sourceCount;
            }
        }

        if (sourceCount == 1) {
            int answer = 0;

            for (int participant = 0; participant < n; ++participant) {
                if (component[participant] == sourceComponent) {
                    ++answer;
                }
            }

            cout << answer << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}