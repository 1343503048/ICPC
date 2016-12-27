#include <stdio.h>
#include <string.h>
#define MAX 50000+5

int f[MAX];

int find(int x){	
	if(f[x] == -1){
		f[x] = x;
	}
	while(f[x] != x){
		x = f[x];
	}
	return f[x];
}

int main() {
	int n, m;
	int cnt = 1;
	while(~scanf("%d%d", &n, &m) && (n || m)){
		memset(f, -1, sizeof(f));
		while(m --){
			int i, j;
			scanf("%d%d", &i, &j);
			int x0 = find(i);
			int y0 = find(j);
			n -= (x0 != y0);
			f[y0] = x0;
		}
		printf("Case %d: %d\n",cnt++, n);
	}
	return 0;
}
