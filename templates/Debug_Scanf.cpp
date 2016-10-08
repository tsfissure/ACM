#include <bits/stdc++.h>

//#define TDEBUG
#ifdef TDEBUG
#define tout(x) std::cerr << #x << " = " << x << std::endl;
#define tdebug(args...) { std::cerr << "(" << #args << ") => "; dbg, args; std::cerr << std::endl; }
#else
#define tout(x)	//skip all
#define tdebug(args...) 
#endif
struct Debuger {
	template<typename T>
	Debuger& operator, (const T& v) {
		std::cerr << v << " ";
		return *this;
	}
} dbg;
template<typename T>inline void scaf(T&v) {
	char ch = getchar();
	int sgn = 1;
	for (; '-' != ch && (ch < '0' || ch > '9'); ch = getchar());
	if ('-' == ch) sgn = -1, v = 0;
	else v = ch - '0';
	for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) v = (v << 1) + (v << 3) + ch - '0';
	v *= sgn;
}


int main() {
	double x = 3.3f;
	tdebug("first =", 1, 2, 3, 2, 1, 1.1, x);
	tout(x);
	tout(3);
	return 0;
}
