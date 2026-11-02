#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000 + 5;
static const int MAXC = 100000 + 5;
static const int LOG = 17;

int n, q;
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN], depth[MAXN], par[MAXN];
int up[MAXN][LOG];
int euler[MAXN * 2];
int timerN;

int col[MAXN];
bool inSet[MAXN];
int freq[MAXC];
long long curAns;
int BLOCK;

struct Update {
    int node, prev, nxt;
};

struct Query {
    int l, r, t, idx, extra; 
};

vector<Update> updates;
vector<Query> queries;

void dfsIter(int root) {
    timerN = 0;
    vector<int> stk;
    vector<int> it(n, 0);
    vector<char> started(n, 0);
    par[root] = -1;
    depth[root] = 0;
    up[root][0] = root;
    stk.push_back(root);
    while (!stk.empty()) {
        int u = stk.back();
        if (!started[u]) {
            started[u] = 1;
            tin[u] = timerN;
            euler[timerN++] = u;
        }
        if (it[u] < (int)adj[u].size()) {
            int v = adj[u][it[u]++];
            if (v == par[u]) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            up[v][0] = u;
            stk.push_back(v);
        } else {
            tout[u] = timerN;
            euler[timerN++] = u;
            stk.pop_back();
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int k = 0; k < LOG; ++k)
        if (diff & (1 << k)) a = up[a][k];
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }
    return up[a][0];
}

inline void toggle(int node) {
    int c = col[node];
    if (inSet[node]) {
        --freq[c];
        curAns -= freq[c];
        inSet[node] = false;
    } else {
        curAns += freq[c];
        ++freq[c];
        inSet[node] = true;
    }
}

inline void applyUpdate(int id, bool forward) {
    const Update &u = updates[id];
    int to = forward ? u.nxt : u.prev;
    if (inSet[u.node]) {
        int c = col[u.node];
        --freq[c];
        curAns -= freq[c];
        col[u.node] = to;
        curAns += freq[to];
        ++freq[to];
    } else {
        col[u.node] = to;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> q)) return 0;
    for (int i = 0; i < n; ++i) cin >> col[i];
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsIter(0);

    for (int k = 1; k < LOG; ++k)
        for (int i = 0; i < n; ++i)
            up[i][k] = up[up[i][k - 1]][k - 1];

    vector<int> now(col, col + n);
    vector<long long> answers;
    answers.reserve(q);

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, y;
            cin >> x >> y;
            updates.push_back({x, now[x], y});
            now[x] = y;
        } else {
            int a, b;
            cin >> a >> b;
            if (tin[a] > tin[b]) swap(a, b);
            int w = lca(a, b);
            int idx = (int)answers.size();
            answers.push_back(0);
            if (w == a)
                queries.push_back({tin[a], tin[b], (int)updates.size(), idx, -1});
            else
                queries.push_back({tout[a], tin[b], (int)updates.size(), idx, w});
        }
    }

    int M = max(timerN, 1);
    BLOCK = max(1, (int)pow((double)M, 2.0 / 3.0));

    sort(queries.begin(), queries.end(), [](const Query &A, const Query &B) {
        int blA = A.l / BLOCK, blB = B.l / BLOCK;
        if (blA != blB) return blA < blB;
        int brA = A.r / BLOCK, brB = B.r / BLOCK;
        if (brA != brB) return (blA & 1) ? brA > brB : brA < brB;
        if (brA & 1) return A.t > B.t;
        return A.t < B.t;
    });

    int curL = 0, curR = -1, curT = 0;
    for (const Query &qq : queries) {
        while (curT < qq.t) applyUpdate(curT++, true);
        while (curT > qq.t) applyUpdate(--curT, false);
        while (curR < qq.r) toggle(euler[++curR]);
        while (curR > qq.r) toggle(euler[curR--]);
        while (curL < qq.l) toggle(euler[curL++]);
        while (curL > qq.l) toggle(euler[--curL]);

        if (qq.extra != -1) toggle(qq.extra);
        answers[qq.idx] = curAns;
        if (qq.extra != -1) toggle(qq.extra);
    }

    for (long long x : answers) cout << x << '\n';
    return 0;
}