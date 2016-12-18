#include <bits/stdc++.h>

typedef unsigned long long LLONG;
typedef std::pair<double, double> PDD;
typedef std::pair<int, int> PII;

#define TDEBUG
#ifdef TDEBUG
#define tout(x) std::cerr << #x << " = " << x << std::endl;
#define tdebug(args...) { std::cerr << "(" << #args << ") = > "; dbg, args; std::cerr << std::endl; }
#else
#define tout(x) //skip all
#define tdebug(args...)
#endif
struct Debuger {
  template<typename T>
  Debuger& operator, (const T& v) {
    std::cerr << v << " ";
    return *this;
  }
} dbg;

const int N = 285113;
const int MOD = 1e9 + 7;
const LLONG M = 1e16;
const int NUM_LEN = 20;
LLONG c[N * 2 + 10][NUM_LEN][11];
LLONG sm[N];
LLONG smln[N][NUM_LEN];
int bit[NUM_LEN];
int power[NUM_LEN];

inline void gao(int t, LLONG n, int ln, bool mark) {
  if (ln < 0) { return; }
  LLONG lsm = 0;
  for (int i = mark ? 1 : 0; i < 10; ++i) {
    LLONG v = c[t][ln + 1][i];
    if (lsm + v >= n) {
      bit[ln] = i;
      gao(t - power[ln]*i, n - lsm, ln - 1, false);
      break;
    }
    lsm += v;
  }
}

int main() {
  c[0][1][0] = 1;
  c[0][1][10] = 1;
  sm[0] = 1;
  smln[0][1] = 1;
  power[0] = 1;
  for (int i = 1; i < NUM_LEN; ++i) {
    power[i] = power[i - 1] << 1;
  }
  for (int i = 0; i < 10; ++i) {
    c[i][1][i] = 1;
  }
  for (int i = 0; i < N; ++i) {
    LLONG lsm = 0;
    LLONG zero = 0;
    for (int d = 1; power[d - 1] <= i; ++d) {
      LLONG lnsm = 0;
      for (int j = 1; j < 10; ++j) {
        if (c[i][d][j]) {
          for (int k = 0; k < 10; ++k) {
            c[(i << 1) + k][d + 1][j] += c[i][d][j];
          }
          lnsm += c[i][d][j];
        }
      }
      lsm += lnsm;
      smln[i][d] = lnsm;
      c[i][d][0] = zero;
      zero += smln[i][d];
      c[i][d + 1][0] = zero;
    }
    if (i > 0) {
      sm[i] = sm[i - 1] + lsm;
    }
    if (sm[i] >= M) {break;}
  }
  int q;
  for (scanf("%d", &q); q--;) {
    LLONG n;
    scanf("%lld", &n);
    int l = 0, r = 285112;
    for (; l <= r;) {
      int mid = l + r >> 1;
      if (sm[mid] >= n) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    n -= sm[r];
    int v = r + 1;
    LLONG lsm = 0;
    int rn = 0;
    for (int i = 0; i < NUM_LEN; ++i) {
      if (lsm + smln[v][i] >= n) {
        memset(bit, 0, i * sizeof(*bit));
        gao(v, n - lsm, i - 1, true);
        rn = i - 1;
        break;
      }
      lsm += smln[v][i];
    }
    for (int i = rn; ~i; --i) {
      printf("%d", bit[i]);
    }
    putchar(10);
  }
  return 0;
}
/*
5999999999
23001090090
*/



