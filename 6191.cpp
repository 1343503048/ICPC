
/***********************************************************
   
        FileName：6191.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-04 14:47:35
    Descripttion：可持久化trie树
   
*************************************************************/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;

#define debug printf("%s %d\n", __FUNCTION__, __LINE__);

struct Edge{
    int to, next;
};

Edge e[N<<1];

int ret[N*100][2];
int sz[N*100];
int id[N];
int tot, cnt, dfs_clock;
int head[N];
int val[N];
int l[N], r[N];
int rt[N];

inline void addEdge(int u, int v) {
    e[++tot] = Edge{v, head[u]};
    head[u] = tot;
}

void insert(int u, int v, int x) {
    for(int i = 30; i >= 0; -- i) {
        int c = (x>>i)&1;
        if(!ret[u][c]) {
            ret[u][c] = ++cnt;
            ret[u][c^1] = ret[v][c^1];
        }
        u = ret[u][c];
        v = ret[v][c];
        sz[u] = sz[v] + 1;
    }
}

void dfs(int u) {
    rt[u] = ++cnt;
    l[u] = ++dfs_clock;
    id[dfs_clock] = u;
    
    insert(rt[u], rt[id[dfs_clock-1]], val[u]);

    for(int i = head[u]; i; i = e[i].next) {
        dfs(e[i].to);
    }
    r[u] = dfs_clock;
}

int query(int u, int x) {
    int res = 0;
    int a = rt[id[l[u]-1]], b = rt[id[r[u]]];
    for(int i = 30; i >= 0; -- i) {
        int c = (x>>i)&1;
        int l = ret[a][c^1];
        int r = ret[b][c^1];
        if(sz[r]-sz[l]) {
            res |= (1<<i);
            a = l;
            b = r;
        }
        else {
            a = ret[a][c];
            b = ret[b][c];
        }
    }
    return res;
}

int main() {
    int n, q;
    while(~scanf("%d%d", &n, &q)) {
        tot = cnt = dfs_clock = 0;
        memset(head, 0, sizeof(head));
        memset(ret, 0, sizeof(ret));
        memset(sz, 0, sizeof(sz));
         
        for(int i = 1; i <= n; ++ i) {
            scanf("%d", &val[i]);
        }

        for(int i = 2; i <= n; ++ i) {
            int x;
            scanf("%d", &x);
            addEdge(x, i);
        }
            
        dfs(1);

        while(q --) {
            int u, x;
            scanf("%d%d", &u, &x);
            printf("%d\n", query(u, x));
        }
    }
    return 0;
}
