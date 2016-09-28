#include <bits/stdc++.h>

typedef long long LLONG;
typedef std::pair<int, int>PII;

const int N = 1e6 + 10;
const LLONG MOD = 1e9 + 7;

inline void tryMulti(LLONG& o, LLONG mul) {
	if(o >= MOD) {
		o %= MOD;
	}
	o *= mul;
	if(o >= MOD) {
		o %= MOD;
	}
}
inline void tryAdd(LLONG& o, LLONG s) {
	o += s;
	if(o < 0) {
		o %= MOD;
		o += MOD;
	}
	if(o >= MOD) {
		o %= MOD;
	}
}

LLONG c[N], ci[N];
LLONG sc[N], sci[N];

inline void initial(int n) {
	sc[0] = c[0] = 1;
	sci[0] = ci[0] = 0;
	LLONG cur = 1;
	for(int i = 1; i <= n; ++i) {
		ci[i] = c[i] = cur;
		tryMulti(ci[i], i);
		sc[i] =  c[i];
		sci[i] = ci[i];
		tryAdd(sc[i], sc[i - 1]);
		tryAdd(sci[i], sci[i - 1]);
		tryMulti(cur, 2);
	}
}

inline LLONG compute(int x, int l, int r) {
	LLONG tmp = sc[l];
	tryMulti(tmp, sc[r]);
	tryMulti(tmp, l + r + 1);
	LLONG rlt = tmp;
	tmp = sci[l];
	tryMulti(tmp, sc[r]);
	tryAdd(rlt, -tmp);
	tmp = sci[r];
	tryMulti(tmp, sc[l]);
	tryAdd(rlt, -tmp);
	tryMulti(rlt, x);
	return rlt;
}

int main() {
	int n;
	scanf("%d", &n);
	initial(n);
	LLONG rlt = 0;
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		tryAdd(rlt, compute(x, i - 1, n - i));
	}
	std::cout << rlt % MOD << std::endl;
	return 0;
}
