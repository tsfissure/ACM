#include <bits/stdc++.h>

typedef long long LLONG;
typedef std::pair<int, int>PII;

const int N = 1e5;
const int MOD = 1e9 + 7;

std::pair<int, PII>tracks[N];

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	LLONG rlt = 1LL * n * m;
	for(int i = 0; i < k; ++i) {
		int r, c, cc;
		scanf("%d%d%d", &r, &c, &cc);
		tracks[i] = {r, {c, cc} };
	}
	std::sort(tracks, tracks + k);
	for(int i = 0, j = 0; i < k; i = j) {
		int l = m, r = 0, curr = tracks[i].second.second;
		LLONG ex = 0;
		for(j = i; j < k && tracks[i].first == tracks[j].first; ++j) {
			l = std::min(tracks[j].second.first, l);
			r = std::max(r, tracks[j].second.second);
			ex += std::max(0, tracks[j].second.first - curr - 1);
			curr = std::max(curr, tracks[j].second.second);
		}
		rlt -= std::max(0, r - l + 1);
		rlt += ex;
	}
	std::cout << rlt << std::endl;
	return 0;
}
/*
10 10 5
3 2 3
3 4 7
3 25 44
3 10 30
3 10 20

2 10 3
1 2 5
1 1 3
1 7 9
*/
