//最大流问题
//EK算法
#include <bits/stdc++.h>
using namespace std;
const int MAX = 15+5;

int pre[MAX], c[MAX][MAX], flow[MAX];
bool vis[MAX];

int bfs(int s, int t, int &f){			//寻找增广路
	memset(pre, -1, sizeof(pre));
	memset(vis, false, sizeof(vis));
	queue<int> Q;
	Q.push(s);
	vis[s] = true;
	while(!Q.empty()){
		int v = Q.front(); 
		Q.pop();
		for(int i = 1; i <= t; ++ i) {
			if(!vis[i] && c[v][i] > 0){
				Q.push(i);
				vis[i] = true;
				pre[i] = v;
				f = min(f, c[v][i]);
				if(i == t){
					return f;
				}
			}
		}
	}
	return 0;
}

int EK(int s, int t){
	int ans = 0, f = INT_MAX;
	while(bfs(s, t, f)){
		int v = t;
		do{
			c[v][pre[v]] += f;
			c[pre[v]][v] -= f;
			v = pre[v];
		}while(v != s);
		ans += f;
		f = INT_MAX;
	}
	return ans;
}

int main(){
	ifstream cin("data.in");
	int t, cnt = 1;
	cin >> t;
	while(t --) {
		memset(c, 0, sizeof(c));
		int n, m;
		cin >> n >> m;
		while(m --) {
			int x, y, w;
			cin >> x >> y >> w;
			c[x][y] += w;
		}
		cout << "Case " << cnt ++ << ": " << EK(1, n) << endl;
	}
	return 0;
}
