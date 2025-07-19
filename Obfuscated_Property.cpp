#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000000; // Adjust as needed

int main() {
    vector<int> fusc(MAX_N + 1);
    fusc[0] = 0;
    fusc[1] = 1;

    for (int i = 2; i <= MAX_N; ++i) {
        if (i % 2 == 0)
            fusc[i] = fusc[i / 2];
        else
            fusc[i] = fusc[i / 2] + fusc[(i / 2) + 1];
    }

    int n;
    while (cin >> n) {
        cout << fusc[n] << endl;
    }
    return 0;
}