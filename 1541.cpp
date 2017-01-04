#include <bits/stdc++.h>
#define MAXN 32000+10
using namespace std;
int sum[MAXN];
int level[MAXN>>1];
int N, M;
int lowbit(int x) {
    return x & (-x);
}

void update(int x, int d) {
    while(x <= MAXN) {
        sum[x] += d;
        x += lowbit(x);
    }
}
int query(int x) {
    int ans = 0;
    while(x > 0) {
        ans += sum[x];
        x -= lowbit(x);
    }
    return ans;
}
int main() {
	freopen("data.in", "r", stdin);
    while(scanf("%d", &N) != EOF) {
        memset(sum , 0, sizeof(sum));
		memset(level, 0, sizeof(level));
        int a, b;
        for(int i = 1; i <= N; i++) {
            scanf("%d%d", &a, &b);
			a ++;
			level[query(a)] ++;
            update(a, 1);
        }
		for(int i = 0; i < N; ++ i) {
			printf("%d\n", level[i]);
		}
    }
    return 0;
}
