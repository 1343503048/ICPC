#include <bits/stdc++.h>
using namespace std;

int value[1005];
int dp[1005];

int main(int argc, char const *argv[]) {
	int t;
	cin >> t;
	while(t --) {
		int n, v, volume;
		memset(dp, 0, sizeof(dp));
		cin >> n >> v;
		for(int i = 0; i < n; ++ i) {
			cin >> value[i];
		}

		for(int i = 0; i < n; ++ i) {
			cin >> volume;
			for(int j = v; j >= volume; -- j) {
				dp[j] = max(dp[j], dp[j - volume] + value[i]);
			}
		}

		cout << dp[v] << endl;
	}
	return 0;
}