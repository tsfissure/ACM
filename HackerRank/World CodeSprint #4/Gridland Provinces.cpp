#include <bits/stdc++.h>

typedef long long LLONG;
typedef unsigned long long ULLONG;
typedef std::pair<LLONG, LLONG>PLL;

const int N = 666;
const int MAGIC = 131;
const LLONG MOD[] = {1e9 + 7, 1e9 + 9};

PLL paths[N * N * 4];
ULLONG power[N << 2][2];
char s[2][N];
ULLONG preHash[2][N][2];	//preHash_i,j,k表示从s[i][j]到s[i][1]再到s[i^1][1]到s[i^1][j]同时%MOD[k]
ULLONG suffixHash[2][N][2];	//preHash_i,j,k表示从s[i][j]到s[i][n]再到s[i^1][n]到s[i^1][j]同时%MOD[k]
int toper;

inline int get(int layer, int idx) {
	return s[layer][idx];
}

inline void calcPreStr(int layer, int k, int modIdx, ULLONG& answer) {
	answer = ((answer * power[k << 1][modIdx]) % MOD[modIdx] + preHash[layer][k][modIdx]) % MOD[modIdx];
}

inline void calcSuffixStr(int layer, int n, int k, int modIdx, ULLONG& answer) {
	answer = ((answer * power[(n - k + 1) << 1][modIdx]) % MOD[modIdx] + suffixHash[layer][k][modIdx]) % MOD[modIdx];
}

inline void init(int n) {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j) {
			preHash[i][0][j] = 0;
			suffixHash[i][n + 1][j] = 0;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k) {
				preHash[j][i][k] = (get(j, i) * power[(i - 1) << 1][k] + preHash[j][i - 1][k]) % MOD[k];
				preHash[j][i][k] = (preHash[j][i][k] * MAGIC + get(j ^ 1, i)) % MOD[k];
			}

	for (int i = n; i > 0; --i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k) {
				suffixHash[j][i][k] = (get(j, i) * power[(n - i) << 1][k] + suffixHash[j][i + 1][k]) % MOD[k];
				suffixHash[j][i][k] = (suffixHash[j][i][k] * MAGIC + get(j ^ 1, i)) % MOD[k];
			}
}

inline void addColumn(ULLONG& rlt, int layer, int p, int modIdx) {
	rlt = (rlt * MAGIC % MOD[modIdx] + get(layer, p)) % MOD[modIdx];
	rlt = (rlt * MAGIC % MOD[modIdx] + get(layer ^ 1, p)) % MOD[modIdx];
}

inline void calcLtoR(int p, int n, int layer) {
	ULLONG answer[2] = {0};
	for (int i = 0; i < 2; ++i) {
		calcPreStr(layer ^ 1,  p - 1, i, answer[i]);
	}
	for (int j = p; j <= n; ++j, layer ^= 1) {
		ULLONG tmpAnswer[2];
		for (int i = 0; i < 2; ++i) {
			tmpAnswer[i] = answer[i];
			calcSuffixStr(layer, n, j, i, tmpAnswer[i]);
			addColumn(answer[i], layer, j, i);
		}
		paths[toper++] = std::make_pair(tmpAnswer[0], tmpAnswer[1]);
	}
}

inline void calcRtoL(int p, int n, int layer) {
	ULLONG answer[2] = {0};
	for (int i = 0; i < 2; ++i) {
		calcSuffixStr(layer ^ 1, n, p + 1, i, answer[i]);
	}
	for (int j = p; j > 0; --j, layer ^= 1) {
		ULLONG tmpAnswer[2];
		for (int i = 0; i < 2; ++i) {
			tmpAnswer[i] = answer[i];
			calcPreStr(layer, j, i, tmpAnswer[i]);
			addColumn(answer[i], layer, j, i);
		}
		paths[toper++] = std::make_pair(tmpAnswer[0], tmpAnswer[1]);
	}
}

int main() {
	power[0][0] = 1;
	power[0][1] = 1;
	for (int i = 1; i - N < (N << 1); ++i) {
		for (int j = 0; j < 2; ++j) {
			power[i][j] = (power[i - 1][j] * MAGIC) % MOD[j];
		}
	}
	int t, n;
	scanf("%d", &t);
	for (; t--;) {
		scanf("%d%s%s", &n, s[0] + 1, s[1] + 1);
		init(n);
		toper = 0;
		for (int i = 1; i <= n; ++i) {
			calcLtoR(i, n, 0);
			calcLtoR(i, n, 1);

			calcRtoL(i, n, 0);
			calcRtoL(i, n, 1);
		}
		std::sort(paths, paths + toper);
		int tot = std::unique(paths, paths + toper) - paths;
		printf("%d\n", tot);
	}
	return 0;
}
