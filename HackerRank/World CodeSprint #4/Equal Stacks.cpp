#include <bits/stdc++.h>

typedef long long LLONG;
typedef unsigned long long ULLONG;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;

int a[N];
int b[N];
int c[N];

int main() {
	int n, m, h;
	scanf("%d%d%d", &n, &m, &h);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}
	for (int i = 0; i < m; ++i) {
		scanf("%d", b + i);
	}
	for (int i = 0; i < h; ++i) {
		scanf("%d", c + i);
	}
	int rlt = 0;
	for (int i = n - 2; i >= 0; --i)
		a[i] += a[i + 1];
	for (int i = m - 2; i >= 0; --i)
		b[i] += b[i + 1];
	for (int i = h - 2; i >= 0; --i)
		c[i] += c[i + 1];
	int i = 0, j = 0, k = 0;
	for (; i < n && j < m && k < h;) {
		if (a[i] == b[j] && a[i] == c[k]) {
			rlt = a[i];
			break;
		}
		if (a[i] >= b[j] && a[i] >= c[k]) ++ i;
		else if (a[i] <= b[j] && b[j] >= c[k]) ++j;
		else ++k;
	}
	printf("%d\n", rlt);
	return 0;
}
