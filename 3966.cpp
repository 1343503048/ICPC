//#pragma comment(linker, "/STACK:1024000000, 1024000000")
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 50000+10;

int num[N], siz[N]; //保存子树节点个数
int top[N], son[N];	//用来保存当前节所在链的顶端节点和重儿子
int dep[N];			//保存当前节点深度
int tid[N];			//保存树中每个节点剖分后的新编号
int Rank[N];		//节点在线段树中的位置
int fa[N];			//父节点
int head[N], to[N<<1], Next[N<<1], edge;
int n, m, Q;
int tim;

void init() {
	memset(head, -1, sizeof(head));
	memset(son, -1, sizeof(son));
	tim = 0;
	edge = 0;
}

void addEdge(int u, int v) {
	to[edge] = v, Next[edge] = head[u], head[u] = edge++;
	to[edge] = u, Next[edge] = head[v], head[v] = edge++;
}

//树链剖分
//dfs1(1, 0, 0)
void dfs1(int u, int f, int d) {
	dep[u] = d;
	fa[u] = f;
	siz[u] = 1;
	for(int i = head[u]; i != -1; i = Next[i]) {
		int v = to[i];
		if(v != f) {
			dfs1(v, u, d+1);
			siz[u] += siz[v];
			if(son[u] == -1 || siz[v] > siz[son[u]]) {//重边
				son[u] = v;
			}
		}
	}
}

//dfs2(1, 1)
void dfs2(int u, int tp) {
	top[u] = tp;
	tid[u] = ++ tim;		//给每个节点都编号
	Rank[tid[u]] = u;		//位置tim上为u, u 与 tim相互映射
	if(son[u] == -1) {	//到达叶子节点
		return ;
	}
	dfs2(son[u], tp);		//重边
	for(int i = head[u]; i != -1; i = Next[i]) {
		int v = to[i];
		if(v != son[u] && v != fa[u]) {
			dfs2(v, v);
		}
	}
}

int sum[N<<2], col[N<<2];

void pushUp(int root) {
	sum[root] = sum[root<<1] + sum[root<<1|1];
}

void pushDown(int root, int m) {
	if(col[root]) {
		col[root<<1] += col[root];
		col[root<<1|1] += col[root];
		sum[root<<1] += (m-(m>>1)) * col[root];
		sum[root<<1|1] += (m>>1)*col[root];
		col[root] = 0;
	}
}

void build(int l, int r, int root) {
	col[root] = 0;
	if(l == r) {
		sum[root] = num[Rank[l]];
		return ;
	}
	int m = (l+r) >> 1;
	build(l, m, root<<1);
	build(m+1, r, root<<1|1);
	pushUp(root);
}

void update(int L, int R, int v, int l, int r, int root) {
	if(L <= l && R >= r) {
		col[root] += v;
		sum[root] += v * (r-l+1);
		return ;
	}
	pushDown(root, r-l+1);
	int m = (l+r) >> 1;
	if(L <= m) {
		update(L, R, v, l, m, root<<1);
	}
	if(R > m) {
		update(L, R, v, m+1, r, root<<1|1);
	}
	pushUp(root);
}

int query(int l, int r, int root, int val) {
	if(l == r) {
		return sum[root];
	}
	pushDown(root, r-l+1);
	int m = (l+r) >> 1;
	int ret = 0;
	if(val <= m) {
		ret = query(l, m, root<<1, val);
	}
	else {
		ret = query(m+1, r, root<<1|1, val);
	}
	pushUp(root);
	return ret;
}

void change(int x, int y, int val) {
	while (top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) {
			swap(x, y);
		}
		update(tid[top[x]], tid[x], val, 1, n, 1);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) {
		swap(x, y);
	}
	update(tid[x], tid[y], val, 1, n, 1);
}

int main(int argc, char const *argv[]) {
	char oper[5];
	int a, b, c;
	while(~scanf("%d%d%d", &n, &m, &Q)) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", num+i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(a, b);
		}
		dfs1(1, 0, 0);
		dfs2(1, 1);
		build(1, n, 1);
		while(Q --) {
			scanf("%s", oper);
			if(oper[0] == 'Q') {
				scanf("%d", &a);
				printf("%d\n", query(1, n, 1, tid[a]));
			}
			else {
				scanf("%d%d%d", &a, &b, &c);
				if(oper[0] == 'D') {
					c = -c;
				}
				change(a, b, c);
			}
		}
	}
	return 0;
}