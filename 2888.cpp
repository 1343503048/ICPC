
/***********************************************************
   
        FileName：2888.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-05 23:47:43
    Descripttion：二维ST
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 305;

int mx[N][N][10][10];
int val[N][N];

void init(int n, int m) {
    int x = log(n)/log(2);
    int y = log(m)/log(2);
    for(int i = 0; i <= x; ++ i) {
        for(int j = 0; j <= y; ++ j) {
            if(i == 0 && j == 0) continue;
            for(int a = 1; a+(1<<i)-1 <= n; ++ a) {
                for(int b = 1; b+(1<<j)-1 <= m; ++ b) {
                    if(i == 0) {
                        mx[a][b][i][j] = max(mx[a][b][i][j-1], mx[a][b+(1<<(j-1))][i][j-1]);
                    }
                    else {
                        mx[a][b][i][j] = max(mx[a][b][i-1][j], mx[a+(1<<(i-1))][b][i-1][j]);
                    }
                }
            }
        }
    }
}

int ask(int a, int b, int c, int d) {
    int x = log(c-a+1)/log(2);
    int y = log(d-b+1)/log(2);
    int v1 = max(mx[a][b][x][y], mx[c-(1<<x)+1][b][x][y]);
    int v2 = max(mx[a][d-(1<<y)+1][x][y], mx[c-(1<<x)+1][d-(1<<y)+1][x][y]);
    return max(v1, v2);
}

int main() {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
        memset(mx, 0, sizeof(mx));
        for(int i = 1; i <= n; ++ i) {
            for(int j = 1; j <= m; ++ j) {
                scanf("%d", &val[i][j]);
                mx[i][j][0][0] = val[i][j];
            }
        }

        init(n, m);

        int q;
        scanf("%d", &q);
        while(q --) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            int res = ask(a, b, c, d);
            printf("%d ", res);
            if(res == val[a][b]) {
                printf("yes\n");
            }
            else if(res == val[a][d]) {
                printf("yes\n");
            }
            else if(res == val[c][b]) {
                printf("yes\n");
            }
            else if(res == val[c][d]) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
        }
    }
    return 0;
}
