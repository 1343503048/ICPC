#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int N = 100000+5;

int height[N], dp[N];
int min(int a, int b) {
	return a < b? a : b;
}

// int upper_bound(int val, int l, int r){
// 	while(l <= r) {
// 		int m = (l + r) >> 1;
// 		if(dp[m] <= val) {
// 			r = m - 1;
// 		}
// 		else {
// 			l = m;
// 		}
// 	}
// 	return l;
// }

int main(int argc, char const *argv[]) {
	int n;
	while(~scanf("%d", &n)) {
		for(int i = 0; i < n; ++ i) {
			scanf("%d", height + i);
		}
		int loc = 0;
		dp[0] = height[0];
		for(int i = 1; i < n; ++ i) {
			if(dp[loc] <= height[i]) {
				dp[++loc] = height[i];
			}
			else {
				int j = lower_bound(dp, dp+loc, height[i]) - dp;
				dp[j] = height[i];
			}
		}
		printf("%d\n", loc+1);
	}
	return 0;
}
