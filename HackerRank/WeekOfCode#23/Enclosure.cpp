#include <bits/stdc++.h>

const int N = 1e5 + 10;
const double PI = acos(-1);
const double EPS = 1e-8;

int a[N];
double pos[N][2];

inline double computeAcos(double R, double d) {
	return acos(1 - (d * d) / (R * R * 2.0f));
}

inline double computeAngle(int n, double r, int exceptIdx = -1) {
	double rlt = 0;
	for(int i = 0; i < n; ++i) {
		if(i == exceptIdx) { continue; }
		rlt += computeAcos(r, a[i]);
	}
	return rlt;
}

inline void computePosition(int n, double R, bool bigger, int maxIdx) {
	pos[0][0] = 0; pos[0][1] = 0;
	pos[1][0] = 0; pos[1][1] = a[0];
	double circleX = -sqrt(R * R - a[0] * a[0] / 4.0f), circleY = a[0] / 2.0f;
	if(!bigger && 0 == maxIdx) {
		circleX *= -1;
	}
	for(int i = 1; i < n - 1; ++i) {
		double cosSita = 1 - (a[i] * a[i]) / (R * R * 2.0f);
		double sinSita = sqrt(1 - cosSita * cosSita);
		if(!bigger && i == maxIdx) {
			sinSita = -sinSita;
		}
		double x = pos[i][0] - circleX, y = pos[i][1] - circleY;
		pos[i + 1][0] = x * cosSita - y * sinSita + circleX;
		pos[i + 1][1] = x * sinSita + y * cosSita + circleY;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	double maxl = 0;
	int maxIdx = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(a[i] > maxl) {
			maxl = a[i];
			maxIdx = i;
		}
	}
	double l = maxl / 2.0f;
	double angle = computeAngle(n, l, maxIdx);
	bool bigger = angle >= PI - EPS;
	double r = 10000000, mid, answer;
	for(; std::fabs(r - l) >= EPS;) {
		mid = (l + r) / 2.0f;
		double angle = computeAngle(n, mid, maxIdx);
		double zero = computeAcos(mid, a[maxIdx]);
		if(bigger) {
			if(zero + angle > 2.0f * PI) {
				l = mid;
			} else {
				r = mid;
			}
		} else {
			if(angle > zero) {
				r = mid;
			} else {
				l = mid;
			}
		}
	}
	computePosition(n, l, bigger, maxIdx);
	for(int i = 0; i < n; ++i) {
		printf("%f\n%f\n\n", -(pos[i][0]), pos[i][1]);
	}
	return 0;
}
