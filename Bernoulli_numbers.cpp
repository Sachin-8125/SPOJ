#include <cstdio>
#include <cmath>
#include <cstdint>

double zeta(unsigned N) {
    if (N > 50) return 1.0;
    double sum = 1.0;
    for (int k = 2; k < 100; ++k) {
        sum += pow(1.0 / k, N);
        if (pow(1.0 / k, N) < 1e-20) break;
    }
    return sum;
}

int main() {
    uint32_t N;
    while (fread(&N, sizeof(N), 1, stdin) == 1) {
        double ln2 = log(2.0);
        double ln2pi = log(2.0 * M_PI);
        double ln_fact = lgamma(N + 1);
        double ln_zeta = log(zeta(N));
        double result = ln2 + ln_fact - N * ln2pi + ln_zeta;
        fwrite(&result, sizeof(result), 1, stdout);
    }
    return 0;
}
