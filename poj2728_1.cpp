
/***********************************************************
   
        FileName：poj2728.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-02 22:01:46
    Descripttion：最优比率生成树+迭代
   
*************************************************************/
#include <iomanip>
#include <climits>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1005;
const double eps = 1e-4;
const double dmax = 10000000;

double x[N], y[N], z[N];
double map[N][N];
double height[N][N];
double d[N][N];
double dis[N];
bool vis[N];
int pre[N];

double dist(int i, int j) {
    return sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
}

double prim(double o, int n) {
    double sh = 0, sl = 0;
    for(int i = 1; i <= n; ++ i) {
        dis[i] = dmax+1;
        vis[i] = false;
    }
    dis[1] = 0;
    pre[1] = 1;
    for(int i = 1; i <= n; ++ i) {
        int min_vertex;
        double min_val = dmax;
        for(int j = 1; j <= n; ++ j) {
            if(!vis[j] && dis[j] < min_val) {
                min_vertex = j;
                min_val = dis[j];
            }
        }
        vis[min_vertex] = true;
        sh += height[pre[min_vertex]][min_vertex];
        sl += d[pre[min_vertex]][min_vertex];
        for(int j = 1; j <= n; ++ j) {
            double tmp = height[min_vertex][j] - o * d[min_vertex][j];
            if(!vis[j] && dis[j] > tmp) {
                dis[j] = tmp;
                pre[j] = min_vertex;
            }
        }
    }
    return sh / sl;
}

int main() {
    int n;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    while(cin >> n) {
        if(!n) break;
        double r0 = 0, r = 0;
        double sh = 0, sl = 0;
        for(int i = 1; i <= n; ++ i) {
            cin >> x[i] >> y[i] >> z[i];
            for(int j = 1; j < i; ++ j) {
                d[i][j] = d[j][i] = dist(i, j);
                height[i][j] = height[j][i] = fabs(z[i]-z[j]);
            }
            sh += height[i][1];
            sl += d[i][1];
        }
        r = sh / sl; 
        do {
            r0 = r;
            r = prim(r, n);
        }while(fabs(r0-r) > eps);

        cout.setf(ios::fixed);
        cout << fixed << setprecision(3) << r0 << "\n";
    }
    return 0;
}
