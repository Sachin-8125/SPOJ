#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <algorithm>

using namespace std;

static int lines[49];
static vector<int> cell_lines[27];
static int cell_weight[27];
static unordered_map<uint64_t, bool> memo;

void init_lines() {
    int idx = 0;
    for (int dz = -1; dz <= 1; ++dz) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dz < 0 || (dz == 0 && dy < 0) || (dz == 0 && dy == 0 && dx <= 0))
                    continue;
                for (int z = 0; z < 3; ++z) {
                    for (int y = 0; y < 3; ++y) {
                        for (int x = 0; x < 3; ++x) {
                            int mask = 0, cnt = 0;
                            for (int k = 0; k < 3; ++k) {
                                int nz = z + k * dz;
                                int ny = y + k * dy;
                                int nx = x + k * dx;
                                if (nz >= 0 && nz < 3 && ny >= 0 && ny < 3 && nx >= 0 && nx < 3) {
                                    mask |= (1 << (nz * 9 + ny * 3 + nx));
                                    cnt++;
                                }
                            }
                            if (cnt == 3) {
                                lines[idx] = mask;
                                for (int b = 0; b < 27; ++b) {
                                    if (mask & (1 << b)) {
                                        cell_lines[b].push_back(idx);
                                        cell_weight[b]++;
                                    }
                                }
                                idx++;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool has_won(int mask) {
    for (int i = 0; i < 49; ++i) {
        if ((mask & lines[i]) == lines[i])
            return true;
    }
    return false;
}

bool can_win(int me, int opp) {
    int occ = me | opp;
    int opp_threats = 0;

    for (int i = 0; i < 49; ++i) {
        int L = lines[i];
        int m = me & L;
        int o = opp & L;
        if (o == 0) {
            if (m && (m & (m - 1)))
                return true;
        }
        if (m == 0) {
            if (o && (o & (o - 1))) {
                opp_threats |= (L ^ o);
            }
        }
    }

    if (opp_threats) {
        if (opp_threats & (opp_threats - 1))
            return false;
        return !can_win(opp, me | opp_threats);
    }

    int rem = ((1 << 27) - 1) ^ occ;
    if (rem == 0)
        return false;

    uint64_t key = ((uint64_t)me << 27) | (uint64_t)opp;
    auto it = memo.find(key);
    if (it != memo.end())
        return it->second;

    pair<int, int> moves[27];
    int mcnt = 0;
    for (int b = 0; b < 27; ++b) {
        if (rem & (1 << b)) {
            int score = cell_weight[b];
            int my_threats_created = 0;
            int opp_threats_blocked = 0;
            for (int l_idx : cell_lines[b]) {
                int L = lines[l_idx];
                int m = me & L;
                int o = opp & L;
                if (o == 0 && m != 0) {
                    score += 20;
                    my_threats_created++;
                } else if (m == 0 && o != 0) {
                    score += 12;
                    opp_threats_blocked++;
                } else if (m == 0 && o == 0) {
                    score += 2;
                }
            }
            if (my_threats_created >= 2)
                score += 200;
            if (opp_threats_blocked >= 2)
                score += 100;
            moves[mcnt++] = {-score, b};
        }
    }
    sort(moves, moves + mcnt);

    for (int i = 0; i < mcnt; ++i) {
        int b = moves[i].second;
        if (!can_win(opp, me | (1 << b))) {
            memo[key] = true;
            return true;
        }
    }

    memo[key] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_lines();
    memo.reserve(1 << 16);

    int T;
    if (!(cin >> T))
        return 0;

    while (T--) {
        int x_mask = 0, o_mask = 0;
        int x_cnt = 0, o_cnt = 0;
        for (int i = 0; i < 9; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < 3; ++j) {
                int bit = i * 3 + j;
                if (s[j] == 'x') {
                    x_mask |= (1 << bit);
                    x_cnt++;
                } else if (s[j] == 'o') {
                    o_mask |= (1 << bit);
                    o_cnt++;
                }
            }
        }

        if (memo.size() > 1000000)
            memo.clear();

        bool ada_wins;
        if (has_won(x_mask))
            ada_wins = true;
        else if (has_won(o_mask))
            ada_wins = false;
        else if (x_cnt == o_cnt)
            ada_wins = can_win(x_mask, o_mask);
        else
            ada_wins = !can_win(o_mask, x_mask);

        cout << (ada_wins ? "Ada\n" : "Vinit\n");
    }

    return 0;
}