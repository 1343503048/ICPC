#include <bits/stdc++.h>
using namespace std;

int dp[10005], weight, value;
const int inf = 100000000;

int main( ) {
	int t;
	scanf("%d", &t);
	while(t --) {
		int e, f, n;
		scanf("%d %d %d", &e, &f, &n);
		f = f - e;

		for(int i = 1; i <= f; ++ i) {
			dp[i] = inf;
		}
		dp[0] = 0;

		for(int i = 0; i < n; ++ i) {
			scanf("%d %d", &value, &weight);
			for(int j = weight; j <= f; ++ j) {
				dp[j] = min(dp[j], dp[j - weight] + value);		//设为INT_MAX会溢出
			}
		}

		if(dp[f] >= inf) {
			puts("This is impossible.");
		}
		else {
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[f]);
		}
	}
	return 0;
}