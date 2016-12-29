//dinic
//缩点
#include <bits/stdc++.h>
using namespace std;
const int N = 2000+50;
const int M = 300000+5000;

struct Edge{
	int to,  c, next;
	Edge(){}
	Edge(int _to, int _c, int _next) : to(_to), c(_c), next(_next){}
};

Edge e[M];
int vis[N], head[N], dist[N], cur[N];
int f[N];

void addEdge(int from, int to, int c, int &k) {
	e[k] = Edge(to, c, head[from]);
	head[from] = k ++;
	e[k] = Edge(from, 0, head[to]);
	head[to] = k ++;
}

bool bfs(int s, int t) {
	queue<int> Q;
	memset(dist, -1, sizeof(dist));
	memset(vis, false, sizeof(vis));
	vis[s] = true;
	dist[s] = 0;
	Q.push(s);
	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for(int i = head[v]; i != -1; i = e[i].next) {
			if(!vis[e[i].to] && e[i].c > 0) {
				dist[e[i].to] = dist[v] + 1;
				if(e[i].to == t) {
					return true;
				}
				vis[e[i].to] = true;
				Q.push(e[i].to);
			}
		}
	}
	return false;
}

int dfs(int s, int t, int f) {
	if(s == t || f == 0) {
		return f;
	}
	int ans = 0, x;
	for(int &i = cur[s]; i != -1; i = e[i].next) {			//引用优化
		if(dist[e[i].to] == dist[s] + 1 && (x = dfs(e[i].to, t, min(f, e[i].c))) > 0) {
			e[i].c -= x;
			e[i^1].c += x;
			ans += x;
			f -= x;
			if(f == 0) {
				break;
			}
		}
	}
	return ans;
}

int dinic(int s, int t) {
	int ans = 0;
	while(bfs(s, t)) {
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, t, INT_MAX);
	}
	return ans;
}

int main(){
	freopen("data.in", "r", stdin);
	int n, m;
	while(~scanf("%d%d", &n, &m)) {
		memset(head, -1, sizeof(head));
		memset(f, 0, sizeof(f));
		int k = 0, x, num = 0, top = 1, t;
		for(int i = 1; i <= n; ++ i) {
			x = 0;
			for(int j = 1; j <= m; ++ j) {
				int temp;
				scanf("%d", &temp);
				x = x * 2 + temp;
			}
			f[x] ++;
		}
		for(int i = 1; i < N; ++ i) {
			num += (f[i] != 0);
		}
		for(int i = 1; i < N; ++ i) {
			if(f[i] > 0) {
				addEdge(0, top ++, f[i], k);
				int x = i;
				int y = m;
				while(x) {
					if(x & 1) {
						addEdge(top-1, num+y, INT_MAX, k);
					}
					y --;
					x /= 2;
				}
			}
		}
		int temp;
		t = m + num + 1;
		for(int i = 1+num; i < t; ++ i) {	
			scanf("%d", &temp);
			addEdge(i, t, temp, k);
		}
		if(dinic(0, t) == n) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}
