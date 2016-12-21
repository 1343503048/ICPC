#include <bits/stdc++.h>
using namespace std;

int data[30], dp[30][30], pow2[30];

int main() {
	ifstream cin("data.in");
	int n = 6;
	for(int i = 0; i < n; i ++) {
		cin >> data[i];
		cout << data[i] << " ";
		dp[i][0] = data[i];
	}
	cout << endl;
	int m = log(n)/log(2);			//2^m=n
	for(int j = 1; j <= m; ++ j) {
		for(int i = 0; i < n; ++ i) {
			if((i+(1<<j)-1) < n) {
				dp[i][j] = max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
			}
		}
	}
	
	int a, b;
	while(cin >> a >> b) {
		//cout << "111" << endl;
		int k = log(b-a+1) / log(2);
		//cout << k << endl;
		cout << a << "," << b << " : " ;
		cout << max(dp[a][k], dp[b-(1<<k)+1][k]) << endl;
	}
	return 0;
}
