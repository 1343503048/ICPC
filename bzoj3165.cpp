
/***********************************************************
   
        FileName：bzoj3165.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-10-10 22:10:25
    Descripttion：李超线段树
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 4e4;
const int m1 = 39989;
const int m2 = 1e9;

struct Line{
    int id;
    double k, b;
    double getY(int x) {
        return k * x + b;
    }
};

Line l[N<<2];
int flag[N<<2]; 
Line v[N<<2];

inline double getCross(const Line &x, const Line &y) {
    return (y.b-x.b)/(x.k-y.k);
}

inline double getY(const Line &a, int x) {
    return a.k * x + a.b;
}

void update(int rt, int l, int r, const Line &li) {
    if(!flag[rt]) {
        v[rt] = li;
        flag[rt] = 1;
        return ;
    }
    double l1 = v[rt].getY(l), l2 = getY(li, l);
    double r1 = v[rt].getY(r), r2 = getY(li, r);
    if(l1 < l2 && r1 < r2) {
        v[rt] = li;
    }
    else if(l1 > l2 && r1 > r2) {
        return ;
    }
    else {
        double x = getCross(v[rt], li);
        int mid = (l + r) >> 1;
        if(l1 > l2) {
            if(x <= mid) {
                update(rt<<1, l, mid, v[rt]);
                v[rt] = li;    
            }
            else {
                update(rt<<1|1, mid+1, r, li);
            }
        }
        else {
            if(x <= mid) {
                update(rt<<1, l, mid, li);
            }
            else {
                update(rt<<1|1, mid+1, r, v[rt]);
                v[rt] = li;
            }
        }
    }
}

void insert(int rt, int l, int r, int a, int b, const Line &li) {
    if(a <= l && r <= b) {
        update(rt, l, r, li);
        return ;
    }
    int mid = (l + r) >> 1;
    if(a <= mid) {
        insert(rt<<1, l, mid, a, b, li);
    }
    if(b > mid) {
        insert(rt<<1|1, mid+1, r, a, b, li);
    }
}


Line res;

void query(int rt, int l, int r, int x) {
    if(flag[rt]) {
        if(v[rt].getY(x)==res.getY(x)&&res.id > v[rt].id) {
            res = v[rt];
        }
        else if(v[rt].getY(x)>res.getY(x)) {
            res = v[rt];
        }
    }
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(x <= mid) {
        query(rt<<1, l, mid, x);
    }
    else {
        query(rt<<1|1, mid+1, r, x);
    }
}

int main() {
    int lastans = 0;
    int n;
    int id = 1;
    scanf("%d", &n);
    while(n --) {
        int op;
        scanf("%d", &op);
        if(op==0) {
            int k;
            scanf("%d", &k);
            int x = ((k+lastans-1)%m1+1);
            res = Line{0, 0, 0};
            query(1, 1, m1, x);
            printf("%d\n", res.id);   
            lastans = res.id;
        }
        else {
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            x0 = ((x0+lastans-1)%m1+1);
            x1 = ((x1+lastans-1)%m1+1);
            y0 = ((y0+lastans-1)%m2+1);
            y1 = ((y1+lastans-1)%m2+1); 
            if(x0>x1)swap(x0, x1), swap(y0, y1);
            double k, b;
            if(x0==x1) {
                k = 0;
                b = max(y0, y1);
            }
            else {
                k = (y0-y1)*1.0/(x0-x1);
                b = y0 * 1.0 - k * x0;
            }
            l[id] = Line{id, k, b};
            insert(1, 1, m1, x0, x1, l[id]);
            id ++;
        } 
    }
    return 0;
}
