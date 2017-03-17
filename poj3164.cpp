#include <cstdio>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
const int M = 10000+5;
const int N = 100+5;
const int inf = 2e9;

struct Edge {
	int from, to;
	double cost;
	Edge(){}
	Edge(int _from, int _to, double _cost) {
		from = _from;
		to = _to;
		cost = _cost;
	}
};


struct Node {	
	double x, y;
};

Edge e[M];
Node node[N];
int n, m;
double in[N];
int pre[N], id[N];
int vis[N];

double dis(Node a, Node b) {
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );  
}

double zhuliu(int root) {
	double res = 0;
	int u, v;

	while(true) {
		for(int i = 0; i < n; ++ i) {
			in[i] = inf;
		}
		for(int i = 0; i < m; ++ i) {
			Edge E = e[i];
			if(E.from != E.to && E.cost < in[E.to]) {
				pre[E.to] = E.from;	//记录前驱
				in[E.to] = E.cost;	//更新
			}
		}

		//存在孤立点,则不存在最小树形图
		for(int i = 0; i < n; ++ i) {
			if(i != root && in[i] == inf) {
				return -1;
			}
		}

		// 找有向环
		int flag = 0;		//记录缩点后的点数
		memset(id, -1, sizeof(id));
		memset(vis, -1, sizeof(vis));
		in[root] = 0;

		//找环缩点
		for(int i = 0; i < n; ++ i) {
			res += in[i];
			v = i;
			//找图中的有向环,三种情况终止while循环
			//1.碰到属于同一环的点
			//2.回溯到根
			//3.节点已属于其他环
			while(vis[v] != i && id[v] == -1 && v != root) {
				vis[v] = i;	//标记
				v = pre[v];
			}

			//找到某节点属于其他环 或者 遍历到根
			if(v != root && id[v] == -1) {	//找到环
				for(u = pre[v]; u != v; u = pre[u]) {
					id[u] = flag;
				}
				id[v] = flag ++;
			}
		}

		if(flag == 0) {
			break ;		//不存在有向环，找到最小树形图
		}

		for (int i = 0; i < n; ++ i) {
			if(id[i] == -1) {
				id[i] = flag ++;	//标记点
			}
		}

		for(int i = 0; i < m; ++ i) {
			v = e[i].to;
			e[i].from = id[e[i].from];
			e[i].to = id[e[i].to];
			if(e[i].from != e[i].to) {
				e[i].cost -= in[v];	//两点不在同一个环 u到v的距离为 边权cost - in[v]
			}
		}

		n = flag;
		root = id[root];
	}
	return res;
}

int main() {
	// freopen("data.in", "r", stdin);
	while(~scanf("%d%d", &n, &m)) {
		int a, b;
		for(int i = 0; i < n; ++ i) {
			scanf("%lf%lf", &node[i].x, &node[i].y);
		}
		for(int i = 0; i < m; ++ i) {
			scanf("%d%d", &a, &b);
			a --;
			b --;
			e[i] = Edge(a, b, (a == b ? inf : dis(node[a], node[b])));
		}
		double ans = zhuliu(0);
		if(ans < 0) {
			puts("poor snoopy");
		}
		else {
			printf("%.2f\n", ans);
		}
	}
	return 0;
}