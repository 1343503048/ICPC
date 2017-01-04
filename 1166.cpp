#include <bits/stdc++.h>
using namespace std;
const int MAX = 50000+5;

struct {
    int l, r, v;
};

Node segTree[4*MAX];
int data[MAX];

void creat(int root, int l, int r) {
    segTree[root].l = l;
    segTree[root].r = r;
    if(l == r) {
        segTree[root].v = data[l];
    }
    else {
        int mid = (l + r) >> 1;
        creat(2*root, l, mid);
        creat(2*root+1, mid+1, r);
        segTree[root].v = segTree[2*root].v + segTree[2*root+1].v;
    }
}

void update(int root, int x, int _v) {
    int l = segTree[root].l;
    int r = segTree[root].r;
    if(l == r) {
        segTree[root].v += _v;
    }
    else {
        int mid = (l + r) >> 1;
        if(x <= mid) {
            update(2*root, x, _v);
        }
        else {
            update(2*root+1, x, _v);
        }
        segTree[root].v = segTree[2*root].v + segTree[2*root+1].v;
    }
}

int query(int root, int l, int r) {
    if(segTree[root].l >= l && segTree[root].r <= r) {
        return segTree[root].v;
    }
    else {
        int q1 = 0, q2 = 0;
        if(r <= segTree[2*root].r) {
            q1 = query(2*root, l, r);
        }
        else if(l >= segTree[2*root+1].l) { 
            q2 = query(2*root+1, l, r);
        }
        else {
            q1 = query(2*root, l, r);
            q2 = query(2*root+1, l, r);
        }
        return q1 + q2;
    }
}

int main(){
    int t, cnt = 1;
    scanf("%d", &t);
    while(t -- ) {
        printf("Case %d:\n", cnt ++);
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", &data[i]);
        }
        creat(1, 1, n);
        char ch[10];
        while(~scanf("%s", ch) && ch[0] != 'E') {
            if(ch[0] == 'Q') {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%d\n", query(1, l, r));
            }
            else if(ch[0] == 'A') {
                int x, v;
                scanf("%d%d", &x, &v);
                update(1, x, v);
            }
            else if(ch[0] == 'S') {
                int x, v;
                scanf("%d%d", &x, &v);
                update(1, x, -v);
            }
        }
    }
    return 0;
}