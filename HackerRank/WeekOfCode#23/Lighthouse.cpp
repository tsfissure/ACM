#include <bits/stdc++.h>

const int N = 1e2 + 10;

char g[N][N];

inline bool check(int i, int j, int ii, int jj, int k) {
	int x1 = std::abs(i - ii), y1 = std::abs(j - jj);
	return k * k < x1 * x1 + y1 * y1;
}

inline bool check(int n, int k) {
	for(int i = k; i <= n - k; ++i) {
		for(int j = k; j <= n - k; ++j) {
			if('.' == g[i][j]) {
				bool mark = false;
				for(int ii = 1; !mark && ii <= n; ++ii) {
					for(int jj = 1; !mark && jj <= n; ++jj) {
						if('.' != g[ii][jj] && !check(i, j, ii, jj, k)) {
							mark = true;
						}
					}
				}
				if(!mark) return true;
			}
		}
	}
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", g[i]);
	}
	int l = 0, r = n / 2 + 1, mid, answer = 0;
	for(; l <= r;) {
		mid = l + r >> 1;
		if(check(n, mid)) {
			answer = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d\n", answer);
	return 0;
}
