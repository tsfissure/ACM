#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#define DEFMID  int mid = l + r >> 1
#define L_SON    (v << 1)
#define R_SON    (v << 1 | 1)
#define L_RANGE  l, mid
#define R_RANGE  mid + 1, r

typedef long long LLONG;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;

struct EdgeSet {
  int to, next;
} edges[N << 1];
int head[N], etot;

int p[N], fp[N], maxr[N];
LLONG dis[N], A[N];
int stk[N], parent[N];

LLONG maxToRoot[N << 2];
LLONG lazy[N << 2];

inline void addEdge(int u, int v) {
  edges[etot].to = v;
  edges[etot].next = head[u];
  head[u] = etot++;
}

inline void assignPos(int u, int pos) {
  p[u] = pos;
  fp[pos] = u;
}

inline void assignParent(int u, int v) {
  parent[v] = u;
  if (~u)
    dis[v] = dis[u] + A[v];
  else dis[v] = A[v];
}

inline void getPos(int u) {
  int toper =  -1;
  stk[++toper] = u;
  assignPos(u, 1);
  assignParent(-1, u);
  int pos = 1;
  for (; ~toper;) {
    int u = stk[toper];
    int e = head[u];
    if (~e) {
      int v = edges[e].to;
      if (v != parent[u]) {
        stk[++toper] = v;
        assignPos(v, ++pos);
        assignParent(u, v);
      }
      head[u] = edges[e].next;
    } else {
      maxr[u] = pos;
      --toper;
    }
  }
}


inline void pushUp(int v) {
  maxToRoot[v] = std::max(maxToRoot[L_SON], maxToRoot[R_SON]);
}

inline void build(int l, int r, int v) {
  lazy[v] = 0;
  if (l >= r) {
    maxToRoot[v] = dis[fp[l]];
    return;
  }
  DEFMID;
  build(L_RANGE, L_SON);
  build(R_RANGE, R_SON);
  pushUp(v);
}

inline void pushDown(int v) {
  if (lazy[v]) {
    lazy[L_SON] += lazy[v];
    lazy[R_SON] += lazy[v];
    maxToRoot[L_SON] -= lazy[v];
    maxToRoot[R_SON] -= lazy[v];
    lazy[v] = 0;
  }
}

inline void modify(int l, int r, int x, int y, int z, int v) {
  if (l >= x && r <= y) {
    maxToRoot[v] -= z;
    lazy[v] += z;
    return;
  }
  pushDown(v);
  DEFMID;
  if (mid >= x) modify(L_RANGE, x, y, z, L_SON);
  if (mid < y) modify(R_RANGE, x, y, z, R_SON);
  pushUp(v);
}

inline LLONG query(int l, int r, int x, int y, int v) {
  if (l >= x && r <= y) {
    return maxToRoot[v];
  }
  pushDown(v);
  LLONG rlt = -1LL << 60;
  DEFMID;
  if (mid >= x) rlt = query(L_RANGE, x, y, L_SON);
  if (mid < y) rlt = std::max(rlt, query(R_RANGE, x, y, R_SON));
  pushUp(v);
  return rlt;
}

int main() {
  int n, q;
  int u, v, w;
  int t, tt = 0;
  scanf("%d", &t);
  for (; t--;) {
    printf("Case #%d:\n", ++tt);
    int q;
    scanf("%d%d", &n, &q);
    memset(head, -1, n * sizeof(int));
    etot = 0;
    for (int i = 1; i < n; ++i) {
      scanf("%d%d", &u, &v);
      addEdge(u, v);
      addEdge(v, u);
    }
    for (int i = 0; i < n; ++i)
      scanf("%I64d", A + i);
    getPos(0);
    build(1, n, 1);
    int oper = 0;
    for (; q--;) {
      scanf("%d", &oper);
      if (1 == oper) {
        scanf("%d", &u);
        printf("%I64d\n", query(1, n, p[u], maxr[u], 1));
      } else {
        scanf("%d%d", &u, &v);
        modify(1, n, p[u], maxr[u], A[u] - v, 1);
        A[u] = v;
      }
    }
  }

  return 0;
}
