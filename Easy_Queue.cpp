#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class FastScanner {
    static constexpr int BUFFER_SIZE = 1 << 16;
    char buffer[BUFFER_SIZE];
    int position = 0, length = 0;

    char readChar() {
        if (position == length) {
            length = static_cast<int>(fread(buffer, 1, BUFFER_SIZE, stdin));
            position = 0;
            if (length == 0) return EOF;
        }
        return buffer[position++];
    }

public:
    bool readInt(int& value) {
        char c;
        do {
            c = readChar();
            if (c == EOF) return false;
        } while (c <= ' ');

        value = 0;
        while (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
            c = readChar();
        }
        return true;
    }

    bool readLongLong(long long& value) {
        char c;
        do {
            c = readChar();
            if (c == EOF) return false;
        } while (c <= ' ');

        bool negative = false;
        if (c == '-') {
            negative = true;
            c = readChar();
        }

        value = 0;
        while (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
            c = readChar();
        }

        if (negative) value = -value;
        return true;
    }
};

int main() {
    FastScanner scanner;

    int T;
    if (!scanner.readInt(T)) return 0;

    vector<long long> queue;
    queue.reserve(T);

    size_t front = 0;
    string output;
    output.reserve(static_cast<size_t>(T) * 12);

    for (int i = 0; i < T; ++i) {
        int query;
        scanner.readInt(query);

        if (query == 1) {
            long long value;
            scanner.readLongLong(value);
            queue.push_back(value);
        } else if (query == 2) {
            if (front < queue.size()) {
                ++front;
            }
        } else { // query == 3
            if (front < queue.size()) {
                output += to_string(queue[front]);
                output += '\n';
            } else {
                output += "Empty!\n";
            }
        }
    }

    fwrite(output.data(), 1, output.size(), stdout);
    return 0;
}
