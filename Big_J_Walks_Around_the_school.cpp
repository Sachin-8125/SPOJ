#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int total = 0;
    for (int i = 0; i < n - 1; i++) {
        int time;
        cin >> time;
        total += time;
    }
    
    cout << total << endl;
    
    return 0;
}
