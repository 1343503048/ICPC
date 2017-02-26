#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int dp[N][40];
int val[N];

void st(int n){
	for(int i = 1; i <= n; ++ i) {
		dp[i][0] = val[i];
	}
	for(int j = 1; (1<<j) < n; ++ j) {
		for(int i = 1; i + (1<<j) - 1 <= n; ++ i) { //~!!!!!
			dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r) {
	int k = log(r-l+1)/log(2);
	int a = dp[l][k];
	int b = dp[r-(1<<k)+1][k];
	return min(a, b);
}

int main(int argc, char const *argv[]) {
	// freopen("data.in", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++ i) {
		printf("Case %d:\n", i);
		int n, q, l, r;
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; ++ i) {
			scanf("%d", val + i);
		}
		st(n);
		while(q--) {
			scanf("%d%d", &l, &r);
			printf("%d\n", query(l, r));
		}
	}
	return 0;
}