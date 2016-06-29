#include <bits/stdc++.h>

typedef long long LLONG;
typedef unsigned long long ULLONG;
typedef std::pair<int, std::pair<int, int> >PIPII;
typedef std::pair<int, int>PII;

const int mod = 1e9 + 7;
const int N = 2e5 + 10;

PIPII edges[N], treeEdges[N];
int root[N >> 1];
LLONG c[N << 1];
int head[N >> 1], etot;
int sonCount[N >> 1];

inline void addEdge(int u, int v, int w) {
	treeEdges[etot] = std::make_pair(head[u], std::make_pair(v, w));
	head[u] = etot++;
}

inline void addEdge(const PIPII& edge) {
	int u = edge.second.first;
	int v = edge.second.second;
	int w = edge.first;
	addEdge(u, v, w);
	addEdge(v, u, w);
}

inline int findSet(int x) {
	return root[x] = root[x] == x ? x : findSet(root[x]);
}

inline void unionSet(const PIPII& edge) {
	int u = findSet(edge.second.first);
	int v = findSet(edge.second.second);
	if (u != v) {
		root[u] = v;
		addEdge(edge);
	}
}

inline void dfs(int n, int u, int f) {
	for (int e = head[u]; ~e; e = treeEdges[e].first) {
		int v = treeEdges[e].second.first;
		if (v != f) {
			dfs(n, v, u);
			sonCount[u] += sonCount[v];
			c[treeEdges[e].second.second] += 1LL * (n - sonCount[v]) * sonCount[v];
		}
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		root[i] = i;
		sonCount[i] = 1;
		head[i] = -1;
	}
	etot = 0;
	memset(c, 0, sizeof(c));

	int u, v, w;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		edges[i] = std::make_pair(w, std::make_pair(u, v));
	}

	std::sort(edges, edges + m);
	for (int i = 0; i < m; ++i) {
		unionSet(edges[i]);
	}

	dfs(n, 1, -1);
	int mx = N << 1;
	mx -= 2;
	for (int i = 0; i < mx; ++i) {
		c[i + 1] += c[i] >> 1;
		c[i] &= 1;
	}
	int lastOnePos = 0;
	for (lastOnePos = mx; lastOnePos > 0 && !c[lastOnePos]; --lastOnePos);
	for (int i = lastOnePos; i >= 0; --i)
		printf("%d", c[i]);
	putchar(10);

	return 0;
}
