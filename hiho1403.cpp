
/***********************************************************
   
        FileName：hiho1403.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-11 13:54:12
    Descripttion：后缀数组-至少重复k次的最长子串
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
const int M = 256;

int cntA[N], cntB[N];
int ch[N];
int sa[N], rk[N], height[N];
int A[N], B[N];
int tsa[N];
int n;

void solve()
{
    for (int i = 0; i < M; i ++) cntA[i] = 0;
    for (int i = 1; i <= n; i ++) cntA[ch[i]] ++;
    for (int i = 1; i < M; i ++) cntA[i] += cntA[i - 1];
    for (int i = n; i; i --) sa[cntA[ch[i]] --] = i;
    rk[sa[1]] = 1;
    for (int i = 2; i <= n; i ++)
    {
        rk[sa[i]] = rk[sa[i - 1]];
        if (ch[sa[i]] != ch[sa[i - 1]]) rk[sa[i]] ++;
    }
    for (int l = 1; rk[sa[n]] < n; l <<= 1)
    {
        for (int i = 0; i <= n; i ++) cntA[i] = 0;
        for (int i = 0; i <= n; i ++) cntB[i] = 0;
        for (int i = 1; i <= n; i ++)
        {
            cntA[A[i] = rk[i]] ++;
            cntB[B[i] = (i + l <= n) ? rk[i + l] : 0] ++;
        }
        for (int i = 1; i <= n; i ++) cntB[i] += cntB[i - 1];
        for (int i = n; i; i --) tsa[cntB[B[i]] --] = i;
        for (int i = 1; i <= n; i ++) cntA[i] += cntA[i - 1];
        for (int i = n; i; i --) sa[cntA[A[tsa[i]]] --] = tsa[i];
        rk[sa[1]] = 1;
        for (int i = 2; i <= n; i ++)
        {
            rk[sa[i]] = rk[sa[i - 1]];
            if (A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]) rk[sa[i]] ++;
        }
    }
    for (int i = 1, j = 0; i <= n; i ++)
    {
        if (j) j --;
        while (ch[i + j] == ch[sa[rk[i] - 1] + j]) j ++;
        height[rk[i]] = j;
    }
}   

int main() {
    int k;
    while(~scanf("%d%d", &n, &k)) {
        for(int i = 1; i <= n; ++ i) {
            scanf("%d", &ch[i]);
        }
        solve();
        
        int l = 1, r = n;
        int res = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for(int i = 1; i <= n; ++ i) {
                if(height[i] >= mid) ++ cnt;
                else cnt = 1;
                if(cnt >= k) break;
            }
            if(cnt>=k) {
                res = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        printf("%d\n", res);
    }    
    return 0;
}
