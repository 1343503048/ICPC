#include <bits/stdc++.h>
using namespace std;
const int MAX = 40000+5;

vector<int> num[MAX], query[MAX];
map<int, int> e[MAX];
bool vis[MAX];
int answer[205], dist[MAX], f[MAX];

int find(int x) {
	if(f[x] != x) {
		f[x] = find(f[x]);
	}
	return f[x];
}

void unit(int x, int y) {
	x = find(x);
	y = find(y);
	if(x != y) {
		f[y] = x;
	}
}

void tarjan(int cur, int w) {
	vis[cur] = true;
	dist[cur] = w;
	map<int, int>::iterator it;
	for(it = e[cur].begin(); it != e[cur].end(); ++ it) {
		int to = it->first;
		int ww = it->second;
		if(!vis[to]) {
			tarjan(to, w + ww);
			unit(cur, to);
		}
	}
	for(int i = 0; i < query[cur].size(); ++ i) {
		int to = query[cur][i];
		if(vis[to]) {
			answer[num[cur][i]] = dist[cur] + dist[to] - 2 * dist[find(to)];
		}
	} 
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
			f[i] = i;
			dist[i] = 0;
			vis[i] = false;
			num[i].clear();
			query[i].clear();
		}
		while(-- n) {
			int i, j, w;
			cin >> i >> j >> w;
			e[i][j] = w;
			e[j][i] = w;
		}
		for(int i = 0; i < m; ++ i){
			int a, b;
			cin >> a >> b;
			num[a].push_back(i);
			num[b].push_back(i);
			query[a].push_back(b);
			query[b].push_back(a);
		}
		tarjan(1, 0);
		for(int i = 0; i < m; ++ i) {
			cout << answer[i] << endl;
		}
	}
	return 0;
}