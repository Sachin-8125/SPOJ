#include <iostream>
#include <vector>

int main() {
    int precision = 100; // Change to desired precision
    std::vector<int> res;
    long long n = 2, rem = 0, root = 0;

    for (int i = 0; i < precision + 1; ++i) {
        rem = rem * 100 + (i == 0 ? n : 0) * (i == 0 ? 1 : 0);
        int x = 9;
        while ((20 * root + x) * x > rem) --x;
        rem -= (20 * root + x) * x;
        root = root * 10 + x;
        res.push_back(x);
    }

    std::cout << res[0] << ".";
    for (int i = 1; i < precision + 1; ++i)
        std::cout << res[i];
    std::cout << std::endl;
    return 0;
}