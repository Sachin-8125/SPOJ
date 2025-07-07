//  Nobabs Treasure Hunt

#include <iostream>
#include <cstdlib> // For abs() with integers
using namespace std;

int main() {
    long long x, y, t1, t2; // Use long long to handle large constraints
    cin >> x >> y >> t1 >> t2;
    long long cost = llabs(x - t1) + llabs(y - t2);
    cout << cost << endl;
    return 0;
}

