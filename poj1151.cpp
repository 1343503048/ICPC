/*************************************************

       Filename: poj1151.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-05-18 21:31:42
    Description: 扫描线

*************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 500;

struct Line{
    double x, y1, y2;
    int f;  
    bool operator < (const Line &l) const  {
        return x < l.x;
    }
};

struct Node {
    double lf, rf, v;
    int f;
};

Line l[N];
Node ret[N];
double y[N];

void build(int rt, int l, int r) {
    ret[rt] = Node{y[l], y[r], 0, 0};
    if(l + 1 == r) return ;
    int mid = (l + r) >> 1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid, r);
}

void pushUp(int rt, int l, int r) {
    if(ret[rt].f > 0) {
        ret[rt].v = ret[rt].rf-ret[rt].lf;
    }
    else if(l+1 == r) {
        ret[rt].v = 0;    // 叶子节点
    }
    else {
        ret[rt].v = ret[rt<<1].v + ret[rt<<1|1].v;
    }
}

void update(int rt, int l, int r, double a, double b, int f) {
    if(a <= ret[rt].lf && b >= ret[rt].rf) {
        ret[rt].f += f;
        pushUp(rt, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    if(b  <= ret[rt<<1].rf) {
        update(rt<<1, l, mid, a, b, f);
    }
    else if(a >= ret[rt<<1|1].lf) {
        update(rt<<1|1, mid, r, a, b, f);
    }
    else {
        update(rt<<1|1, mid, r, a, b, f);
        update(rt<<1, l, mid, a, b, f);
    }
    pushUp(rt, l, r);
}

int main() {
    int n, t = 1;
    while(scanf("%d", &n) && n) {
        int tot = 0;
        for(int i = 1; i <= n; ++ i) {
            double a, b, c, d;
            scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
            y[++tot] = b;
            l[tot] = Line{a, b, d, 1};
            y[++tot] = d;
            l[tot] = Line{c, b, d, -1};
        }
        sort(l+1, l+tot+1);
        sort(y+1, y+tot+1);
        build(1, 1, tot);
        update(1, 1, tot, l[1].y1, l[1].y2, l[1].f);
        double res = 0;
        for(int i = 2; i <= tot; ++ i) {
            res += ret[1].v * (l[i].x - l[i-1].x);
           update(1, 1, tot, l[i].y1, l[i].y2, l[i].f);
        } 
        printf("Test case #%d\nTotal explored area: %.2f\n\n", t++, res);
    }
    return 0;
}
