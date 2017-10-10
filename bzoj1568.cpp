
/***********************************************************
   
        FileName：bzoj1568.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-10-10 20:16:02
    Descripttion：李超线段树
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

// 插入多条射线，询问在与直线x=x0相交的交点中的最值

#include <bits/stdc++.h>
using namespace std;
const int N = 50000;

double getCrossX(double k1, double b1, double k2, double b2) {
    return (b2-b1)/(k1-k2);
}

double ki[N<<2], bi[N<<2];
bool flag[N<<2];  // 该区间是否存在线段覆盖

void update(int rt, int l, int r, double k, double b) {
    if(!flag[rt]) {
        ki[rt] = k;
        bi[rt] = b;
        flag[rt] = 1;
    }
    else {
        double l1 = ki[rt] * l + bi[rt], r1 = ki[rt]*r+bi[rt];
        double l2 = k * l + b, r2 = k * r + b;
        int mid = (l + r) >> 1;
        if(l1 >= l2 && r1 >= r2) return ;  // 不更新
        else if(l1 <= l2 && r1 <= r2) {   // 整个区间更新
            ki[rt] = k;
            bi[rt] = b;
        }
        else if(l1 < l2) {
            double x = getCrossX(ki[rt], bi[rt], k, b);
            // 有交点 -> 比较谁更优势，把不优势的下放到交点所在儿子区间上
            if(x <= mid) {
                update(rt<<1, l, mid, k, b); 
            }
            else {
                update(rt<<1|1, mid+1, r, ki[rt], bi[rt]);
                ki[rt] = k;
                bi[rt] = b;
            }
        }
        else {
            double x = getCrossX(ki[rt], bi[rt], k, b);
            if(x <= mid) {
                update(rt<<1, l, mid, ki[rt], bi[rt]);
                ki[rt] = k;
                bi[rt] = b;
            }
            else {
                update(rt<<1|1, mid+1, r, k, b);
            }
        }
    }
}

double res;
void query(int rt, int l, int r, int x) {
    if(flag[rt]) res = max(res, ki[rt]*x+bi[rt]);
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(x <= mid) query(rt<<1, l, mid, x);
    else query(rt<<1|1, mid+1, r, x);
}

int main() {
    int n;
    scanf("%d", &n);
    while(n --) {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'P') {
            double k, b;
            scanf("%lf%lf", &b, &k);
            update(1, 1, N, k, b-k); 
        }
        else {
            res = 0;
            int t;
            scanf("%d", &t);
            query(1, 1, N, t);
            printf("%lld\n", (long long) res/100);
        }
    }
    return 0;
}
