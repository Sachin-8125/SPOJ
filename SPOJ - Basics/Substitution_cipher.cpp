//  Substitution cipher

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    string cypher;
    cin >> cypher;

    // Reverse the cypher string
    reverse(cypher.begin(), cypher.end());

    // Prepare the substitution key pairs
    vector<pair<char, char>> cypher_key;
    for (int i = 0; i < n; ++i) {
        char first = cypher[i];
        char second = cypher[(i - 1 + n) % n]; // Handles negative index
        cypher_key.push_back({first, second});
    }
    cypher_key[n-1].first = '|';

    int m;
    cin >> m;
    cin.ignore(); // Ignore leftover newline

    for (int i = 0; i < m; ++i) {
        string s;
        getline(cin, s);

        // Replace the character first (cypher_key[0].second) with '|'
        for (char& c : s) {
            if (c == cypher_key[0].second) c = '|';
        }

        // Substitute according to cypher_key
        for (auto& key : cypher_key) {
            for (char& c : s) {
                if (c == key.first) c = key.second;
            }
        }

        cout << s << endl;
    }
    return 0;
}