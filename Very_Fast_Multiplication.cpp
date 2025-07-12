#include <bits/stdc++.h>
using namespace std;

string multiply(const string &num1, const string &num2) {
    int n1 = (int)num1.size();
    int n2 = (int)num2.size();
    vector<int> result(n1 + n2, 0);

    // Reverse iterate over digits for multiplication
    for (int i = n1 - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        for (int j = n2 - 1; j >= 0; j--) {
            int digit2 = num2[j] - '0';
            int sum = digit1 * digit2 + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Convert result vector to string, skipping leading zeros
    string product;
    int i = 0;
    while (i < (int)result.size() && result[i] == 0) i++;
    for (; i < (int)result.size(); i++) {
        product.push_back(result[i] + '0');
    }
    if (product.empty()) product = "0";  // If product is zero
    return product;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    while (n--) {
        string l1, l2;
        cin >> l1 >> l2;
        cout << multiply(l1, l2) << "\n";
    }

    return 0;
}
