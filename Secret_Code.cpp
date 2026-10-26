#include <iostream>
#include <vector>

using namespace std;

void solve() {
    long long Xr, Xi, Br, Bi;
    if (!(cin >> Xr >> Xi >> Br >> Bi)) return;

    long long N = Br * Br + Bi * Bi;
    vector<int> digits;
    digits.reserve(105);

    bool possible = true;

    do {
        if (digits.size() > 100) {
            possible = false;
            break;
        }

        int found_a = -1;
        long long next_Xr = 0, next_Xi = 0;

        for (long long a = 0; a < N; ++a) {
            long long num_r = (Xr - a) * Br + Xi * Bi;
            long long num_i = Xi * Br - (Xr - a) * Bi;

            if (num_r % N == 0 && num_i % N == 0) {
                found_a = static_cast<int>(a);
                next_Xr = num_r / N;
                next_Xi = num_i / N;
                break;
            }
        }

        if (found_a == -1) {
            possible = false;
            break;
        }

        digits.push_back(found_a);

        if (next_Xr == Xr && next_Xi == Xi && (Xr != 0 || Xi != 0)) {
            possible = false;
            break;
        }

        Xr = next_Xr;
        Xi = next_Xi;

    } while (Xr != 0 || Xi != 0);

    if (!possible) {
        cout << "The code cannot be decrypted.\n";
    } else {
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            cout << digits[i] << (i > 0 ? "," : "");
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}