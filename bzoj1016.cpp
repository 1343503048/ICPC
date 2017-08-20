
/***********************************************************
   
        FileName：bzoj1016.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-20 20:43:25
    Descripttion：最小生成树计数
   
*************************************************************/

// 不同的最小生成树中,相同权值的边的数量是确定的

#include <bits/stdc++.h>
using namespace std;
const int mod = 31011;
const int N = 105;
const int M = 1005;

struct Edge{
    int u, v, w;
    bool operator < (const Edge &a) const {
        return w < a.w;
    }
};

map<int, int> c;
int sum;
int f[N];
Edge e[M];

// 不能路劲压缩
int find(int x) {
    if(f[x] != x) {
        return  find(f[x]);
    }
    return f[x];
}

void dfs(int v, int i, int k) {
    if(e[i].w != v) {
        if(c[v] == k) {
            sum ++;
        }
        return ;
    } 
    int x = find(e[i].u);
    int y = find(e[i].v);
    if(x != y) {   // 选择第i条边
        f[y] = x;
        dfs(v, i+1, k+1);
        f[y] = y;
        f[x] = x;
    }
    dfs(v, i+1, k);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++ i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        e[i] = Edge{x, y, w};
    }
    sort(e, e+m);
    for(int i = 1; i <= n; ++ i) {
        f[i] = i;
    }
    e[m].w = 0;
    int cnt = 0;
    for(int i = 0; i < m; ++ i) {
        int x = find(e[i].u);
        int y = find(e[i].v);
        if(x != y) {
            f[y] = x;
            c[e[i].w] ++;
            cnt ++ ;
        }
    }

    int res = 1;
    if(cnt != n-1) {
        puts("0");
        return 0;
    }
    for(int i = 1; i <= n; ++ i) {
        f[i] = i;
    }

    for(int i = 0; i < m; ++ i) {
        if(c[e[i].w]) {
            sum = 0;
            dfs(e[i].w, i, 0);
            res = res * sum % mod;
            c[e[i].w] = 0;
            for(int j = i; e[i].w == e[j].w; ++ j) {
                int x = find(e[j].u);
                int y = find(e[j].v);
                if(x != y) {
                    f[y] = x;
                }
            }
        }
    }

    printf("%d\n", res);
    return 0;
}
