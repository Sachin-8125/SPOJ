#include <iostream>
using namespace std;

// Function to find GCD of two numbers using efficient iterative method
long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find LCM of two numbers
long long lcm(long long a, long long b) {
    // To avoid overflow, first divide a by gcd
    return ((a*b )/ gcd(a, b));
}

int main() {
    int N;
    // Read input until EOF (End Of File)
    while (cin >> N) {
        // Initialize LCM as 1
        long long result = 1;
        
        // Read N numbers
        for (int i = 0; i < N; i++) {
            long long num;
            cin >> num;
            // Calculate LCM iteratively
            result = lcm(result, num);
        }
        
        cout << result << endl;
    }
    return 0;
}