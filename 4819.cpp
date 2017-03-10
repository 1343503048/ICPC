#include <bits/stdc++.h>
using namespace std;
const int N = 800+5;
const int inf = 0x3f3f3f;
#define lson rt<<1
#define rson rt<<1|1

struct NodeY {
	int ly, ry, Min, Max;
};

int posX[N], posY[N];
int n;

struct NodeX {
	int lx, rx;
	NodeY treeY[N<<2];
	void buildY(int rt, int l, int r) {
		treeY[rt].ly = l;
		treeY[rt].ry = r;
		treeY[rt].Min = inf;
		treeY[rt].Max = 0;
		if(l == r) {
			posY[l] = rt;
			return;		
		}
		int m = (l + r) >> 1;
		buildY(lson, l, m);
		buildY(rson, m+1, r);
	}

	int queryY(int rt, int y1, int y2, int op) {
		if(treeY[rt].ly >= y1 && treeY[rt].ry <= y2) {
			return op == 0? treeY[rt].Min : treeY[rt].Max;
		}
		int m = (treeY[rt].ly + treeY[rt].ry) >> 1;
		if(m < y1) {
			return queryY(rt<<1|1, y1, y2, op);
		}
		else if(m >= y2) {
			return queryY(rt<<1, y1, y2, op);
		}
		else {
			int pl = queryY(rt<<1, y1, y2, op);
			int pr = queryY(rt<<1|1, y1, y2, op);
			return op == 0? min(pl, pr) : max(pl, pr);
		}
	}
};

NodeX treeX[N<<2];

void buildX(int rt, int l, int r) {
	treeX[rt].lx = l; treeX[rt].rx = r;
	treeX[rt].buildY(1, 1, n);
	if(l == r) {
		posX[l] = rt;
		return ;
	}
	int m = (l + r) >> 1;
	buildX(lson, l, m);
	buildX(rson, m+1, r);
}

int queryX(int rt, int x1, int x2, int y1, int y2, int op) {
	if(treeX[rt].lx >= x1 && treeX[rt].rx <= x2) {
		return treeX[rt].queryY(1, y1, y2, op);
	}
	int m = (treeX[rt].lx + treeX[rt].rx) >> 1;
	if(m < x1) {
		return queryX(rson, x1, x2, y1, y2, op);
	}
	else if(m >= x2) {
		return queryX(lson, x1, x2, y1, y2, op);
	}
	else {
		int pl = queryX(lson, x1, x2, y1, y2, op);
		int pr = queryX(rson, x1, x2, y1, y2, op);
		return op == 0? min(pl, pr) : max(pl, pr);
	}
}

void pushUpY(int rtX, int rtY) {
	treeX[rtX].treeY[rtY].Min = min(treeX[rtX].treeY[rtY<<1].Min, treeX[rtX].treeY[rtY<<1|1].Min);
	treeX[rtX].treeY[rtY].Max = max(treeX[rtX].treeY[rtY<<1].Max, treeX[rtX].treeY[rtY<<1|1].Max);
}

void pushUpX(int rtX, int rtY) {
	treeX[rtX].treeY[rtY].Min = min(treeX[rtX<<1].treeY[rtY].Min, treeX[rtX<<1|1].treeY[rtY].Min);
	treeX[rtX].treeY[rtY].Max = max(treeX[rtX<<1].treeY[rtY].Max, treeX[rtX<<1|1].treeY[rtY].Max);
}

void modify(int x, int y, int v) {
	treeX[x].treeY[y].Min = v;
	treeX[x].treeY[y].Max = v;
}

void update(int x, int y, int v) {
	for(int i = posX[x]; i > 0; i >>= 1) {
		for(int j = posY[y]; j > 0; j >>= 1) {
			if(i == posX[x] && j == posY[y]) {
				modify(i, j, v);
				continue;
			}
			pushUpY(i, j);
		}
		if(i != posX[x]) {
			for(int j = posY[y]; j > 0; j >>= 1) {
				pushUpX(i, j);
			}
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++ i) {
		scanf("%d", &n);
		buildX(1, 1, n);
		for(int u = 1; u <= n; ++ u) {
			for(int v = 1; v <= n; ++ v) {
				int x;
				scanf("%d", &x);
				update(u, v, x);
			}
		}
		int m;
		scanf("%d", &m);
		printf("Case #%d:\n", i);
		while(m --) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			int x1 = max(1, a-c/2);
			int x2 = min(n, a+c/2);
			int y1 = max(1, b-c/2);
			int y2 = min(n, b+c/2);
			int mi = queryX(1, x1, x2, y1, y2, 0);
			int mx = queryX(1, x1, x2, y1, y2, 1);
			int ans = (mx + mi) >> 1;
			printf("%d\n", ans);
			update(a, b, ans);
		}
	}
	return 0;
}