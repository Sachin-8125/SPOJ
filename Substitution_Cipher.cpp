#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int A, K;
    if (!(cin >> A >> K)) return;

    vector<string> words(K);
    for (int i = 0; i < K; ++i) {
        cin >> words[i];
    }

    string dummy;
    getline(cin, dummy);
    string message;
    getline(cin, message);

    if (!message.empty() && message.back() == '\r') {
        message.pop_back();
    }

    vector<vector<bool>> reach(A, vector<bool>(A, false));
    bool possible = true;

    for (int i = 0; i + 1 < K; ++i) {
        const string& w1 = words[i];
        const string& w2 = words[i + 1];
        size_t len = min(w1.size(), w2.size());
        bool diff_found = false;

        for (size_t j = 0; j < len; ++j) {
            if (w1[j] != w2[j]) {
                int u = w1[j] - 'a';
                int v = w2[j] - 'a';
                if (u >= 0 && u < A && v >= 0 && v < A) {
                    reach[u][v] = true;
                }
                diff_found = true;
                break;
            }
        }

        if (!diff_found && w1.size() > w2.size()) {
            possible = false;
        }
    }

    for (int k = 0; k < A; ++k) {
        for (int i = 0; i < A; ++i) {
            for (int j = 0; j < A; ++j) {
                if (reach[i][k] && reach[k][j]) {
                    reach[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < A; ++i) {
        if (reach[i][i]) {
            possible = false;
        }
    }

    vector<int> decrypted_rank(A, -1);
    for (int i = 0; i < A; ++i) {
        int before = 0;
        int after = 0;
        for (int j = 0; j < A; ++j) {
            if (i == j) continue;
            if (reach[j][i]) before++;
            if (reach[i][j]) after++;
        }
        if (before + after == A - 1) {
            decrypted_rank[i] = before;
        }
    }

    if (possible) {
        for (char& c : message) {
            if (c >= 'a' && c < 'a' + A) {
                int idx = c - 'a';
                if (decrypted_rank[idx] == -1) {
                    possible = false;
                    break;
                }
                c = static_cast<char>('a' + decrypted_rank[idx]);
            }
        }
    }

    if (possible) {
        cout << message << "\n";
    } else {
        cout << "Message cannot be decrypted.\n";
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