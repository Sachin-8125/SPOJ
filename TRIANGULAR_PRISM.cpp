#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    const double PI = 2 * acos(0.0);
    const double sin60 = sin(60.0 * PI / 180.0); 
    const double sin60_sq = sin60 * sin60;
    
    while (t--) {
        double V;
        cin >> V;
        
        double a = cbrt(3.0 * V / sin60_sq);
        
        double h = (2.0 * V) / (a * a * sin60);
        
        double S = a * a * sin60 + 3.0 * a * h;
        
        cout << fixed << setprecision(10) << S << endl;
    }
    
    return 0;
}