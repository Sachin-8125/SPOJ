#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int INF = 1e9;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.assign(2 * n, INF);
    }

    void update(int pos, int value) {
        pos += n;
        tree[pos] = min(tree[pos], value);

        for (pos >>= 1; pos > 0; pos >>= 1) {
            tree[pos] = min(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    int query(int left, int right) const {
        if (left > right) return INF;

        left += n;
        right += n;

        int result = INF;

        while (left <= right) {
            if (left & 1) {
                result = min(result, tree[left]);
                ++left;
            }

            if (!(right & 1)) {
                result = min(result, tree[right]);
                --right;
            }

            left >>= 1;
            right >>= 1;
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    while (D--) {
        int N;
        ll C, T;

        cin >> N >> C >> T;

        vector<ll> G(N + 1);

        for (int i = 1; i <= N; ++i) {
            cin >> G[i];
        }

        vector<ll> values;

        for (int i = 1; i <= N; ++i) {
            values.push_back(G[i]);
        }

        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        vector<vector<int>> channels(values.size());

        for (int i = 1; i <= N; ++i) {
            int compressedIndex = lower_bound(values.begin(), values.end(), G[i]) - values.begin();
            channels[compressedIndex].push_back(i);
        }

        SegmentTree segmentTree((int)values.size());

        vector<int> dp(N + 1, INF);

        int startIndex = lower_bound(values.begin(), values.end(), G[1]) - values.begin();

        dp[1] = 0;
        segmentTree.update(startIndex, 0);

        ll answerGirliness = G[1];
        ll answerTime = 0;

        for (int valueIndex = startIndex + 1; valueIndex < (int)values.size(); ++valueIndex) {
            
            ll currentGirliness = values[valueIndex];

            ll lowerGirliness = currentGirliness - C;

            int leftIndex = lower_bound(values.begin(), values.end(), lowerGirliness) - values.begin();

            int rightIndex = valueIndex - 1;

            int bestPreviousSwitches = segmentTree.query(leftIndex, rightIndex);

            if (bestPreviousSwitches == INF) {
                continue;
            }

            int currentSwitches = bestPreviousSwitches + 1;

            for (int channel : channels[valueIndex]) {
                dp[channel] = currentSwitches;
            }

            segmentTree.update(valueIndex, currentSwitches);

            answerGirliness = currentGirliness;
            answerTime = 1LL * currentSwitches * T;
        }

        cout << answerGirliness << ' ' << answerTime << '\n';
    }

    return 0;
}
