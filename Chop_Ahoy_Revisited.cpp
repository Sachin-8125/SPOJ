#include <cstring>
#include <iostream>
#include <string>

using namespace std;

string s;
int n;
long long memo[26][226];

long long solve(int pos, int prev_sum) {
    if (pos == n) {
        return 1;
    }
    if (memo[pos][prev_sum] != -1) {
        return memo[pos][prev_sum];
    }

    long long ways = 0;
    int cur_sum = 0;
    for (int i = pos; i < n; ++i) {
        cur_sum += s[i] - '0';
        if (cur_sum >= prev_sum) {
            ways += solve(i + 1, cur_sum);
        }
    }

    return memo[pos][prev_sum] = ways;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_case = 1;
    while (cin >> s && s != "bye") {
        n = static_cast<int>(s.length());
        memset(memo, -1, sizeof(memo));
        cout << test_case++ << ". " << solve(0, 0) << "\n";
    }

    return 0;
}