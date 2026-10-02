#include <bits/stdc++.h>
using namespace std;

class FastInput {
    static const int SIZE = 1 << 20;
    char buffer[SIZE];
    int idx = 0, size = 0;

    inline char getChar() {
        if (idx >= size) {
            size = fread(buffer, 1, SIZE, stdin);
            idx = 0;
            if (size == 0)
                return 0;
        }
        return buffer[idx++];
    }

public:
    int nextInt() {
        char c = getChar();

        while (c <= ' ')
            c = getChar();

        int x = 0;

        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getChar();
        }

        return x;
    }
};

int main() {
    FastInput in;

    int n = in.nextInt();
    int k = in.nextInt();


    for (int i = 0; i < n; ++i)
        in.nextInt();

    for (int i = 0; i < k; ++i)
        in.nextInt();

    puts("Yes");

    return 0;
}