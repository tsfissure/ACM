#include <bits/stdc++.h>

typedef long long LLONG;
typedef unsigned long long ULLONG;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;

int a[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}
	int rlt = n + 1;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n && j < i + rlt; ++j)
			if (a[i] == a[j]) {
				rlt = std::min(rlt, j - i);
				break;
			}
	printf("%d\n", rlt > n ? -1 : rlt);
	return 0;
}
