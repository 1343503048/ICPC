#include <bits/stdc++.h>
using namespace std;
const int N = 100000+5;

int a[N];
int c[N];

int sum(int x) {
	int ans = 0;
	while(x > 0) {
		ans += c[x];
		x -= x&-x;
	}
	return ans;
}

void update(int x, int add) {
	while(x < N) {
		c[x] += add;
		x += x&-x;
	}
}

int main(int argc, char const *argv[]) {
	int n, k;
	while(cin >> n >> k) {
		memset(c, 0, sizeof(c));
		for(int i = 1; i <= n; ++ i) {
			a[i] = i;
		}
		for(int i = 1; i+i<=n && i <= k; ++ i) {
			swap(a[i], a[n-i+1]);
		}
		long long ans = 0;
		for(int i = 1; i <= n; ++ i) {
			update(a[i], 1);
			ans += i - sum(a[i]);		//求出比ai小的数的个数然后减i
		}
		cout << ans << endl;
	}
	return 0;
}