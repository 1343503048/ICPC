#include <bits/stdc++.h>
using namespace std;
const int N = 1005;

double load[N][N];
const double eps = 1e-4;

void floyd(int n) {
	for(int k = 1; k <= n; ++ k) {
		for(int i = 1; i <= n; ++ i) {
			if(load[i][k] != 0)
			for(int j = 1; j <= n; ++ j) {
				if (load[i][j] < load[i][k] * load[k][j]) {
					load[i][j] = load[i][k] * load[k][j];
				}	
			}
		}
	}
}

int main() {
	//freopen("data.in", "r", stdin);
	int n;
	while(~scanf("%d", &n)) {
		for(int i = 1; i <= n; ++ i) {
			for(int j = 1; j <= n; ++ j) {
				scanf("%lf", &load[i][j]);
			}
		}
		floyd(n);
		int q, a, b;
		scanf("%d", &q);
		while(q--) {
			scanf("%d%d", &a, &b);
			if(load[a][b] < eps) {
				printf("What a pity!\n");
			}
			else {
				printf("%.3lf\n", load[a][b]);
			}
		}
	}
	return 0;
}