#include <cstdio>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 100000+5;

struct Edge {
	int from, to, w, next;
};

Edge e[N<<1];
//dist代表当前点到root的距离
int head[N], dist[N], id[N], depth[N<<1], vis[N<<1], dp[N<<1][30];
int eNum, t;

void addEdge(int from, int to, int w) {
	e[eNum].to = to;
	e[eNum].w = w;
	e[eNum].next = head[from];
	head[from] = eNum ++;
}

void dfs(int u, int fa, int deep) {
	id[u] = t;	//标记第一次遍历到u点时的时间点
	depth[t] = deep;	
	vis[t++] = u;
	for(int i = head[u]; i != -1; i = e[i].next) {
		int to = e[i].to;
		if(to != fa) {
			dist[to] = dist[u] + e[i].w;
			dfs(to, u, deep + 1);
			depth[t] = deep;
			vis[t++] = u;
		}
	}
}

void st() {
	for(int i = 1; i < t; ++ i) {
		dp[i][0] = i;
	}
	for (int i = 1; (1<<i) < t; ++i) {
		for(int j = 1; j + (1<<i) - 1 < t; ++ j) {		//确保能分成两端
			int a = dp[j][i-1];
			int b = dp[j+(1<<(i-1))][i-1];
			if(depth[a] < depth[b]) {
				dp[j][i] = a;
			}
			else {
				dp[j][i] = b;	
			}
		}
	}
}

int query(int l, int r) {
	int k = log(r-l+1)/log(2); 		//!!1
	int a = dp[l][k];
	int b = dp[r-(1<<k)+1][k];
	return depth[a] < depth[b] ? a : b;
}

int lca(int u, int v) {		//找最近的公共祖先
	int x = id[u];
	int y = id[v];
	if(x < y) {
		return vis[query(x, y)];
	}
	else {
		return vis[query(y, x)];
	}
}

int main() {
	int n, m;
	// freopen("data.in", "r", stdin);
	while(~scanf("%d%d", &n, &m)) {
		memset(head, -1, sizeof(head));
		char op[5];
		int u, v, w, k;
		dist[1] = eNum = 0;	
		t = 1;
		for(int i = 0; i < m; ++ i) {
			scanf("%d%d%d%s", &u, &v, &w, op);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}
		dfs(1, -1, 0);
		st();
		scanf("%d", &k);
		while(k --) {
			scanf("%d%d", &u, &v);
			printf("%d\n", dist[u] + dist[v] - 2 * dist[lca(u, v)]);		
		}
	}
	return 0;
}