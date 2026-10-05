#include <bits/stdc++.h>
using namespace std;

class Solver {
    static constexpr int MAXP = 10, MAXC = 100;
    struct Hint {
        array<int, MAXP> guess{};
        int black, total;
        vector<pair<int, int>> freq;
    };
    struct State {
        array<bitset<MAXC + 1>, MAXP> domain;
        array<int, MAXC + 1> low{}, high{};
    };
    int p, c, m;
    vector<Hint> hints;
    array<int, MAXP> answer{};
    bool validInput = true;

    // Enforce necessary conditions until no bound or domain changes.
    bool propagate(State &s) {
        bool changed;
        do {
            changed = false;
            auto tighten = [&](int color, int lo, int hi) {
                lo = max(lo, s.low[color]);
                hi = min(hi, s.high[color]);
                if (lo > hi) return false;
                if (lo != s.low[color] || hi != s.high[color]) {
                    s.low[color] = lo;
                    s.high[color] = hi;
                    changed = true;
                }
                return true;
            };

            array<int, MAXC + 1> forced{}, possible{};
            array<int, MAXP> fixed{};
            for (int i = 0; i < p; ++i) {
                int size = (int)s.domain[i].count();
                if (size == 0) return false;
                for (int color = 1; color <= c; ++color) {
                    if (s.domain[i][color]) {
                        ++possible[color];
                        if (size == 1) {
                            ++forced[color];
                            fixed[i] = color;
                        }
                    }
                }
            }
            int sumLow = 0, sumHigh = 0;
            for (int color = 1; color <= c; ++color) {
                if (!tighten(color, forced[color], possible[color]))
                    return false;
                sumLow += s.low[color];
                sumHigh += s.high[color];
            }
            if (sumLow > p || sumHigh < p) return false;
            for (int color = 1; color <= c; ++color) {
                if (!tighten(color,
                             p - (sumHigh - s.high[color]),
                             p - (sumLow - s.low[color])))
                    return false;
            }

            for (const Hint &h : hints) {
                // Black points: exact matches at the same positions.
                int certain = 0, available = 0;
                for (int i = 0; i < p; ++i) {
                    certain += s.domain[i].count() == 1 &&
                               s.domain[i][h.guess[i]];
                    available += s.domain[i][h.guess[i]];
                }
                if (certain > h.black || available < h.black)
                    return false;
                for (int i = 0; i < p; ++i) {
                    int color = h.guess[i];
                    if (s.domain[i].count() > 1 && s.domain[i][color]) {
                        if (certain == h.black) {
                            s.domain[i].reset(color);
                            changed = true;
                        } else if (available == h.black) {
                            s.domain[i].reset();
                            s.domain[i].set(color);
                            changed = true;
                        }
                    }
                }

                // B + W = sum_color min(secretCount[color], guessCount[color]).
                int minTotal = 0, maxTotal = 0;
                for (auto [color, count] : h.freq) {
                    minTotal += min(s.low[color], count);
                    maxTotal += min(s.high[color], count);
                }
                if (minTotal > h.total || maxTotal < h.total)
                    return false;
                // Each additional/removed pin changes the total by at most 1.
                if (minTotal + p - sumLow < h.total ||
                    maxTotal + p - sumHigh > h.total)
                    return false;
                for (auto [color, count] : h.freq) {
                    int minHere = min(s.low[color], count);
                    int maxHere = min(s.high[color], count);
                    int need = h.total - (maxTotal - maxHere);
                    int limit = h.total - (minTotal - minHere);
                    int lo = max(0, need);
                    int hi = (limit < count ? limit : p);
                    if (!tighten(color, lo, hi)) return false;
                }
            }

            // Translate count bounds back into position domains.
            // The counts from the start of this round remain sound bounds.
            for (int color = 1; color <= c; ++color) {
                if (forced[color] == s.high[color]) {
                    for (int i = 0; i < p; ++i) {
                        if (fixed[i] != color && s.domain[i][color]) {
                            s.domain[i].reset(color);
                            changed = true;
                        }
                    }
                }
                if (possible[color] == s.low[color]) {
                    for (int i = 0; i < p; ++i) {
                        if (s.domain[i][color] && s.domain[i].count() > 1) {
                            s.domain[i].reset();
                            s.domain[i].set(color);
                            changed = true;
                        }
                    }
                }
            }
        } while (changed);
        return true;
    }

