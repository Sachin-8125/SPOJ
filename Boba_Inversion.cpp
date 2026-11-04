#include <cstdio>
#include <vector>
using namespace std;

static const int INBUF = 1 << 20;
static char inbuf[INBUF];
static int inIdx = 0, inSize = 0;
inline char gc() {
  if (inIdx >= inSize) {
    inSize = (int)fread(inbuf, 1, INBUF, stdin);
    inIdx = 0;
    if (inSize <= 0)
      return 0;
  }
  return inbuf[inIdx++];
}
inline int rd() {
  char c = gc();
  while (c < '0' || c > '9')
    c = gc();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + (c - '0');
    c = gc();
  }
  return x;
}

static const int OUTBUF = 1 << 24;
static char obuf[OUTBUF];
static int oIdx = 0;
inline void wi(int x) {
  if (x == 0) {
    obuf[oIdx++] = '0';
    obuf[oIdx++] = '\n';
    return;
  }
  char t[12];
  int n = 0;
  while (x) {
    t[n++] = (char)('0' + x % 10);
    x /= 10;
  }
  while (n)
    obuf[oIdx++] = t[--n];
  obuf[oIdx++] = '\n';
}

int main() {
  int N = rd();
  vector<int> A(N + 2);
  for (int i = 1; i <= N; i++)
    A[i] = rd();

  vector<long long> off(N + 3, 0);
  for (int L = 1; L <= N; L++)
    off[L + 1] = off[L] + (N - L + 1);
  long long total = off[N + 1];
  vector<int> inv((size_t)total, 0);

  for (int L = N; L >= 1; L--) {
    long long baseL = off[L];
    long long baseL1 = off[L + 1];
    for (int R = L + 1; R <= N; R++) {
      long long v = inv[baseL1 + (R - (L + 1))]; 
      v += inv[baseL + (R - 1 - L)];             
      if (R - 1 >= L + 1)
        v -= inv[baseL1 + (R - 1 - (L + 1))]; 
      if (A[L] > A[R])
        v += 1; 
      inv[baseL + (R - L)] = (int)v;
    }
  }

  int M = rd();
  for (int q = 0; q < M; q++) {
    int L = rd(), R = rd();
    wi(inv[off[L] + (R - L)]);
  }
  fwrite(obuf, 1, oIdx, stdout);
  return 0;
}