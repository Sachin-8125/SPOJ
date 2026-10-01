#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string s;
    cin >> s;

    int K;
    cin >> K;

    vector<int> required(26, 0);

    for (int i = 0; i < K; ++i) {
        int x;
        char y;
        cin >> x >> y;
        required[y - 'a'] = x;
    }

    vector<int> current(26, 0);
    int satisfied = 0;
    int answer = N + 1;
    int left = 0;

    for (int right = 0; right < N; ++right) {
        int c = s[right] - 'a';

        ++current[c];

        if (required[c] > 0 && current[c] == required[c]) {
            ++satisfied;
        }

        while (satisfied == K && left <= right) {
            answer = min(answer, right - left + 1);

            int leftChar = s[left] - 'a';
            --current[leftChar];

            if (required[leftChar] > 0 && current[leftChar] < required[leftChar]) {
                --satisfied;
            }

            ++left;
        }
    }

    if (answer == N + 1) {
        cout << "Andy rapopo\n";
    } else {
        cout << answer << '\n';
    }

    return 0;
}