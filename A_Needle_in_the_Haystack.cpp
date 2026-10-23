#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    while (cin >> m) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string needle;
        getline(cin, needle);
        if (!needle.empty() && needle.back() == '\r')
            needle.pop_back();

        vector<int> pi(m, 0);
        for (int i = 1, j = 0; i < m; ++i) {
            while (j > 0 && needle[i] != needle[j])
                j = pi[j - 1];
            if (needle[i] == needle[j]) ++j;
            pi[i] = j;
        }

        char c;
        int matched = 0;
        long long position = 0;
        while (cin.get(c) && c != '\n') {
            if (c == '\r') continue; 

            while (matched > 0 && c != needle[matched])
                matched = pi[matched - 1];
            if (c == needle[matched]) ++matched;

            if (matched == m) {
                cout << position - m + 1 << '\n';
                matched = pi[matched - 1]; 
            }
            ++position;
        }
        cout << '\n';
    }
    return 0;
}