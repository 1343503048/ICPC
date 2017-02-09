#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;
double l[10005];

bool isOk(double li, int n, int k) {
	int cnt = 0;
	for(int i = 0; i < n; ++ i) {
		cnt += (int)(l[i]/li);
	}
	return cnt >= k;
}

int main() {	
	int n, k;
	while(~scanf("%d%d", &n, &k)) {
		for(int i = 0; i < n; ++ i) {
			scanf("%lf", l+i);
		}
		double left = 0, right = 100000;
		for(int i = 0; i < 100; ++ i) {
			double mid = (left + right) / 2.0;
			if(isOk(mid, n, k)) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		printf("%.2f\n", floor(right*100) / 100);
	}
	return 0;
}