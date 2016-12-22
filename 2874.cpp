//Accepted
//Exe.Time	Exe.Memory
// 2874	     1716MS	
#include <vector>
#include <cstdio>
#include <map>
using namespace std;

const int MAX = 10000+10;
const int MAXQ = 1000000+10;

struct Edge{
	int to, w, next;
};

struct Query{
	int to, w, next;
};

Edge e[2*MAX];
Query query[2*MAXQ];

int vis[MAX], dist[MAX], f[MAX];
int headE[MAX], headQ[MAX];

void addEdge(int from, int to, int w, int &k) {
	e[k].to = to;
	e[k].w = w;
	e[k].next = headE[from];
	headE[from] = k ++;
}

void addQuery(int from, int to, int &k) {
	query[k].to = to;
	query[k].w = -1;
	query[k].next = headQ[from];
	headQ[from] = k ++;
}

int find(int x) {
	if(f[x] != x) {
		f[x] = find(f[x]);
	}
	return f[x];
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x != y) {
		f[y] = x;
	}
}

void tarjan(int v, int flag) {
	vis[v] = flag;
	for(int i = headE[v]; i != -1; i = e[i].next) {
		int to = e[i].to;
		if(!vis[to]) {
			dist[to] = dist[v] + e[i].w;
			tarjan(to, flag);
			merge(v, to);
		}
	}
	for(int i = headQ[v]; i != -1; i = query[i].next) {
		int to = query[i].to;
		if(vis[to] == flag) {
			query[i^1].w = query[i].w = dist[to] + dist[v] - 2 * dist[find(to)];
		}
	}
}

int main() {
	//freopen("data.in", "r", stdin);
	int n, m, k;
	while(~scanf("%d%d%d", &n, &m, &k)) {
		for(int i = 1; i <= n; ++ i) {
			f[i] = i;
			dist[i] = vis[i] = 0;
			headE[i]= -1;
			headQ[i] = -1;
		}
		int cnt = 0;
		while(m --) {
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			addEdge(a, b, w, cnt);
			addEdge(b, a, w, cnt);
		}
		cnt = 0;
		for(int i = 0; i < k; ++ i) {
			int a, b;
			scanf("%d%d", &a, &b);
			addQuery(a, b, cnt);
			addQuery(b, a, cnt);
		}
		int flag = 1;
		for(int i = 1; i <= n; ++ i) {
			if(!vis[i]) {
				tarjan(i, flag);
				++ flag;
			}
		}
		for(int i = 0; i < k; ++ i) {
			int f = i * 2;
			if(query[f].w >= 0) {
				printf("%d\n", query[f].w);
			}
			else {
				puts("Not connected");
			}
		}
	}
	return 0;
}