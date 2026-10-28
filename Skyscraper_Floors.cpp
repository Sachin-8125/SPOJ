#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Elevator {
    long long x, y;
};

long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

bool stopsAt(const Elevator &el, long long Z, long long F) {
    if (Z < el.y || Z >= F) return false;
    return (Z - el.y) % el.x == 0;
}

bool canTransfer(Elevator e1, Elevator e2, long long F) {
    if (e1.y > e2.y) {
        swap(e1, e2);
    }
    long long u, v;
    long long g = extGCD(e2.x, e1.x, u, v);
    long long diff = e1.y - e2.y;

    if (diff % g != 0) {
        return false;
    }

    long long x1_prime = e1.x / g;
    long long d = diff / g;

    long long d_mod = ((d % x1_prime) + x1_prime) % x1_prime;
    long long u_mod = ((u % x1_prime) + x1_prime) % x1_prime;
    long long k2 = (d_mod * u_mod) % x1_prime;

    long long min_common_floor = e2.y + k2 * e2.x;
    return min_common_floor < F;
}

void solve() {
    long long F, A, B;
    int E;
    if (!(cin >> F >> E >> A >> B)) return;

    vector<Elevator> elevators(E);
    for (int i = 0; i < E; ++i) {
        cin >> elevators[i].x >> elevators[i].y;
    }

    if (A == B) {
        cout << "It is possible to move the furniture.\n";
        return;
    }

    vector<bool> visited(E, false);
    vector<bool> isTarget(E, false);
    queue<int> q;

    for (int i = 0; i < E; ++i) {
        if (stopsAt(elevators[i], B, F)) {
            isTarget[i] = true;
        }
        if (stopsAt(elevators[i], A, F)) {
            visited[i] = true;
            q.push(i);
        }
    }

    bool possible = false;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (isTarget[curr]) {
            possible = true;
            break;
        }

        for (int next = 0; next < E; ++next) {
            if (!visited[next] && canTransfer(elevators[curr], elevators[next], F)) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    if (possible) {
        cout << "It is possible to move the furniture.\n";
    } else {
        cout << "The furniture cannot be moved.\n";
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