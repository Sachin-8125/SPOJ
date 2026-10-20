#include <bits/stdc++.h>
using namespace std;

int main() {
    string tok;
    vector<array<int, 4>> moves;

    auto solve = [&]() {
        if (moves.empty()) return;

        int whiteTeam = moves[0][0];
        int blackTeam = 3 - whiteTeam;
        int w = 0, b = 0, red = 0, redTeam = 0, winner = 0;

        for (auto &m : moves) {
            w += m[1];
            b += m[2];

            if (m[3] > 0 && !red) {
                red = 1;
                redTeam = m[0];
            }

            if (!winner) {
                if (w >= 9) winner = whiteTeam;
                else if (b >= 9) winner = blackTeam;
            }
        }

        if (!winner || !red) {
            puts("Incomplete game.");
        } else {
            int remaining = (winner == whiteTeam) ? max(0, 9 - b) : max(0, 9 - w);
            int pts = remaining + (redTeam == winner ? 5 : 0);
            printf("Team-%d win and the point is %d.\n", winner, pts);
        }

        moves.clear();
    };

    while (cin >> tok) {
        if (tok[0] == '#') {
            solve();
            continue;
        }

        int W, B, R;
        if (!(cin >> W >> B >> R)) break;

        char p = toupper(tok[0]);
        int team = (p == 'A' || p == 'C') ? 1 : 2;
        moves.push_back({team, W, B, R});
    }

    solve();

    return 0;
}