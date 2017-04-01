// 依赖背包
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int m[N], dp[N];

int main() {
    int n, w;
    while(cin >> n >> w) {
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n; ++ i) {
	    int pi, mi;
	    cin >> pi >> mi;
	    memcpy(m, dp, sizeof(m));	    //更新上一层状态
	    for(int j = 0; j < mi; ++ j) {
		int cj, vj;
		cin >> cj >> vj;
		for(int k = w-pi; k >= cj; -- k) {
		    m[k] = max(m[k], m[k-cj]+vj);
		}
	    }
	    for(int j = w; j >= pi; -- j) {
		dp[j] = max(dp[j], m[j-pi]+dp[j-pi]);	    //如果上一层策略更好则更新
	    }
	}

	cout << dp[w] << "\n";
    }
    return 0;
}
