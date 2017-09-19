
/***********************************************************
   
        FileName：spoj1811.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-19 21:14:43
    Descripttion：后缀自动机
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 500000;

struct State{
    int pre, go[26];
    int step;
};

int rt, last;
State ret[N];
int cur;

void init() {
    cur = 1;
    rt = last = cur ++;
}

void insert(int w) {
    int p = last;
    int np = cur ++;
    ret[np].step = ret[p].step + 1;
    while(p&&!ret[p].go[w]) {
        ret[p].go[w] = np;
        p = ret[p].pre;
    }
    if(p == 0) {
        ret[np].pre = rt;
    }
    else {
        int q = ret[p].go[w];
        if(ret[p].step+1 == ret[q].step) {
            ret[np].pre = q;
        }
        else {
            int nq = cur ++;
            memcpy(ret[nq].go, ret[q].go, sizeof(ret[q].go));
            ret[nq].step = ret[p].step + 1;
            ret[nq].pre = ret[q].pre;
            ret[q].pre = nq;
            ret[np].pre = nq;
            while(p&&ret[p].go[w] == q) {
                ret[p].go[w] = nq;
                p = ret[p].pre;
            }
        }
    }
    last = np;
}

char a[N];
int main() {
    scanf("%s", a);
    int n = strlen(a);
    init();
    for(int i = 0; i < n; ++ i) {
        insert(a[i]-'a');
    }
    scanf("%s", a);
    int m = strlen(a);
    int res = 0, len = 0;
    int p = rt;
    for(int i = 0; i < m; ++ i) {
        int x = a[i]-'a';
        if(ret[p].go[x]) {
            len ++;
            p = ret[p].go[x];
        } 
        else {
            while(p&&!ret[p].go[x]) p = ret[p].pre;
            if(!p) {
                p = rt;
                len = 0;
            }
            else {
                len = ret[p].step+1;
                p = ret[p].go[x];
            }
        }
        res = max(res, len);
    }
    printf("%d\n", res);
    return 0;
}
