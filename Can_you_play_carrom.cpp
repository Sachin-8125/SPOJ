#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Helper function to determine team based on player
int getTeam(char player) {
    if (player == 'A' || player == 'C') return 1; // Team-1
    return 2; // Team-2
}

int main() {
    string line;
    
    while (true) {
        int white1 = 0, black1 = 0, red1 = 0; // Team-1 stats
        int white2 = 0, black2 = 0, red2 = 0; // Team-2 stats

        int total_white = 0;
        int total_black = 0;
        int total_red = 0;

        bool first_line = true;
        bool game_started = false;
        
        while (getline(cin, line)) {
            if (line.empty()) continue;

            if (line[0] == '#') break;

            char player;
            int w, b, r;
            sscanf(line.c_str(), "%c %d %d %d", &player, &w, &b, &r);

            if (first_line) {
                // Determine starting team (Team-1), who got white
                int team = getTeam(player);
                game_started = true;
                first_line = false;
            }

            int team = getTeam(player);

            if (team == 1) {
                white1 += w;
                black1 += b;
                red1 += r;
            } else {
                white2 += w;
                black2 += b;
                red2 += r;
            }

            total_white += w;
            total_black += b;
            total_red += r;

            // total_white+total_black+total_red must be ≤ 19 (9 white + 9 black + 1 red)
        }

        if (!game_started) break; // All input processed

        // CHECK IF GAME COMPLETE
        bool complete = (white1 + white2 == 9) && (black1 + black2 == 9) && (red1 + red2 == 1);

        if (!complete) {
            cout << "Incomplete game." << endl;
            continue;
        }

        // Decide the winner
        if ((white1 + red1 == 10)) { // Team-1 win
            int points = 9 - black2 + (red1 == 1 ? 5 : 0);
            cout << "Team-1 win and the point is " << points << "." << endl;
        } else if ((black2 + red2 == 10)) { // Team-2 win
            int points = 9 - white1 + (red2 == 1 ? 5 : 0);
            cout << "Team-2 win and the point is " << points << "." << endl;
        } else {
            cout << "Incomplete game." << endl;
        }
    }

    return 0;
}
