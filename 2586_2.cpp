
/*************************************************

       Filename: 2586_2.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-07-25 09:24:20
    Description: 倍增法求+lca

*************************************************/

#include <bits/stdc++.h>
using namespace std;
const int N = 40000+5;

struct Edge{
    int to, w, next;
};

int p[N][15];
int dist[N];
int d[N];
int head[N];
int tot;
Edge e[N<<1];

void addEdge(int u, int v, int w) {
    e[tot] = Edge{v, w, head[u]};
    head[u] = tot ++;
    e[tot] = Edge{u, w, head[v]};
    head[v] = tot ++;
}

void dfs(int u, int fa) {
    for(int i = head[u]; ~i; i = e[i].next) {
	int to = e[i].to;
	int w = e[i].w;
	if(to == fa) continue;
	dist[to] = dist[u] + w;
	d[to] = d[u] + 1;
	p[to][0] = u;
	dfs(to, u);
    }
}

void init(int n) {
    for(int i = 1; i < 15; ++ i) {
	for(int j = 1; j <= n; ++ j) {
	    p[j][i] = p[p[j][i-1]][i-1];
	}
    }
}

int query(int a, int b) {
    if(d[a] > d[b]) swap(a, b);
    int f = d[b] - d[a];
    for(int i = 0; (1<<i) <= f; ++ i) {
	if((1<<i)&f) {
	    b = p[b][i];
	}
    }

    if(a != b) {
	for(int i = int(log2(N)); i >= 0; -- i) {
	    if(p[a][i] != p[b][i]) {
		a = p[a][i];
		b = p[b][i];
	    }
	}
	a = p[a][0];
    }
    return a;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t --) {
	int n, m;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	tot = 0;
	for(int i = 1; i < n; ++ i) {
	    int x, y, w;
	    scanf("%d%d%d", &x, &y, &w);
	    addEdge(x, y, w);
	}
	
	d[1] = dist[1] = 0;
	dfs(1, -1);
	init(n);

	while(m --) {
	    int x, y;
	    scanf("%d%d", &x, &y);
	    int lca = query(x, y);
	    int res = dist[x] + dist[y] - 2 * dist[lca];
	    printf("%d\n", res);
	}
    }
    return 0;
}
