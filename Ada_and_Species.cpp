#include <bits/stdc++.h>
using namespace std;

struct Vegetable {
    int x, y, z, w;
};

class Fenwick2DMin {
private:
    int n;
    vector<vector<int>> coords;
    vector<vector<int>> bit;

public:
    Fenwick2DMin(int n, const vector<Vegetable>& vegetables) : n(n), coords(n + 1), bit(n + 1) {
        for (const auto& v : vegetables) {
            for (int i = v.y; i <= n; i += i & -i) {
                coords[i].push_back(v.z);
            }
        }

        for (int i = 1; i <= n; ++i) {
            sort(coords[i].begin(), coords[i].end());
            coords[i].erase(unique(coords[i].begin(), coords[i].end()),
                            coords[i].end());
            bit[i].assign(coords[i].size() + 1, INT_MAX);
        }
    }

    void update(int y, int z, int w) {
        for (int i = y; i <= n; i += i & -i) {
            int pos = lower_bound(coords[i].begin(), coords[i].end(), z)
                      - coords[i].begin() + 1;

            for (int j = pos; j < static_cast<int>(bit[i].size()); j += j & -j) {
                bit[i][j] = min(bit[i][j], w);
            }
        }
    }

    int query(int yLimit, int zLimit) const {
        int answer = INT_MAX;

        for (int i = yLimit; i > 0; i -= i & -i) {
            int count = lower_bound(coords[i].begin(), coords[i].end(), zLimit)
                        - coords[i].begin();

            for (int j = count; j > 0; j -= j & -j) {
                answer = min(answer, bit[i][j]);
            }
        }

        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Vegetable> vegetables(n);
    for (auto& v : vegetables) {
        cin >> v.x >> v.y >> v.z >> v.w;
    }

    sort(vegetables.begin(), vegetables.end(), [](const Vegetable& a, const Vegetable& b) {
        return a.x < b.x;
    });

    Fenwick2DMin fenwick(n, vegetables);
    int answer = 0;

    for (const auto& v : vegetables) {
        int minW = fenwick.query(v.y - 1, v.z);

        if (minW >= v.w) {
            ++answer;
        }

        fenwick.update(v.y, v.z, v.w);
    }

    cout << answer << '\n';
    return 0;
}