    // Find any completion; lexicographic minimization is done separately.
    bool search(State s) {
        if (!propagate(s)) return false;
        int pos = -1;
        for (int i = 0; i < p; ++i)
            if (s.domain[i].count() > 1 &&
                (pos == -1 || s.domain[i].count() < s.domain[pos].count()))
                pos = i;
        if (pos == -1) {
            for (int i = 0; i < p; ++i)
                for (int color = 1; color <= c; ++color)
                    if (s.domain[i][color]) answer[i] = color;
            return true;
        }

        // Prefer a color-count variable involved in many unsaturated hints.
        int chosen = -1;
        double best = 0;
        for (int color = 1; color <= c; ++color) {
            if (s.low[color] == s.high[color]) continue;
            int degree = 0;
            for (const Hint &h : hints)
                for (auto [v, count] : h.freq)
                    if (v == color && s.low[color] < count) ++degree;
            double score = double(degree) / (s.high[color] - s.low[color]);
            if (score > best) { best = score; chosen = color; }
        }
        if (chosen != -1) {
            for (int n = s.low[chosen]; n <= s.high[chosen]; ++n) {
                State next = s;
                next.low[chosen] = next.high[chosen] = n;
                if (search(next)) return true;
            }
        } else {
            for (int color = 1; color <= c; ++color) {
                if (!s.domain[pos][color]) continue;
                State next = s;
                next.domain[pos].reset();
                next.domain[pos].set(color);
                if (search(next)) return true;
            }
        }
        return false;
    }

public:
    void run() {
        cin >> p >> c >> m;
        hints.resize(m);
        for (Hint &h : hints) {
            array<int, MAXC + 1> counts{};
            for (int i = 0; i < p; ++i) {
                cin >> h.guess[i];
                ++counts[h.guess[i]];
            }
            int white;
            cin >> h.black >> white;
            h.total = h.black + white;
            if (h.black < 0 || white < 0 || h.total > p)
                validInput = false;
            for (int color = 1; color <= c; ++color)
                if (counts[color]) h.freq.emplace_back(color, counts[color]);
        }
        State initial;
        // Colors absent from every guess are indistinguishable. Only the
        // smallest such color is needed in the lexicographically first code.
        array<bool, MAXC + 1> seen{};
        for (const Hint &h : hints)
            for (auto [color, count] : h.freq) seen[color] = true;
        int firstUnused = 0;
        for (int color = 1; color <= c; ++color)
            if (!seen[color]) { firstUnused = color; break; }
        for (int color = 1; color <= c; ++color) {
            if (!seen[color] && color != firstUnused) continue;
            initial.high[color] = p;
            for (int i = 0; i < p; ++i) initial.domain[i].set(color);
        }
        if (!validInput || !search(initial)) {
            cout << "You are cheating!\n";
            return;
        }

        // Fix the answer left to right. Keep a known feasible completion,
        // and test only colors smaller than its current color.
        for (int i = 0; i < p; ++i) {
            propagate(initial);
            int upper = answer[i];
            auto saved = answer;
            for (int color = 1; color < upper; ++color) {
                if (!initial.domain[i][color]) continue;
                State next = initial;
                next.domain[i].reset();
                next.domain[i].set(color);
                if (search(next)) break;
                answer = saved;
            }
            initial.domain[i].reset();
            initial.domain[i].set(answer[i]);
        }
        for (int i = 0; i < p; ++i)
            cout << answer[i] << (i + 1 == p ? '\n' : ' ');
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        Solver solver;
        solver.run();
    }
}