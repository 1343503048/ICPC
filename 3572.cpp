//dinic
#include <bits/stdc++.h>
using namespace std;
const int N = 1000+5;
const int M = 500000+2000;

struct Edge{
	int from, to,  c, next;
	Edge(){}
	Edge(int _from, int _to, int _c, int _next) : from(_from),
												to(_to), c(_c), next(_next){}
};

Edge e[M];
int vis[N], head[N], dist[N], cur[N];

void addEdge(int from, int to, int c, int &k) {
	e[k] = Edge(from, to, c, head[from]);
	head[from] = k ++;
	e[k] = Edge(to, from, 0, head[to]);
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
	//freopen("data.in", "r", stdin);
	int t, cnt = 1;
	scanf("%d", &t);
	while(t --) {
		int n, m;
		memset(head, -1, sizeof(head));
		scanf("%d%d", &n, &m);
		int k = 0, p = 0;
		for(int i = 1; i <= n; ++ i) {
			int c, x, y;
			scanf("%d%d%d", &c, &x, &y);
			p += c;
			addEdge(0, i, c, k);
			for(int j = x; j <= y; ++ j) {
				addEdge(i, j + 500, 1, k);
			}
		}
		for(int i = 501; i < 1001; ++ i) {
			addEdge(i, 1001, m, k);
		}
		if(dinic(0, 1001) == p) {
			printf("Case %d: Yes\n\n", cnt++);
		}
		else {
			printf("Case %d: No\n\n", cnt++);
		}
	}
	return 0;
}
