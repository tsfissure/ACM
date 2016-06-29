#include <bits/stdc++.h>

const int N = 5e4 + 10;

char A[N];
char B[N];
char C[N];
int Abin[N << 2];
int Bbin[N << 2];
int Cbin[N << 2];

inline int hexToBinary(char* src, int dest[]) {
	int j = 0;
	for (int i = 0; src[i]; ++i, j += 4) {
		int key = src[i] - '0';
		if (src[i] >= 'A')
			key = src[i] - 'A' + 10;
		for (int k = 0; k < 4; ++k)
			dest[k + j] = (key & (1 << (3 - k))) > 0;
	}
	std::reverse(dest, dest + j);
	return j;
}

inline int countOfOne(int src[], int l, int r) {
	int rlt = 0;
	for (int i = l; i < r; ++i)
		rlt += src[i];
	return rlt;
}

inline bool assign(int src[], int idx, int toVal) {
	bool rlt = src[idx] > 0;
	src[idx] = toVal;
	return rlt;
}

inline char computeHex(int src[], int idx) {
	int rlt = 0;
	for (int i = 0; i < 4; ++i) {
		rlt |= src[idx + i] ? 1 << i : 0;
	}
	return rlt > 9 ? 'A' + rlt - 10 : rlt + '0';
}

inline void binaryToHex(int src[], char dest[]) {
	int lastOnePos = 0;
	for (int i = N << 2; i; --i) {
		if (src[i - 1]) {
			lastOnePos = i - 1;
			break;
		}
	}
	int hexLen = 0;
	for (int i = 0; i <= lastOnePos; i += 4) {
		dest[hexLen++] = computeHex(src, i);
	}
	dest[hexLen] = 0;
	std::reverse(dest, dest + hexLen);
}

int main() {
	int q, k;
	scanf("%d", &q);
	for (; q--;) {
		memset(Abin, 0, sizeof(Abin));
		memset(Bbin, 0, sizeof(Bbin));
		scanf("%d%s%s%s", &k, A, B, C);
		int Alen = hexToBinary(A, Abin);	//二进制长度
		int Blen = hexToBinary(B, Bbin);
		int Clen = hexToBinary(C, Cbin);

		//先计算多余的位并清0
		int mustChgInA = countOfOne(Abin, Clen, Alen), mustChgInB = countOfOne(Bbin, Clen, Blen);
		for (int i = Clen; i < Alen; ++i)
			Abin[i] = 0;
		for (int i = Clen; i < Blen; ++i)
			Bbin[i] = 0;

		//处理必须要变的位
		for (int i = 0; i < Clen; ++i) {
			if (!Cbin[i]) {
				mustChgInA += assign(Abin, i, 0);
				mustChgInB += assign(Bbin, i, 0);
			} else if (!Abin[i] && !Bbin[i]) {
				Bbin[i] = 1;
				++mustChgInB;
			}
		}

		int rlt = mustChgInA + mustChgInB;
		for (int i = Clen - 1; i >= 0 && rlt < k; --i) {
			if (Cbin[i]) {
				if (Abin[i] && Bbin[i]) {
					++rlt;
					Abin[i] = 0;
				} else if (Abin[i] && !Bbin[i]) {
					if (rlt + 2 <= k) {
						rlt += 2;
						Abin[i] = 0;
						Bbin[i] = 1;
					}
				}
			}
		}

		if (rlt > k) puts("-1");
		else {
			binaryToHex(Abin, A);
			binaryToHex(Bbin, B);
			printf("%s\n%s\n", A, B);
		}
	}
	return 0;
}
