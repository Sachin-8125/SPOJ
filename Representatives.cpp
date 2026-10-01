#include <bits/stdc++.h>
using namespace std;

struct Student {
    long long ability;
    int classId;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Student> students;
    students.reserve(1LL * N * M);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            long long ability;
            cin >> ability;
            students.push_back({ability, i});
        }
    }

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.ability < b.ability;
    });

    vector<int> count(N, 0);
    int classesCovered = 0;
    int left = 0;

    long long answer = LLONG_MAX;

    for (int right = 0; right < (int)students.size(); ++right) {
        int classId = students[right].classId;

        if (count[classId] == 0) {
            ++classesCovered;
        }
        ++count[classId];

        while (classesCovered == N) {
            answer = min(answer, students[right].ability - students[left].ability);

            int leftClass = students[left].classId;
            --count[leftClass];

            if (count[leftClass] == 0) {
                --classesCovered;
            }

            ++left;
        }
    }

    cout << answer << '\n';

    return 0;
}
