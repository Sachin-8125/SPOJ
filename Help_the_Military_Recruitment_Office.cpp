#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<string> id_to_mro;
    unordered_map<string, int> mro_to_id;

    DSU(int expected_size = 200005) {
        parent.reserve(expected_size);
        id_to_mro.reserve(expected_size);
        mro_to_id.reserve(expected_size);
    }

    int get_id(const string& mro) {
        auto it = mro_to_id.find(mro);
        if (it != mro_to_id.end()) {
            return it->second;
        }
        int id = static_cast<int>(id_to_mro.size());
        mro_to_id.emplace(mro, id);
        id_to_mro.push_back(mro);
        parent.push_back(id);
        return id;
    }

    int find(int i) {
        int root = i;
        while (root != parent[root]) {
            root = parent[root];
        }
        int curr = i;
        while (curr != root) {
            int nxt = parent[curr];
            parent[curr] = root;
            curr = nxt;
        }
        return root;
    }

    void redirect(const string& old_mro, const string& new_mro) {
        int u = get_id(old_mro);
        int v = get_id(new_mro);
        int root_v = find(v);
        parent[u] = root_v;
    }

    const string& resolve(int id) {
        return id_to_mro[find(id)];
    }
};

void solve() {
    int s;
    if (!(cin >> s)) return;

    for (int tc = 0; tc < s; ++tc) {
        int p;
        cin >> p;

        DSU dsu(2 * p + 1000);
        unordered_map<long long, int> pesel_to_mro;
        pesel_to_mro.reserve(p * 2);

        for (int i = 0; i < p; ++i) {
            long long pesel;
            string mro;
            cin >> pesel >> mro;
            pesel_to_mro[pesel] = dsu.get_id(mro);
        }

        int z;
        cin >> z;
        for (int i = 0; i < z; ++i) {
            string old_code, new_code;
            cin >> old_code >> new_code;
            dsu.redirect(old_code, new_code);
        }

        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            string pesel_str;
            cin >> pesel_str;
            long long pesel = stoll(pesel_str);
            int mro_id = pesel_to_mro[pesel];
            cout << pesel_str << ' ' << dsu.resolve(mro_id) << '\n';
        }

        if (tc + 1 < s) {
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}