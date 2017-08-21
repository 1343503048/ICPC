
/***********************************************************
   
        FileName：6141.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-18 10:28:53
    Descripttion：最小树形图
   
*************************************************************/

// 最小树形图,n的父节点满足最小字典序
// hdoj6141
#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
const int M = 10005;
#define debug printf("%s %d\n", __FUNCTION__, __LINE__);
struct Edge{
    int u, v, w;
};

Edge e[M];
int pre[N+5];
int vis[N+5];
int id[N+5];
int in[N+5];

int dstm(int rt, int m, int n) {
    int res = 0;
    while(1) {
        for(int i = 1; i <= n; ++ i) {
            in[i] = INT_MIN;
        }
        for(int i = 0; i < m; ++ i) {
            int x = e[i].u, y = e[i].v;
            if(x != y && y != rt && in[y] < e[i].w) {
                in[y] = e[i].w;
                pre[y] = x;
            }
        }    
        for(int i = 0; i < n; ++ i) {
            if(rt != i && in[i] == INT_MIN) {
                return 0;
            }
        }

        int flag = 0;
        in[rt] = 0;
        memset(vis, -1, sizeof(vis));
        memset(id, -1, sizeof(id));
        // 找出环
        pre[rt] = rt;
        for(int i = 1; i <= n; ++ i) {
            res += in[i];
            int u = i;
            while(vis[u] != i && id[u] == -1 && u != rt) {
                vis[u] = i;
                u = pre[u];
            }
                // 存在环一定会遍历回到i
            if(u != rt && id[u] == -1) {
                ++ flag;
                for(int v = pre[u]; v != u; v = pre[v]) {
                    id[v] = flag;
                }
                id[u] = flag;
            }
        }
        if(flag == 0) {
            break;  // 不存在环,找出最小树形图
        }
        for(int i = 1; i <= n; ++ i) {
            if(id[i] == -1) {
                id[i] = ++ flag;
            }
        }
        for(int i = 0; i < m; ++ i) {
            int to = e[i].v;
            e[i].u = id[e[i].u];
            e[i].v = id[e[i].v];
            if(e[i].u != e[i].v) {
                e[i].w -= in[to];
            }
        }
        n = flag;
        rt = id[rt];
    }
    return res;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t --) {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++ i) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            e[i].u = x;
            e[i].v = y;
            e[i].w = w * N;    // 将边权放大
            if(y == n) {
                e[i].w += n-x;   // 可能为负
            }
        }

        int res = dstm(0, m, n);

        printf("%d %d\n", res/N, n-res%N);
    }
    return 0;
}
