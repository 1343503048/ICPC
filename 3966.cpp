
/***********************************************************
   
        FileName：3966.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-07 16:34:56
    Descripttion：树链剖分+线段树
   
*************************************************************/

#include <bits/stdc++.h>
using namespace std;
const int N = 50000+5;

struct Edge{
    int to, next;
};

Edge e[N<<1];
int add[N<<2], v[N<<2];
int head[N];
int Rank[N];     // rank[i]代表编号为i的节点所对应的原始节点
int tid[N];      // tid[i]代表节点i的编号
int dep[N], f[N];
int sz[N];       // 子节点的数量
int son[N], tp[N];
int cnt[N];
int tot, id;

void init() {
    tot = id = 0;
    memset(head, 0, sizeof(head));
    memset(son, -1, sizeof(son));
    dep[1] = 0;
}

void addEdge(int u, int v) {
    e[++tot] = Edge{v, head[u]};
    head[u] = tot;
    e[++tot] = Edge{u, head[v]};
    head[v] = tot;
}

// 树链剖分部分
void dfs1(int u) {
    sz[u] = 1;
    for(int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == f[u]) continue;
        f[to] = u;
        dep[to] = dep[u] + 1;
        dfs1(to);
        sz[u] += sz[to];
        if(son[u] == -1 || sz[son[u]] < sz[to]) {
            son[u] = to;
        }
    }
}

void dfs2(int u, int top) {
    tp[u] = top;
    tid[u] = ++ id; 
    Rank[id] = u; 
    if(son[u] == -1) {
        return ;
    }
    dfs2(son[u], top);   // 重边
    for(int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == f[u] || to == son[u]) continue;
        dfs2(to, to);
    }
}

// 线段树维护
void ctag(int rt, int x) {
    v[rt] += x;
    add[rt] += x;
}

void pushDown(int rt) {
    if(add[rt] != 0) {
        ctag(rt<<1, add[rt]);
        ctag(rt<<1|1, add[rt]);
        add[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    add[rt] = 0;
    v[rt] = 0;
    if(l == r) {
        v[rt] = cnt[Rank[l]];
        return ;
    }
    int mid = (l + r) >> 1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
}

void update(int rt, int l, int r, int a, int b, int x) {
    if(a <= l && r <= b) {
        v[rt] += x;
        add[rt] += x;
        return ;
    }
    pushDown(rt);
    int mid = (l + r) >> 1;
    if(a <= mid) {
        update(rt<<1, l, mid, a, b, x);
    }
    if(b > mid) {
        update(rt<<1|1, mid+1, r, a, b, x);
    }
}

int query(int rt, int l, int r, int pos) {
    if(l == r) {
        return v[rt];
    }  
    pushDown(rt);
    int mid = (l + r) >> 1;
    if(pos <= mid) {
        return query(rt<<1, l, mid, pos);
    }
    else {
        return query(rt<<1|1, mid+1, r, pos);
    }
}

void change(int n, int a, int b, int x) {
    while(tp[a] != tp[b]) {
        if(dep[tp[a]] > dep[tp[b]]) {
            swap(a, b);
        }
         
        update(1, 1, n, tid[tp[b]], tid[b], x);
        b = f[tp[b]];
    }
    if(dep[a] > dep[b]) {
        swap(a, b);
    }
    update(1, 1, n, tid[a], tid[b], x);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, p;
    while(cin >> n >> m >> p) {
        init();
        for(int i = 1; i <= n; ++ i) {
            cin >> cnt[i];
        }
        
        for(int i = 0; i < m; ++ i) {
            int x, y;
            cin >> x >> y;
            addEdge(x, y);
        }

        dfs1(1);
        dfs2(1, 1);

        build(1, 1, n);
        while(p --) {
            char op[5];
            cin >> op;
            if(op[0] == 'Q') {
                int a;
                cin >> a;
                cout << query(1, 1, n, tid[a]) << "\n";
            }
            else {
                int a, b, c;
                cin >> a >> b >> c;
                if(op[0] == 'D') {
                    c = -c; 
                }
                change(n, a, b, c);
            }
        }
    }
    return 0;
}
