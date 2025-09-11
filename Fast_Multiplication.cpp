#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Multiplies two large numbers represented as strings
string multiply(const string& num1, const string& num2) {
    if(num1 == "0" || num2 == "0") return "0";
    int n = num1.size(), m = num2.size();
    vector<int> result(n + m, 0);

    // Reverse the numbers for convenience
    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Construct the result string
    string res;
    int i = 0;
    while(i < result.size() && result[i] == 0) ++i;
    while(i < result.size()) res.push_back(result[i++] + '0');
    return res;
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string l1, l2;
        cin >> l1 >> l2;
        cout << multiply(l1, l2) << endl;
    }
    return 0;
}
