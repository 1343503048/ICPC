#include <bits/stdc++.h>
using namespace std;
const int MAX = 40000+5;

map<int, int> e[MAX];
bool vis[MAX];

int dfs(int s, int t) {
	vis[s] = true;
	for(map<int, int>::iterator it = e[s].begin(); it != e[s].end(); ++ it) {
		int to = it->first, w = it->second;
		if(!vis[to]) {
			if(to == t) {
				return w;
			}
			int temp = dfs(to, t);
			if(temp > 0) {
				return w + temp;
			}
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		int n, m;
		cin >> n >> m;
		for(int i = 1; i <= n; ++ i) {
			e[i].clear();
		}
		while(-- n) {
			int i, j, w;
			cin >> i >> j >> w;
			e[i][j] = w;
			e[j][i] = w;
		}
		while(m --) {
			memset(vis, false, sizeof(vis));
			int i, j;
			cin >> i >> j;
			cout << dfs(i, j) << endl;
		}
	}
	return 0;
}