//  Straight Line Spiral Pattern (Act 3)

#include <iostream>
#include <vector>
using namespace std;

void drawMaize(int s) {
    vector<vector<bool>> maize(s, vector<bool>(s, false));
    int i = 1, j = -1, r = s - 1;
    bool move, normal = true, right = true;

    do {
        move = true;
        if (right) {
            if (j + 1 < r) {
                j++;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
            } else if (i + 1 < r) {
                i++;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
            } else if (j > s - r) {
                j--;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
                right = false;
            } else {
                move = false;
            }
        } else {
            if (j > s - r) {
                j--;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
            } else if (i > s - r + 2) {
                i--;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
            } else if (j + 1 < r - 2) {
                j++;
                normal = !normal;
                if (normal) {
                    maize[i][j] = true;
                } else {
                    maize[j][i] = true;
                }
                right = true;
                r -= 2;
            } else {
                move = false;
            }
        }
    } while (move);

    for (i = 0; i < s; i++) {
        for (j = 0; j < s; j++) {
            if (maize[i][j]) {
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
        int n;
        cin >> n;
        drawMaize(n);
        if (t + 1 < T) {
            cout << "\n";
        }
    }
    return 0;
}
