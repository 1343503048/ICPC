
/*************************************************
#
#       Filename: uva481.cpp
#         Author: zQ
#          Email: zq216991@foxmail.com
#         Create: 2017-04-19 17:01:00
#    Description: 打印LIS 
#
#*************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int N = 1e5+5;

int val[N], dp[N], f[N], pos[N];

int main() {
    int n = 0;
    int m;
    while(scanf("%d", &m) != EOF) {
	val[n++] = m;	
    }
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    // dp[0] = 0;
    for(int i = 0; i < n; ++ i) {
	int lpos = lower_bound(dp, dp+n, val[i]) - dp;
	dp[lpos] = val[i];
	pos[lpos] = i;
	f[i] = (lpos ? pos[lpos-1] : -1);  // 记录路径
    }
    stack<int> s;
    n = lower_bound(dp, dp+n, 0x3f3f3f3f) - dp;
    printf("%d\n-\n", n);
    for(int i = pos[n-1]; i != -1; i = f[i]) {
	s.push(val[i]);	
    }
    while(!s.empty()) {
	printf("%d\n", s.top());
	s.pop();
    }
    return 0;
}

