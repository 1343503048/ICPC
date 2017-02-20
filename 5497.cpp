// Problem: 5497
// User: zq216991
// Language: C++
// Result: Accepted
// Time:2199 ms
// Memory:4046 kb
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
typedef long long ll ;

ll a[N], b[N], c[N];
int n, m;

void update(ll arr[], ll x, int v) {
	while(x <= n) {
		arr[x] += v;
		x += x & -x;
	}
}

int sum(ll arr[], ll x) {
	int ans = 0;
	while(x > 0) {
		ans += arr[x];
		x -= x&-x;
	}
	return ans;;
}

int main(int argc, char const *argv[]) {
	int t;
	scanf("%d", &t);
	while(t --) {
		memset(b, 0 ,sizeof(b));
		memset(c, 0, sizeof(c));
		scanf("%d%d", &n, &m);

		ll cur  = 0;
		for(int i = 1; i <= n; ++ i) {
			scanf("%lld", a+i);
		}
		for (int i = m + 1; i <= n; ++i) {
			update(b, a[i], 1);
			cur += i - m - sum(b, a[i]);
		}

		ll ans = cur;
		for(int i = m + 1; i <= n; ++ i) {
			cur += sum(b, a[i-m]-1);		//统计有多少数a[i-m]小,且在a[i-m]后的
			cur += sum(c, n) - sum(c, a[i-m]);	//统计有多少数比a[i-m]大，且在a[i-m]前的
			update(c, a[i-m], 1);
			cur -= sum(b, a[i]-1);			 //统计有多少数a[i]小,且在a[i]后的
			cur -= sum(c, n) - sum(c, a[i]); //统计有多少数比[i-m]大,且在a[i]前的
			update(b, a[i], -1);
			ans = min(ans, cur);
		}
		printf("%lld\n", ans);
	}
	return 0;
}