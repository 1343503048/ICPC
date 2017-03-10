#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1000+5;

int f[N], degree[N];

void init(int n) {
		for(int i = 1; i <= n; ++ i) {
				f[i] = i;
				degree[i] = 0;
		}
}

int find(int x) {
		if(f[x] != x) {
				f[x] = find(f[x]);
		}
		return f[x];
}

void unit(int x, int y) {
		x = find(x);
		y = find(y);
		if(x != y) {
				f[x] = y;
		}
}

int main() {
		int t, n, m;
		scanf("%d", &t);
		while(t --) {
				scanf("%d%d", &n, &m);
				init(n);
				int x, y;
				while(m --) {
					scanf("%d%d", &x, &y);
					unit(x, y);
					degree[x] ++;
					degree[y] ++;
				}
				int cnt = 0; //连通图的数目
				int ans = 0; //度为奇数的点的数目
				for(int i = 1; i <= n; ++ i) {
						if(f[i] == i) {
							cnt ++;
						}
						if(degree[i] & 1) {
							ans ++;
						}
				}
				if(cnt > 1) {
					puts("No");
					continue;
				}
				if(ans == 0 || ans == 2) {
						puts("Yes");
				}
				else {
						puts("No");
				}
		}
		return 0;
}
