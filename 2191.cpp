#include <bits/stdc++.h>
using namespace std;
const int N = 100+5;

int dp[N];

int main(int argc, char const *argv[]) {
	int t;
	scanf("%d", &t);
	while (t --) {
		memset(dp, 0, sizeof(dp));
		int n, m, value, weight, cnt;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++ i) {
			scanf("%d%d%d", &value, &weight, &cnt);
			for(int k = 1; k <= cnt; ++ k) {	//不取的那种情况已经排除掉了，因为dp[j]对应的就是没取的状态  
				for(int j = n; j >= value; -- j) {
					dp[j] = max(dp[j], dp[j-value]+weight);
				}
			}
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}