#include <bits/stdc++.h>

typedef long long ULLONG;

const int N = 5e5 + 10;
const int MOD = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int magic = 31;

char s[N];
ULLONG hs[N];
ULLONG hs2[N];
ULLONG power[N];
ULLONG power2[N];

inline ULLONG get(int l, int r) {
	return hs[r] - hs[l] * power[r - l];
}

inline ULLONG get(int l, int r, ULLONG h[], ULLONG p[], LLONG m) {
	return ((h[r] - h[l] * p[r - l]) % m + m) % m;
}

int main() {
	LLONG n;
	scanf("%s%lld", s, &n);
	int lth = 0;
	power[0] = 1;
	power2[0] = 1;
	for (int i = 0; s[i]; ++i) {
		++lth;
		hs[i + 1] = (hs[i] * magic + s[i] - 'a') % MOD;
		hs2[i + 1] = (hs2[i] * magic + s[i] - 'a') % MOD2;
		power[i + 1] = power[i] * magic % MOD;
		power2[i + 1] = power2[i] * magic % MOD2;
	}
	int minlth = lth;
	for (int i = 1; i <= lth; ++i) {
		if (lth % i == 0) {
			bool mark = true;
			for (int j = i; j <= lth && mark; j += i) {
				if (get(j - i, j, hs, power, MOD) != hs[i] || get(j - i, j, hs2, power2, MOD2) != hs2[i]) {
					mark = false;
				}
			}
			if (mark) {
				minlth = i; break;
			}
		}
	}
	printf("%d\n", (n / minlth) % MOD);
	return 0;
}
