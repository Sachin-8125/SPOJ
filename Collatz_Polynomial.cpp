#include <iostream>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long long P;

    if (cin >> P) {
        long long steps = 0;
        while (P != 1) {
            if (P & 1) {
                P = (P << 1) ^ P ^ 1;
            } else {
                P >>= 1;
            }
            steps++;
        }
        cout << steps << endl;
    }
    return 0;
}
