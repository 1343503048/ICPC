
/***********************************************************
   
        FileName：bzoj2152.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-10-08 17:03:37
    Descripttion：点分治
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 2e4+5;

struct Edge{
    int to, w, next;
};

Edge e[N<<1];
int head[N];
int tot;

void addEdge(int u, int v, int w) {
    e[++tot] = Edge{u, w, head[v]};
    head[v] = tot;
    e[++tot] = Edge{v, w, head[u]};
    head[u] = tot;
}

int gcd(int a, int b) {
    if(b) return gcd(b, a%b);
    return a;
}

bool vis[N];
int sz[N], mx[N];
int rt;
int res, sum;
int dis[N];

void getRoot(int u , int fa) {
    sz[u] = 1;
    mx[u] = 0;
    for(int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if(vis[to] || to == fa) continue;
        getRoot(to, u);
        sz[u] += sz[to];
        mx[u] = max(mx[u], sz[to]);
    }
    mx[u] = max(mx[u], sum-sz[u]);
    if(mx[u] < mx[rt]) rt = u;
}

int c[10];
void getDis(int u, int fa) {
    c[dis[u]] ++;
    for(int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa || vis[to]) continue;
        dis[to] = (dis[u] + e[i].w) % 3;
        getDis(to, u);
    }
}

int calu(int u, int di) {
    int res = 0;
    c[0] = c[1] = c[2] = 0;
    dis[u] = di % 3;
    getDis(u, 0);
    res += c[0] * c[0];
    res += c[1] * c[2] * 2;
    return res;
}

void dfs(int u) {
    res += calu(u, 0);
    vis[u] = true;
    for(int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if(!vis[to]) {
            res -= calu(to, e[i].w);
            rt = 0;
            sum = sz[to];
            getRoot(to, 0);
            dfs(rt);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i < n; ++ i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        addEdge(x, y, w);
    }
    mx[0] = N;
    sum = n;
    rt = 0;
    getRoot(1, 0);
    dfs(rt);
    int d = gcd(n*n, res);
    printf("%d/%d\n", res/d, n*n/d);
    return 0;
}
