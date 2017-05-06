
/*************************************************

       Filename: poj3177.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-05-06 22:19:06
    Description: poj3177.cpp

#*************************************************/
// 题意：对于题中的联通图，添加多少条边后对于任意两点至少有两条以上的路可以到达
// 思路：将缩点后的树的叶子节点两两链接，故至少要(叶子节点数+1)/2条边
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int N = 1e4+5;

struct Edge{
    int to, next;
};

Edge e[N<<1];
int head[N], low[N], dnf[N], id[N], degree[N];
bool vis[N];
int dfs_clock, flag;
stack<int> st;

void tarjan(int u, int fa) {
    st.push(u);
    vis[u] = true;
    dnf[u] = low[u] = dfs_clock ++;
    bool first = true;
    for(int i = head[u]; i != -1; i = e[i].next) {
	int to = e[i].to;
	if(first && to == fa) {
	    first = false;
	    continue;
	}
	if(dnf[to] == -1) {
	    tarjan(to, u);
	    low[u] = min(low[u], low[to]);
	}
	else if(vis[to]) {
	    low[u] = min(low[u], dnf[to]);
	}
    }
    if(low[u] == dnf[u]) {
	int j;
	flag ++;
	do {
	    j = st.top();
	    vis[j] = false;
	    st.pop();
	    id[j] = flag;
	}while(j != u);
    }
}

int main(void) {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
	memset(head, -1, sizeof(head));
	for(int i = 0; i < m; ++ i) {
	    int x, y;
	    scanf("%d%d", &x, &y);
	    e[i<<1] = Edge{y, head[x]}; 
	    head[x] = i<<1;
	    e[i<<1|1] = Edge{x, head[y]};
	    head[y] = i<<1|1;
	}
	dfs_clock = flag = 0;
	memset(dnf, -1, sizeof(dnf));
	memset(vis, false, sizeof(vis));
	memset(degree, 0, sizeof(degree));
	tarjan(1, -1);
	for(int i = 1; i <= n; ++ i) {
	    for(int j = head[i]; j != -1; j = e[j].next) {
		int from = id[i];
		int to = id[e[j].to];
		if(from != to) {
		    degree[to] ++;
		}
	    }
	}
	int ans = 0;
	for(int i = 1; i <= flag; ++ i) {
	    ans += (degree[i]==1);
	}
	printf("%d\n", (ans+1)>>1);
    }
    return 0;
}
