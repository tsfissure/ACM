#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>

typedef long long LLONG;
typedef long long ULLONG;
typedef std::pair<int, int>PII;
#define	dout(x) std::cout << #x << " = " << x << std::endl;
#define LSON v << 1
#define RSON v << 1 | 1
#define TMID int mid = l + r >> 1

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;
const int K = 20;

int depth[N];
LLONG d2[N], d[N], rd2[N], rd[N];
int son[N], parent[N];
PII edge[N];
int head[N], etot;
int up[N][K];

inline void addEdge(int u, int v) {
	edge[etot] = std::make_pair(v, head[u]);
	head[u] = etot++;
}

inline void assign(int u) {
	int f = parent[u];
	depth[u] = depth[f] + 1;
	up[u][0] = f; son[u] = 1;
	d[u] = 0; d2[u] = 0;
}

inline void compute(int u, int v) {
	son[u] += son[v];
	d2[u] += d2[v] + 2 * d[v] + son[v];
	d[u] += d[v] + son[v];
}

inline void dfs(int u) {
	assign(u);
	for (int e = head[u]; ~e; e = edge[e].second) {
		int v = edge[e].first;
		dfs(v);
		compute(u, v);
	}
}

inline std::tuple<LLONG, LLONG, LLONG>compute(int n, int u, int v) {
	return std::make_tuple(n - son[v], rd[u] - d[v] - son[v], rd2[u] - d2[v] - 2 * d[v] - son[v]);
}

inline void dfs(int n, int f) {
	for (int e = head[f]; ~e; e = edge[e].second) {
		int v = edge[e].first;
		LLONG tmpsonf, tmpdf, tmpd2f;
		std::tie(tmpsonf, tmpdf, tmpd2f) = compute(n, f, v);
		rd2[v] = d2[v] + tmpd2f + 2 * tmpdf + tmpsonf;
		rd[v] = d[v] + tmpdf + tmpsonf;
		dfs(n, v);
	}
}

inline void prepareReverse(int n) {
	rd2[1] = d2[1];
	rd[1] = d[1];
	dfs(n, 1);
}

inline void prepareLca(int n) {
	for (int i = 1; i < K; ++i) {
		for (int j = 1; j <= n; ++j) {
			up[j][i] = up[up[j][i - 1]][i - 1];
		}
	}
}

inline void prepare(int n) {
	memset(head + 1, -1, n * sizeof(head[1]));
	etot = 0;
}

inline int getUpNode(int v, int dis) {
	for (int i = 0; dis; dis >>= 1, ++i) {
		if (dis & 1) {
			v = up[v][i];
		}
	}
	return v;
}

inline int getLca(int u, int v) {
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	v = getUpNode(v, depth[v] - depth[u]);
	if (u == v) {
		return u;
	}
	for (int i = K - 1; i >= 0; --i) {
		if (up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}
	return up[u][0];
}

inline int computeDistance(int u, int v) {
	return depth[u] + depth[v] - 2 * depth[getLca(u, v)];
}

int main() {
	int n, q;
	scanf("%d", &n);
	prepare(n);
	for (int i = 2; i <= n; ++i) {
		int p;
		scanf("%d", &p);
		addEdge(p, i);
		parent[i] = p;
	}
	dfs(1);
	prepareReverse(n);
	prepareLca(n);
	for (scanf("%d", &q); q--;) {
		int u, v;
		scanf("%d%d", &u, &v);
		LLONG dis = computeDistance(u, v);
		if (getUpNode(u, dis) == v) {
			if (dis < 1) std::cout << d2[v] << std::endl;
			else {
				int pt = parent[v];
				if (0 == pt) {
					std::cout << rd2[u] << std::endl;
				} else {
					++dis;
					LLONG tmpdpt, tmpsonpt, tmpd2pt;
					std::tie(tmpsonpt, tmpdpt, tmpd2pt) = compute(n, pt, v);
					LLONG rlt = rd2[u] - tmpd2pt - dis * 2 * tmpdpt - dis * dis * tmpsonpt;
					std::cout << rlt << std::endl;
				}
			}
		} else {
			LLONG rlt = d2[v] + 2 * dis * d[v] + dis * dis * son[v];
			std::cout << rlt << std::endl;
		}
	}
	return 0;
}
