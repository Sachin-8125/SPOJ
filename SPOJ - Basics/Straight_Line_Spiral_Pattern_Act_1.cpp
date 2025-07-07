//  Straight Line Spiral Pattern (Act 1)

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int num_test_cases;
    int size_of_shape;
    int i, j;
    cin >> num_test_cases;
    bool reverse;
    while (num_test_cases--) {
        cin >> size_of_shape;

        // For every row
        for (i = 0; i < size_of_shape; ++i) {
            // First part: . and * alternate
            for (j = 0; j < (size_of_shape - 1) / 2 - abs(((size_of_shape + 1) / 2 - i)); ++j) {
                cout << (j % 2 ? '.' : '*');
            }

            // Second part
            reverse = false;
            if (size_of_shape % 2 == 0 && i > (size_of_shape + 1) / 2) {
                reverse = true;
            }

            for (; j < (size_of_shape + 1) / 2 + abs((size_of_shape / 2 - i)); ++j) {
                // Correction for the center cell
                if (size_of_shape % 2 == 0 && (i - 1) == j && j == (size_of_shape) / 2 - 1) {
                    cout << '.';
                    continue;
                }
                if ((reverse ? i + 1 : i) % 2 == 0) {
                    cout << '*';
                } else {
                    cout << '.';
                }
            }

            // Third part
            for (; j < size_of_shape; ++j) {
                cout << ((j + size_of_shape) % 2 ? '*' : '.');
            }
            cout << '\n';
        }

        if (num_test_cases > 0) {
            cout << '\n';
        }
    }
    return 0;
}