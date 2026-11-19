#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string braces;
    int caseNumber = 1;
    while (cin >> braces && braces.front() != '-') {
        int open = 0;
        int reversals = 0;
        for (char brace : braces) {
            if (brace == '{') {
                ++open;
            } else if (open > 0) {
                --open;
            } else {
                ++reversals;
                ++open;
            }
        }
        reversals += open / 2;
        cout << caseNumber++ << ". " << reversals << '\n';
    }
    return 0;
}