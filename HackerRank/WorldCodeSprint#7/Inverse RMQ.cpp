#include <bits/stdc++.h>

typedef long long LLONG;
typedef std::pair<int, int>PII;
typedef std::map<int, int>MII;
typedef std::vector<int> VI;
typedef std::vector<PII>VPII;

const int N = 1e6 + 10;
const LLONG MOD = 1e9 + 7;

int vis[N];
bool asigned[N];
int answer[N];
int a[N];
int fpos[N];
MII hs;
PII cnts[N];

inline bool cmp(const PII& a, const PII& b) {
	if(a.first == b.first) return a.second > b.second;
	return a.first < b.first;
}

inline bool fix(int m, int np) {
	int cur = 1;
	int layer = 1;
	for(int i = np - 1, nxt; i >= 0; i = nxt, layer <<= 1) {
		VI forAsign;
		forAsign.clear();
		for(nxt = i; nxt >= 0 && cnts[nxt].first == cnts[i].first; --nxt) {
			forAsign.push_back(cnts[nxt].second);
		}
		VPII paces;
		paces.clear();
		VI poses;
		poses.clear();
		for(int k = layer | 1, j = 0; j < forAsign.size(); ++j, k += 2) {
			if(k > (layer << 1)) { return false; }
			paces.emplace_back(answer[k - 1], k);
		}
		for(int k, j = 0; j < paces.size(); ++j) {
			for(k = j; k < paces.size() && paces[j].first > forAsign[j]; ++k) {
				std::swap(forAsign[k], forAsign[j]);
			}
			if(k >= paces.size()) { return false; }
			for(int k = paces[j].second, c = 0; c < cnts[i].first; ++c, k <<= 1) {
				if(k > m) { return false;}
				answer[k] = forAsign[j];
				asigned[k] = 1;
			}
		}
	}
	for(int i = 1; i <= m; ++i) {
		if(!asigned[i]) { return false;}
	}
	return true;
}

int main() {
	int n;
	answer[0] = -MOD;
	scanf("%d", &n);
	int m = 2 * n - 1;
	bool mark = false;
	for(int i = 0; i < m; ++i) {
		scanf("%d", a + i);
		hs[a[i]] = true;
	}
	int np = 0;
	for(MII::iterator iter = hs.begin(); iter != hs.end(); ++iter) {
		iter->second = ++np;
		fpos[np] = iter->first;
	}
	for(int i = 0; i < m; ++i) {
		int p = hs[a[i]];
		++vis[p];
	}
	for(int i = 1; i <= np; ++i) {
		cnts[i - 1] = {vis[i], fpos[i]};
	}
	std::sort(cnts, cnts + np, cmp);
	if(!fix(m, np)) { puts("NO"); }
	else {
		puts("YES");
		for(int i = 1; i <= m; ++i) {
			if(i > 1) { putchar(32); }
			printf("%d", answer[i]);
		}
		putchar(10);
	}
	return 0;
}
/*
6 6 11 6 34 11 39 6 22 34 45 11 29 39 55
6 6 11 6 34 11 39 6 22 34 45 11 29 39 55
8
9 9 18 54 9 27 18 54 63 30 9 27 42 32 18
*/
