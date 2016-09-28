#include <bits/stdc++.h>

//#define TDEBUG
#ifdef TDEBUG
#define tout(x) std::cerr << #x << " = " << x << std::endl;
#define tdebug(args...) { std::cerr << "(" << #args << ") => "; dbg,args; std::cerr << std::endl; }
#else
#define tout(x)	//skip all
#define tdebug(args...)
#endif
struct Debuger {
	template<typename T>
	Debuger& operator, (const T& v) {
		std::cerr << v << " ";
		return *this;
	}
} dbg;

typedef std::pair<int, int>PII;

const int SCCNODE = 4e2 + 10;
struct SCC {

	SCC(): useStamp(0), timeStamp(0) {
	}

	void clear(int n) {
		for(int i = 0; i <= n; ++i) {
			edges[i].clear();
		}
		toper = 0;
		useStamp += 2;
	}

	void addEdge(int u, int v) { edges[u].push_back(v);}

	bool notUse(int u) { return instk[u] < useStamp; }
	bool useNow(int u) { return instk[u] == useStamp; }
	void use(int u) { instk[u] = useStamp; }
	void raise(int u) { instk[u] = useStamp + 1;}

	void tarjan(int u) {
		low[u] = dfn[u] = ++timeStamp;
		stk[toper++] = u;
		use(u);
		for(auto v : edges[u]) {
			if(notUse(v)) {
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			} else if (useNow(v)) {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
		if(low[u] == dfn[u]) {
			for(; toper > 0;) {
				int tmp = stk[--toper];
				raise(tmp);
				cycle[tmp] = u;
				if(tmp == u) break;
			}
		}
	}

	void shrink(int n) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < edges[i].size(); ++j) {
				edges[i][j] = cycle[edges[i][j]];	//Careful, this will create self-loop
			}
		}
		for(int i = 0; i < n; ++i) {
			if(cycle[i] == i) continue;
			int u = cycle[i];
			for(int j = 0; j < edges[i].size(); ++j) {
				edges[u].push_back(edges[i][j]);
			}
			edges[i].clear();
		}
		for(int i = 0; i < n; ++i) {//Not always necessary
			std::sort(edges[i].begin(), edges[i].end());
			std::unique(edges[i].begin(), edges[i].end());
		}
	}

	int computeSCC(int n) {
		int rlt = 0;
		for(int i = 0; i < n; ++i) {
			if(notUse(i)) {tarjan(i); }
		}
		for(int i = 0; i <= n; ++i) {
			rlt += cycle[i] == i;
		}
		return rlt;
	}

	bool inSameCycle(int a, int b) { return cycle[a] == cycle[b]; }
private:
	std::vector<int> edges[SCCNODE];
	int low[SCCNODE], dfn[SCCNODE], cycle[SCCNODE], stk[SCCNODE], instk[SCCNODE];
	int timeStamp, toper, useStamp;
};

struct SAT2 {
	SAT2(): n(0) { }
	void clear(int nn) {
		n = nn;
		scc.clear(n << 1);
	}
	//0~n-1: no, n~n*2-1: yes

	void orClause(int a, int b) { // a || b
		scc.addEdge(a, b + n);
		scc.addEdge(b, a + n);
	}

	void xorClause(int a, int b) {
		scc.addEdge(a, b + n);
		scc.addEdge(a + n, b);
		scc.addEdge(b, a + n);
		scc.addEdge(b + n, a);
	}

	void notAndClause(int a, int b) {
		scc.addEdge(a + n, b);
		scc.addEdge(b + n, a);
	}

	bool possible() {
		(scc.computeSCC(n << 1));
		for(int i = 0; i < n; ++i) {
			if(scc.inSameCycle(i, i + n)) { return false; }
		}
		return true;
	}

private:
	SCC scc;
	int n;
} sat2;

const int N = 1e2 + 10;
PII segs[N << 1];

inline void build(int l, int r) {
	int s = l << 1, e = r << 1 | 1;
	for(int i = s; i < e; i += 2) {
		sat2.xorClause(i, i + 1);
	}
	for(int i = s; i < e; ++i) {
		for(int j = i + 1; j <= e; ++j) {
			if(segs[i].first > segs[j].second || segs[i].second < segs[j].first); //no overlap
			else {
				sat2.notAndClause(i, j);
			}
		}
	}
}

int main() {
	int t, n;
	for(scanf("%d", &t); t--;) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			int s, e, ss, ee;
			scanf("%d%d%d%d", &s, &e, &ss, &ee);
			segs[i << 1] = {s, e};
			segs[i << 1 | 1] = {ss, ee};
		}
		int ansl = 0, ansr = 0;
		for(int l = 0, r = 1; r < n; ++r) {
			sat2.clear(n << 1);
			build(l, r);
			for(; !sat2.possible();) {
				sat2.clear(n << 1);
				build(++l, r);
			}
			if(r - l > ansr - ansl) {
				ansl = l; ansr = r;
			}
		}
		printf("%d %d\n", ansl + 1, ansr + 1);
	}
	return 0;
}
