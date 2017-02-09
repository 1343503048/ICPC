#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;
int l[10005];

bool isOk(int li, int n, int k) {
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
			double temp;
			scanf("%lf", &temp);
			l[i] = 100*temp;
		}
		int left = 1, right = 10000000;
		while(left <= right) {
			int mid = (left + right) / 2;
			if(isOk(mid, n, k)) {
				left = mid+1;
			}
			else {
				right = mid-1;
			}
		}
		printf("%.2f\n", right / 100.0);
	}
	return 0;
}