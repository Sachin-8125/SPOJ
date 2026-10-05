#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
using namespace std;

static long double zeta_minus_one(unsigned n) {
    constexpr long double m = 128.0L;
    long double sum = 0.0L;
    for (unsigned k = 2; k < 128; ++k)
        sum += powl(static_cast<long double>(k), -static_cast<long double>(n));

    long double mn = powl(m, -static_cast<long double>(n));
    sum += m * mn / static_cast<long double>(n - 1) + mn / 2.0L;

    constexpr long double c[] = {
         1.0L / 12.0L,
        -1.0L / 720.0L,
         1.0L / 30240.0L,
        -1.0L / 1209600.0L,
         1.0L / 47900160.0L,
        -691.0L / 1307674368000.0L
    };
    long double rising = static_cast<long double>(n); 
    long double power = mn / m;                         
    for (int j = 0; j < 6; ++j) {
        sum += c[j] * rising * power;
        rising *= static_cast<long double>(n + 2 * j + 1)
                * static_cast<long double>(n + 2 * j + 2);
        power /= m * m;
    }
    return sum;
}

int main() {
    constexpr size_t BLOCK = 8192;
    uint32_t input[BLOCK];
    double output[BLOCK];

    const long double log_two = logl(2.0L);
    const long double log_two_pi = logl(2.0L * acosl(-1.0L));
    array<long double, 64> log_zeta{};
    for (unsigned n = 2; n < 64; n += 2)
        log_zeta[n] = log1pl(zeta_minus_one(n));

    size_t count;
    while ((count = fread(input, sizeof(input[0]), BLOCK, stdin)) != 0) {
        for (size_t i = 0; i < count; ++i) {
            uint32_t n = input[i];
            long double x = static_cast<long double>(n);
            long double ans = log_two + lgammal(x + 1.0L)
                            - x * log_two_pi;
            if (n < 64) ans += log_zeta[n];
            output[i] = static_cast<double>(ans);
        }
        fwrite(output, sizeof(output[0]), count, stdout);
    }
    return 0;
}