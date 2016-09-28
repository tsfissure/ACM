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

int main() {
	double x = 3.3f;
	tdebug("first =", 1, 2, 3, 2, 1, 1.1, x);
	tout(x);
	tout(3);
	return 0;
}
