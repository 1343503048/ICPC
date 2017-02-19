#include <bits/stdc++.h>
using namespace std;

int dp[105][105];

int main(int argc, char const *argv[]) {
	int n, m, k, s;
	while(cin >> n >> m >> k >> s) {
		memset(dp, 0, sizeof(dp));
		int ans = -1;
		for(int i = 0; i < k; ++ i) {
			int a, b;
			cin >> a >> b;
			for(int j = 1; j <= s; ++ j) {
				for(int p = b; p <= m; ++ p) {
					dp[j][p] = max(dp[j][p], dp[j-1][p-b] + a);
					if(dp[j][p] >= n) {
						ans = max(ans, m-p);
					}
				}
			}
		}
		cout << ans << endl;
	}	
	return 0;
}