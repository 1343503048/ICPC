
/***********************************************************
   
        FileName：spojGss3.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-24 01:48:48
    Descripttion：c/c++ file
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);
#include <bits/stdc++.h>
using namespace std;
const int N = 505000;
#define ls rt<<1
#define rs rt<<1|1

int fi() {
    register char c = 0;
    register int a = 0;
    int neg = 1;
    while(c < 33) c= getchar();
    while(c > 33) {
        if(c == '-') neg = -1;
        else a = a * 10 + c - '0';
        c = getchar();
    }
    return a * neg;
}

struct Node{
    int vl; // 左起最大和
    int vm; // 区间最大和
    int vr; // 右起最大和 
    int va; // 整段和
};

Node ret[N<<2];

void merge(const Node &x, const Node &y, Node &tmp) {
    tmp.va = x.va + y.va;
    tmp.vl = max(x.vl, x.va+y.vl);
    tmp.vm = max(max(x.vm, y.vm), x.vr+y.vl);
    tmp.vr = max(y.vr, x.vr+y.va);
}

void build(int rt, int l, int r) {
    if(l == r) {
        int x = fi();
        ret[rt] = Node{x, x, x, x};
        return ;
    }
    int mid = (l + r) >> 1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    merge(ret[rt<<1], ret[rt<<1|1], ret[rt]);
}

Node query(int rt, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return ret[rt];
    }
    int mid = (l + r) >> 1;
    if(b <= mid) {
        return query(rt<<1, l, mid, a, b);
    }
    else if(a > mid) {
        return query(rt<<1|1, mid+1, r, a, b);
    }
    else {
        Node x = query(rt<<1, l, mid, a, b);
        Node y = query(rt<<1|1, mid+1, r, a, b);
        Node res;
        merge(x, y, res);
        return res;
    }
}

void update(int rt, int l, int r, int x, int y) {
    if(l == r) {
        ret[rt] = Node{y, y, y, y};
        return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) {
        update(rt<<1, l, mid, x, y);
    }
    else {
        update(rt<<1|1, mid+1, r, x, y);
    }
    merge(ret[rt<<1], ret[rt<<1|1], ret[rt]);
}

int main() {
    int n = fi();
    // scanf("%d", &n);
       // scanf("%d", &a[i]);
    build(1, 1, n);
//    scanf("%d", &q);
    int q = fi();
    while(q --) {
        int k = fi(), l = fi(), r = fi();
        if(l > r) swap(l, r);
       // scanf("%d%d%d", &k, &l, &r);
        if(k == 0) {
            update(1, 1, n, l, r);
        }
        else {
            printf("%d\n", query(1, 1, n, l, r).vm);
        }
    }
    return 0;
}
