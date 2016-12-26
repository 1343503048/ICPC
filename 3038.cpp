#include <bits/stdc++.h>
using namespace std;
const int MAX = 200000+5;

int f[MAX], dist[MAX];

int find(int x) {
	if(x == f[x]){
		return f[x];
	}
	int temp = f[x];
	f[x] = find(f[x]);
	dist[x] += dist[temp];
	return f[x];
}

int meger(int x, int y, int w) {
	int x0 = find(x);
	int y0 = find(y);
	if(x0 == y0) {
		if(dist[x] + w != dist[y]){
			return 1;
		}	
		return 0;
	}
	dist[y0] = dist[x] + w - dist[y];
	f[y0] = x0;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	ifstream cin("data.in");
	int n, m;
	while(cin >> n >> m) {
		int cnt = 0;
		for(int i = 0; i <= n; ++ i){
			f[i] = i;
			dist[i] = 0;
		}
		while(m--){
			int a, b, w;
			cin >> a >> b >> w;
			cnt += meger(a-1, b, w);	
		}
		cout << cnt << endl;
	}
	return 0;
}
