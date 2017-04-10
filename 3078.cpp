#include <bits/stdc++.h>
using namespace std;
const int MAXN = 80000+5;
const int MAXQ = 30000+5;

struct Edge {
    int to, next;
};

struct Query {
    int from, to, lca, next, dist;
};

Edge e[MAXN<<1];
Query query[MAXN<<1];
int v[MAXN];

int pre[MAXN];
int data[MAXN], f[MAXN], headE[MAXN], headQ[MAXN], dist[MAXN];
bool vis[MAXN];

void addEdge(int from, int to, int &k) {
    e[k].to = to;
    e[k].next = headE[from];
    headE[from] = k ++;
}

void addQuery(int from, int to, int &k, int ans) {
    query[k].from = from;
    query[k].to = to;
    query[k].next = headQ[from];
    query[k].dist = ans;
    headQ[from] = k ++;
}

int find(int x) {
    if(f[x] != x) {
        f[x] = find(f[x]);
    }
    return f[x];
}

void unit(int x, int y) {
    x = find(x);
    y = find(y);
    if(x != y) {
	f[y] = x;
    }
}

// tanjar 求最近公共节点
void tarjan(int v) {
    vis[v] = true;
    for(int i = headE[v]; i != -1; i = e[i].next)  {
	int to = e[i].to;
        if(!vis[to]){
            dist[to] = dist[v] + 1;
	    pre[to] = v;
            tarjan(to);
            unit(v, to);
        }
    }
    for(int i = headQ[v]; i != -1; i = query[i].next) {
        if(vis[query[i].to]) {
            query[i].lca = query[i^1].lca = find(query[i].to);
        }
    }
}

// 将路径上的节点权值排序找第k大
int calu(int to, int from, int lca, int k) {
    int top = 0;
    while(to != lca) {
        v[top++] = data[to];
        to = pre[to];
    }
    while(from != lca) {
        v[top++] = data[from];
        from = pre[from];
    }
    v[top++] = data[lca];
    sort(v, v+top);
    // 第k大
    return v[top-k];
}

int main() {
    int n, q;
    while(~scanf("%d%d", &n, &q)) {
        for(int i = 1; i <= n; ++ i) {
            scanf("%d", &data[i]);
            pre[i] = f[i] = i;
        }
	memset(headE, -1, sizeof(headE));
	memset(headQ, -1, sizeof(headQ));
	memset(vis, false, sizeof(vis));
        int k = 0;
        for(int i = 1; i < n; ++ i) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge(x, y, k);
            addEdge(y, x, k);
        }
        k = 0;
        for(int i = 0; i < q; ++ i) {
            int ans, a, b;
            scanf("%d %d %d", &ans, &a, &b);
            if(ans == 0) {
                query[k+1].next = query[k].next = -2;
                query[k+1].to = query[k].to = a;
                query[k+1].dist = query[k].dist = b;
                k += 2;
            } 
            else {
                addQuery(a, b, k, ans);
                addQuery(b, a, k, ans);
            }
        }
        dist[1] = 1;
        tarjan(1);
        for(int i = 0; i < q; ++ i) {
            int f = i * 2;
            if(query[f].next == -2) {
                data[query[f].to] = query[f].dist;
            }
            else {
                int temp = dist[query[f].to] + dist[query[f].from] - 2 * dist[query[f].lca] + 1;
                if(temp < query[f].dist) {
                    puts("invalid request!");
                }
                else {
                    printf("%d\n", calu(query[f].to, query[f].from, query[f].lca, query[f].dist));
                }
            }
        }
    }
    return 0;
}
