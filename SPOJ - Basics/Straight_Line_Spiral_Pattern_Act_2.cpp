//  Straight Line Spiral Pattern (Act 2)

#include <iostream>
#include <vector>
using namespace std;

void drawMaize(int s) {
    vector<vector<bool>> maize(s, vector<bool>(s, false));
    int i = 1, j = -1, r = s - 1;
    bool move, right = true;

    do {
        move = true;
        if (right) {
            if (j + 1 < r) {
                j++;
                maize[i][j] = true;
            } else if (i + 1 < r) {
                i++;
                maize[i][j] = true;
            } else if (j > s - r) {
                j--;
                maize[i][j] = true;
                right = false;
            } else {
                move = false;
            }
        } else {
            if (j > s - r) {
                j--;
                maize[i][j] = true;
            } else if (i > s - r + 2) {
                i--;
                maize[i][j] = true;
            } else if (j + 1 < r - 2) {
                j++;
                maize[i][j] = true;
                right = true;
                r -= 2;
            } else {
                move = false;
            }
        }
    } while (move);

    for (i = 0; i < s; i++) {
        for (j = 0; j < s; j++) {
            if (maize[j][i]) {
                cout << ".";
            } else {
                cout << "*";
            }
        }
        cout << "\n";
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int s;
        cin >> s;
        drawMaize(s);
        if (t + 1 < T) {
            cout << "\n";
        }
    }
    return 0;
}