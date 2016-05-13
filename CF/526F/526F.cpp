#pragma comment(linker,"/STACK:102400000,102400000")#include <bits/stdc++.h>namespace Defination {typedef long long LLONG;static const int sciArraySize = 3e5 + 10;#define debug(x) std::cout << #x << " = " << x << std::endl;};using namespace Defination;struct SegmentTree {#define LSON	v << 1#define RSON	v << 1 | 1	void build(int l, int r, int v) {		minValue[v] = l;		if (l >= r) {			countOfMinValue[v] = 1;			return;		}		int mid = l + r >> 1;		build(l, mid, LSON);		build(mid + 1, r, RSON);	}	int getCountIfValue(int v, int mv) {return minValue[v] + lazy[v] == mv ? countOfMinValue[v] : 0;}	void pushUp(int v) {		int mv = std::min(minValue[LSON] + lazy[LSON], minValue[RSON] + lazy[RSON]);		minValue[v] = mv;		countOfMinValue[v] = getCountIfValue(LSON, mv) + getCountIfValue(RSON, mv);	}	void pushDown(int v) {		if (lazy[v]) {			lazy[LSON] += lazy[v];			lazy[RSON] += lazy[v];			lazy[v] = 0;		}	}	void update(int l, int r, int x, int y, int addValue, int v) {		if (l >= x && r <= y) {			lazy[v] += addValue;			if (x >= y) countOfMinValue[v] = 1;			return;		}		pushDown(v);		int mid = l + r >> 1;		if (mid >= x) update(l, mid, x, y, addValue, v << 1);		if (mid < y) update(mid + 1, r, x, y, addValue, v << 1 | 1);		pushUp(v);	}private:	int minValue[sciArraySize << 2];	int lazy[sciArraySize << 2];	int countOfMinValue[sciArraySize << 2];} tree;int A[sciArraySize];int dpLager[sciArraySize];//(dp[i],i]半开半闭区间里的数都大于等于第i个数int dpLower[sciArraySize];//(dp[i],i]半开半闭区间里的数都小于等于第i个数int main() {	int n;	LLONG answer = 0;	scanf("%d", &n);	for (int i = 1; i <= n; ++i) {		int r, c;		scanf("%d%d", &r, &c);		A[r] = c;	}	tree.build(1, n, 1);//重点把j加进去	for (int i = 1; i <= n; ++i) {		//计算最左边的pos使得(dp[i],i]的数满足dp条件		//同时把上次在公式中运用到的值恢复回去， 方便重新计算公式		for (dpLower[i] = i - 1; dpLower[i] > 0 && A[dpLower[i]] <= A[i]; dpLower[i] = dpLower[dpLower[i]])			tree.update(1, n, dpLower[dpLower[i]] + 1, dpLower[i], -A[dpLower[i]], 1);		for (dpLager[i] = i - 1; dpLager[i] > 0 && A[dpLager[i]] >= A[i]; dpLager[i] = dpLager[dpLager[i]])			tree.update(1, n, dpLager[dpLager[i]] + 1, dpLager[i], A[dpLager[i]], 1);		tree.update(1, n, dpLower[i] + 1, i, A[i], 1);		tree.update(1, n, dpLager[i] + 1, i, -A[i], 1);		answer += tree.getCountIfValue(1, i);//等于i	}	printf("%I64d\n", answer);	return 0;}