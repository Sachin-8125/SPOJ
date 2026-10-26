#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

static char inbuf[1 << 20];
static size_t inpos = 0, inlen = 0;

static inline int nextChar() {
    if (inpos == inlen) {
        inlen = fread(inbuf, 1, sizeof(inbuf), stdin);
        inpos = 0;
        if (inlen == 0) return EOF;
    }
    return (unsigned char)inbuf[inpos++];
}

static inline int readInt() {
    int c = nextChar();
    while (c != EOF && (c < '0' || c > '9')) c = nextChar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = nextChar();
    }
    return x;
}

static char outbuf[1 << 20];
static size_t outpos = 0;

static inline void flushOut() {
    if (outpos) {
        fwrite(outbuf, 1, outpos, stdout);
        outpos = 0;
    }
}

static inline void putStr(const char *s) {
    size_t n = strlen(s);
    if (outpos + n > sizeof(outbuf)) flushOut();
    memcpy(outbuf + outpos, s, n);
    outpos += n;
}

static inline void putInt(int x) {
    char tmp[12];
    int n = 0;
    if (x == 0) tmp[n++] = '0';
    while (x > 0) {
        tmp[n++] = (char)('0' + x % 10);
        x /= 10;
    }
    if (outpos + 12 > sizeof(outbuf)) flushOut();
    while (n--) outbuf[outpos++] = tmp[n];
}

static vector<char> grid;
static vector<int> dist;
static vector<int> q;

int main() {
    int T = readInt();
    while (T-- > 0) {
        int C = readInt();
        int R = readInt();
        size_t n = (size_t)R * C;
        grid.assign(n, '#');

        for (int r = 0; r < R; ++r) {
            int got = 0;
            while (got < C) {
                int c = nextChar();
                if (c == EOF) break;
                if (c == '\n' || c == '\r') continue;
                grid[(size_t)r * C + got] = (char)c;
                ++got;
            }
        }

        int start = -1;
        for (size_t i = 0; i < n; ++i)
            if (grid[i] == '.') {
                start = (int)i;
                break;
            }

        int diameter = 0;

        if (start >= 0) {
            dist.assign(n, -1);
            q.resize(n);

            auto bfs = [&](int src) -> int {
                int qh = 0, qt = 0;
                q[qt++] = src;
                dist[src] = 0;
                int far = src;
                while (qh < qt) {
                    int u = q[qh++];
                    int du = dist[u];
                    if (du > dist[far]) far = u;
                    int r = u / C, c = u % C;
                    if (r > 0 && grid[u - C] == '.' && dist[u - C] < 0) {
                        dist[u - C] = du + 1;
                        q[qt++] = u - C;
                    }
                    if (r + 1 < R && grid[u + C] == '.' && dist[u + C] < 0) {
                        dist[u + C] = du + 1;
                        q[qt++] = u + C;
                    }
                    if (c > 0 && grid[u - 1] == '.' && dist[u - 1] < 0) {
                        dist[u - 1] = du + 1;
                        q[qt++] = u - 1;
                    }
                    if (c + 1 < C && grid[u + 1] == '.' && dist[u + 1] < 0) {
                        dist[u + 1] = du + 1;
                        q[qt++] = u + 1;
                    }
                }
                return far;
            };

            int end1 = bfs(start);
            fill(dist.begin(), dist.end(), -1);
            int end2 = bfs(end1);
            diameter = dist[end2];
        }

        putStr("Maximum rope length is ");
        putInt(diameter);
        putStr(".\n");
    }

    flushOut();
    return 0;
}