#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, k, m;
	while(scanf("%d%d%d", &n, &k, &m) && n && m && k) {
		int ans = 0;
		for(int i = 2; i <= n; ++ i) {
			ans = (ans + k) % i;
		}
		//第一次删除的是m,故需要减去一个k
		ans = (m-k+1+ans) % n;
		if(ans <= 0) {
			ans += n;
		}
		printf("%d\n", ans);
	}
	return 0;
}