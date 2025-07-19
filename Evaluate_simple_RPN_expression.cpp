#include <iostream>
#include <stack>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

bool isNumber(const string& s, double& number) {
    try {
        size_t idx;
        number = stod(s, &idx);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string token;
        stack<double> stk;
        bool error = false;

        while (iss >> token) {
            double num;
            if (isNumber(token, num)) {
                stk.push(num);
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (stk.size() < 2) {
                    error = true;
                    break;
                }

                double b = stk.top(); stk.pop();
                double a = stk.top(); stk.pop();

                if (token == "+") stk.push(a + b);
                else if (token == "-") stk.push(a - b);
                else if (token == "*") stk.push(a * b);
                else if (token == "/") {
                    if (b == 0) {
                        error = true;
                        break;
                    }
                    stk.push(a / b);
                }
            } else {
                // Not a number or valid operator
                error = true;
                break;
            }
        }

        if (error || stk.size() != 1) {
            cout << "ERROR" << endl;
        } else {
            cout << fixed << setprecision(4) << stk.top() << endl;
        }
    }

    return 0;
}
