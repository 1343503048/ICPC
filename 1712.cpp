#include <bits/stdc++.h>
using namespace std;

int dp[105];
int data[105][105];

int main() {
	ifstream cin("data.in");
	int n, m;
	while(cin >> n >> m && n != 0) {
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < n; ++ i) {
			for(int j = 1; j <= m; ++ j) {
				cin >> data[i][j];
			}
		}

		for(int i = 0; i < n; ++ i) {
			for(int k = m; k >= 0; -- k) {
				for(int j = 1; j <= k; ++ j) {
					dp[k] = max(dp[k], dp[k-j] + data[i][j]);
				}
			}
		}

		cout << dp[m] << endl;
	}
	return 0;
}