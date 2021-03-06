//https://www.codechef.com/SEPT16/problems/JTREE
#include <bits/stdc++.h>

typedef long long LLONG;
typedef std::pair<int, int>PII;
typedef std::map<int, int>MII;
typedef std::vector<int>VI;
typedef std::vector<PII>VPII;
#define	dout(x) std::cout << #x << " = " << x << std::endl;	//debug out
#define LSON v << 1
#define RSON v << 1 | 1
#define TMID int mid = l + r >> 1;	//Tree Middle

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;
const int M = 1e6 + 10;
const int K = 18;
const LLONG oo = 1e16;

VPII scroll[N];
int p[N], fp[N], ptot;
int parent[N];
PII edge[N << 1];
int head[N], etot;
LLONG mn[N << 2], answer[N];
int up[N][K];
int stk[N], toper;

inline void prepare(int n) {
	memset(head + 1, -1, n * sizeof(head[1]));
	etot = ptot = toper = 0;
	answer[1] = 0;
	for(int i = 1; i <= n; ++i) {
		scroll[i].clear();
	}
}

inline void addEdge(int u, int v) {
	edge[etot] = std::make_pair(v, head[u]);
	head[u] = etot++;
}

inline void dfs(int u, int f, int d) {
	up[u][0] = f;
	parent[u] = f;
	for(int e = head[u]; ~e; e = edge[e].second) {
		int v = edge[e].first;
		if(v != f) {
			dfs(v, u, d + 1);
		}
	}
}

inline void pushUp(int v) {
	mn[v] = std::min(mn[LSON], mn[RSON]);
}

inline void build(int l, int r, int v) {
	if(l >= r) {
		mn[v] = 2 > l ? 0 : oo;
		return;
	}
	TMID;
	build(l, mid, LSON);
	build(mid + 1, r, RSON);
	pushUp(v);
}

inline void update(int l, int r, int up, LLONG val, int v) {
	if(up < l || up > r) return;
	if(l >= r) {
		mn[v] = val;
		return;
	}
	TMID;
	if(mid >= up) { update(l, mid, up, val, LSON);}
	else if(mid < up) { update(mid + 1, r, up, val, RSON);}
	pushUp(v);
}

inline LLONG query(int l, int r, int ql, int qr, int v) {
	if (ql > qr) return oo;
	if(l >= ql && r <= qr) {
		return mn[v];
	}
	TMID;
	LLONG rlt = oo;
	if(mid >= ql) { rlt = query(l, mid, ql, qr, LSON);}
	if(mid < qr) { rlt = std::min(rlt, query(mid + 1, r, ql, qr, RSON));}
	return rlt;
}

inline void prepareUpNode(int n) {
	for(int i = 1; i < K; ++i) {
		for(int j = 1; j <= n; ++j) {
			up[j][i] = up[up[j][i - 1]][i - 1];
		}
	}
}

inline int getUpNode(int u, int d) {
	int rlt = u;
	for(int i = 0; d; d >>= 1, ++i) {
		if(d & 1) { rlt = up[rlt][i]; }
	}
	return std::max(rlt, 1);
}

inline void computeBestCost(int n, int u) {
	LLONG minCost = oo;
	for(int i = 0; u > 1 && i < scroll[u].size(); ++i) {
		int v = getUpNode(u, scroll[u][i].first);
		minCost = std::min(query(1, n, fp[v], toper, 1) + scroll[u][i].second, minCost);
	}
	stk[++toper] = u;
	fp[u] = toper;
	answer[u] = u < 2 ? 0 : minCost;
	update(1, n, toper, answer[u], 1);
	for(int e = head[u]; ~e; e = edge[e].second) {
		int v = edge[e].first;
		if(v != parent[u]) {
			computeBestCost(n, v);
		}
	}
	--toper;
}

int main() {
	int n, m, q;
	for(; ~scanf("%d%d", &n, &m);) {
		prepare(n);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(v, u);
		}
		dfs(1, 0, 1);
		prepareUpNode(n);
		for (int i = 0; i < m; ++i) {
			int u, v, k;
			scanf("%d%d%d", &u, &v, &k);
			scroll[u].push_back(std::make_pair(v, k));
		}
		computeBestCost(n, 1);
		scanf("%d", &q);
		for(; q--;) {
			int u;
			scanf("%d", &u);
			std::cout << answer[u] << std::endl;
		}
	}
	return 0;
}
