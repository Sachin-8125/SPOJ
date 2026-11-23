#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct Result {
    int64 cost = 0;
    int64 singles = 0;
    int64 families = 0;
};

Result operator+(const Result& a, const Result& b) {
    return {
        a.cost + b.cost,
        a.singles + b.singles,
        a.families + b.families
    };
}

Result better(const Result& a, const Result& b) {
    if (a.cost != b.cost)
        return a.cost < b.cost ? a : b;

    return (a.singles + a.families <= b.singles + b.families) ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 S = 0, F = 0;
    int testCase = 0;

    unordered_map<string, int> id;
    vector<vector<int>> children;
    vector<bool> hasParent;

    auto getId = [&](const string& name) -> int {
        auto it = id.find(name);
        if (it != id.end())
            return it->second;

        int newId = static_cast<int>(children.size());
        id.emplace(name, newId);
        children.emplace_back();
        hasParent.push_back(false);
        return newId;
    };

    auto solve = [&]() {
        int n = static_cast<int>(children.size());

        vector<int> order;
        order.reserve(n);

        for (int i = 0; i < n; ++i) {
            if (!hasParent[i])
                order.push_back(i);
        }

        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (int v : children[u])
                order.push_back(v);
        }

        vector<array<Result, 2>> dp(n);

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];

            Result family{F, 0, 1};
            for (int v : children[u])
                family = family + dp[v][1];

            Result noFamily;
            for (int v : children[u])
                noFamily = noFamily + dp[v][0];

            Result single = noFamily + Result{S, 1, 0};

            dp[u][0] = better(family, single);
            dp[u][1] = better(family, noFamily);
        }

        Result answer;
        for (int i = 0; i < n; ++i) {
            if (!hasParent[i])
                answer = answer + dp[i][0];
        }

        cout << ++testCase << ". "
             << answer.singles << ' '
             << answer.families << ' '
             << answer.cost << '\n';
    };

    string line;
    bool haveCase = false;

    while (getline(cin, line)) {
        size_t pos = line.find_first_not_of(" \t\r\n");
        if (pos == string::npos)
            continue;

        if (isdigit(static_cast<unsigned char>(line[pos]))) {
            if (haveCase)
                solve();

            const char* p = line.c_str() + pos;
            char* end;
            S = strtoll(p, &end, 10);
            F = strtoll(end, nullptr, 10);

            if (S == 0 && F == 0)
                break;

            id.clear();
            children.clear();
            hasParent.clear();
            haveCase = true;
        } else {
            int parent = -1;
            size_t i = pos;

            while (i < line.size()) {
                while (i < line.size() &&
                       isspace(static_cast<unsigned char>(line[i])))
                    ++i;

                if (i == line.size())
                    break;

                size_t start = i;
                while (i < line.size() &&
                       !isspace(static_cast<unsigned char>(line[i])))
                    ++i;

                int person = getId(line.substr(start, i - start));

                if (parent == -1) {
                    parent = person;
                } else {
                    children[parent].push_back(person);
                    hasParent[person] = true;
                }
            }
        }
    }

    return 0;
}