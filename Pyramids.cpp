#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

long double determinant(long double matrix[5][5]) {
    long double det = 1.0L;

    for (int col = 0; col < 5; ++col) {
        int pivot = col;
        for (int row = col + 1; row < 5; ++row) {
            if (fabsl(matrix[row][col]) > fabsl(matrix[pivot][col])) {
                pivot = row;
            }
        }

        if (fabsl(matrix[pivot][col]) < 1e-24L) {
            return 0.0L;
        }

        if (pivot != col) {
            for (int j = 0; j < 5; ++j) {
                swap(matrix[pivot][j], matrix[col][j]);
            }
            det = -det;
        }

        long double value = matrix[col][col];
        det *= value;

        for (int row = col + 1; row < 5; ++row) {
            long double factor = matrix[row][col] / value;
            for (int j = col + 1; j < 5; ++j) {
                matrix[row][j] -= factor * matrix[col][j];
            }
        }
    }

    return det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    cout << fixed << setprecision(4);

    while (t--) {
        long double AB, AC, AD, BC, BD, CD;
        cin >> AB >> AC >> AD >> BC >> BD >> CD;

        long double d[4][4] = {};

        d[0][1] = d[1][0] = AB * AB;
        d[0][2] = d[2][0] = AC * AC;
        d[0][3] = d[3][0] = AD * AD;
        d[1][2] = d[2][1] = BC * BC;
        d[1][3] = d[3][1] = BD * BD;
        d[2][3] = d[3][2] = CD * CD;

        long double cm[5][5] = {};

        for (int i = 0; i < 4; ++i) {
            cm[0][i + 1] = 1.0L;
            cm[i + 1][0] = 1.0L;

            for (int j = 0; j < 4; ++j) {
                cm[i + 1][j + 1] = d[i][j];
            }
        }

        long double det = determinant(cm);
        long double volumeSquared = det / 288.0L;

        if (volumeSquared < 0.0L && volumeSquared > -1e-12L) {
            volumeSquared = 0.0L;
        }

        long double volume = sqrtl(max(0.0L, volumeSquared));
        cout << volume << '\n';
    }

    return 0;
}