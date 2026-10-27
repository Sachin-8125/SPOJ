#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int M;
    if (!(cin >> M)) return;

    long long total_slots = 1LL * M * M * M;
    long long K = total_slots - 1;

    vector<int> perm(K + 1);
    long long idx = 1;

    int y0 = 0, z0 = 0;

    for (int z = 0; z < M; ++z) {
        for (int i = 0; i < M * M; ++i) {
            int tile;
            cin >> tile;
            if (tile == 0) {
                y0 = i / M;
                z0 = z;
            } else {
                perm[idx++] = tile;
            }
        }
    }

    long long cycles = 0;
    for (long long i = 1; i <= K; ++i) {
        if (perm[i] > 0) {
            cycles++;
            long long curr = i;
            while (perm[curr] > 0) {
                long long next_pos = perm[curr];
                perm[curr] = -perm[curr];
                curr = next_pos;
            }
        }
    }

    long long inv_parity = (K - cycles) % 2;

    long long dy = (M - 1) - y0;
    long long dz = (M - 1) - z0;
    long long move_parity = ((dy + dz) * (M - 1)) % 2;

    if ((inv_parity + move_parity) % 2 == 0) {
        cout << "Puzzle can be solved.\n";
    } else {
        cout << "Puzzle is unsolvable.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (cin >> N) {
        while (N--) {
            solve();
        }
    }
    return 0;
}