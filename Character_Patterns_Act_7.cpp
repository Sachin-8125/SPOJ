#include <iostream>
using namespace std;

// Print a single diamond grid
void diamondGrid(int r, int c, int s) {
    for (int block = 0; block < r; ++block) {
        for (int i = 0; i < 2 * s; ++i) {
            for (int repeat = 0; repeat < c; ++repeat) {
                if (i < s) {
                    // Upper part
                    for (int j = 0; j < s - i - 1; ++j) cout << ".";
                    cout << "/";
                    for (int j = 0; j < 2 * i; ++j) cout << ".";
                    cout << "\\";
                    for (int j = 0; j < s - i - 1; ++j) cout << ".";
                } else {
                    // Lower part
                    for (int j = 0; j < i - s; ++j) cout << ".";
                    cout << "\\";
                    for (int j = 0; j < 2 * (2 * s - i - 1); ++j) cout << ".";
                    cout << "/";
                    for (int j = 0; j < i - s; ++j) cout << ".";
                }
            }
            cout << "\n";
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int r, c, s;
        cin >> r >> c >> s;
        diamondGrid(r, c, s);
        if (t) cout << endl; // Print blank line between test cases
    }
    return 0;
}