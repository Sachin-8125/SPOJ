#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    if (K < 0) K = -K;

    unordered_set<long long> values;
    for (int i = 0; i < N; ++i) {
        long long x;
        cin >> x;
        values.insert(x);
    }

    long long count = 0;
    for (long long x : values) {
        if (values.count(x + K)) {
            ++count;
        }
    }

    cout << count << '\n';
    return 0;
}
