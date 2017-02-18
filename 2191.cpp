//多重背包转化为01背包
#include <bits/stdc++.h>
using namespace std;
const int N = 500+5;

int dp[N], w[N], v[N];

int main(int argc, char const *argv[]) {
	int t;
	scanf("%d", &t);
	while (t --) {
		memset(dp, 0, sizeof(dp));
		int n, m, value, weight, cnt, pos = 0;
		scanf("%d%d", &n, &m);
		
		for(int i = 0; i < m; ++ i) {
			scanf("%d%d%d", &value, &weight, &cnt);
			int k = 1;
			while(k < cnt) {
				v[pos] = k * value;
				w[pos++] = k * weight;
				cnt -= k;
				k <<= 1;
			}
			v[pos] = cnt * value;
			w[pos++] = cnt * weight;
		}

		for(int i = 0; i < pos; ++ i) {
			for(int j = n; j >= v[i]; -- j) {
				dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
			}
		}

		printf("%d\n", dp[n]);
	}
	return 0;
}