#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

using int64 = long long;

constexpr int64 MOD = 4000000007LL;
constexpr int64 LAST_TIMESTAMP = 1924991999LL; // 2030-12-31 23:59:59 UTC

int64 modPow(int64 base, int64 exponent) {
    int64 result = 1;

    while (exponent > 0) {
        if (exponent & 1) {
            result = static_cast<int64>((__int128)result * base % MOD);
        }

        base = static_cast<int64>((__int128)base * base % MOD);
        exponent >>= 1;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 encrypted;
    cin >> encrypted;

    int64 root = modPow(encrypted, (MOD + 1) / 4);

    int64 timestamp;
    if (root <= LAST_TIMESTAMP) {
        timestamp = root;
    } else {
        timestamp = MOD - root;
    }

    time_t value = static_cast<time_t>(timestamp);
    tm* utc = gmtime(&value);

    char output[27];
    strftime(output, sizeof(output), "%a %b %d %H:%M:%S %Y", utc);
    cout << output << '\n';

    return 0;
}