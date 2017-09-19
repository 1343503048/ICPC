
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
const int N = 250000;

int go[N][26];
int pre[N];
int step[N];
int rt, last;
int cur;

void init() {
    cur = 1;
    rt = last = cur ++;
}

void insert(int w) {
    int p = last;
    int np = cur ++;
    step[np] = step[p] + 1;
    while(p&&!go[p][w]) {
        go[p][w] = np;
        p = pre[p];
    }
    if(p == 0) {
        pre[np] = rt;
    }
    else {
        int q = go[p][w];
        if(step[p]+1 == step[q]) {
            pre[np] = q;
        }
        else {
            int nq = cur ++;
            memcpy(go[nq], go[q], sizeof(go[q]));
            step[nq] = step[p] + 1;
            pre[nq] = pre[q];
            pre[q] = nq;
            pre[np] = nq;
            while(p&&go[p][w] == q) {
                go[p][w] = nq;
                p = pre[p];
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
        if(go[p][x]) {
            len ++;
            p = go[p][x];
        } 
        else {
            while(p&&!go[p][x]) p = pre[p];
            if(!p) {
                p = rt;
                len = 0;
            }
            else {
                len = step[p]+1;
                p = go[p][x];
            }
        }
        res = max(res, len);
    }
    printf("%d\n", res);
    return 0;
}
