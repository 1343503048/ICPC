#include <bits/stdc++.h>
using namespace std;
const int MAX = 50000+5;

int f[MAX], dist[MAX];

int find(int x) {
	if(f[x] == x) {
		return f[x];
	}
	int temp = f[x];
	f[x] = find(f[x]);
	dist[x] += dist[temp];
	return f[x];
}

int merge(int x, int y, int w) {
	int x0 = find(x);
	int y0 = find(y);
	if(x0 == y0) {
		if(dist[x] + w == dist[y]) {
			return 0;
		}
		else {
			return 1;
		}
	}
	f[y0] = x0;
	dist[y0] = dist[x0] + w - dist[y0];
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in"); 
	int n, m;
	while(cin >> n >> m) {
		int cnt = 0;
		for(int i = 1; i <= n; ++ i) {
			f[i] = i;
			dist[i] = 0;
		}
		while(m --) {
			int a, b, x;
			cin >> a >> b >> x;
			cnt += merge(a, b, x);
		}
		cout << cnt << endl;
	}
	return 0;
}