#include <iostream>
using namespace std;

string diamondRow(int s, int row) {
    string diamond_row = "";
    if (row < s) {
        for (int i = 0; i < s - row - 1; i++)
            diamond_row += ".";
        diamond_row += "/";
        for (int i = s - row; i < s + row; i++)
            diamond_row += "*";
        diamond_row += "\\";
        for (int i = s + row + 1; i < 2 * s; i++)
            diamond_row += ".";
    } else if (row < 2 * s) {
        for (int i = 0; i < row - s; i++)
            diamond_row += ".";
        diamond_row += "\\";
        for (int i = row - s + 1; i < 3 * s - row - 1; i++)
            diamond_row += "*";
        diamond_row += "/";
        for (int i = 3 * s - row; i < 2 * s; i++)
            diamond_row += ".";
    }
    return diamond_row;
}

void diamondGrid(int r, int c, int s) {
    for (int i = 0; i < r; i++) {
        for (int row = 0; row < 2 * s; row++) {
            string dr = diamondRow(s, row);
            for (int j = 0; j < c; j++)
                cout << dr;
            cout << endl;
        }
    }
}

int main() {
    int t, r, c, s;
    cin >> t;
    while (t--) {
        cin >> r >> c >> s;
        diamondGrid(r, c, s);
    }
    return 0;
}