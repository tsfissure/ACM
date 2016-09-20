#include <bits/stdc++.h>

int main() {
	int t, n, m;
	scanf("%d", &t);
	for(; t--;) {
		scanf("%d", &n);
		if(n < 3) { puts("Yes");}
		else {
			puts(n & 1 ? "No" : "Yes");
		}
	}
	return 0;
}
