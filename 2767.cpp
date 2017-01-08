//1. 基本上是模板题，首先对有向图进行缩点，即把所有强连通分量看成是一个点，Targan 算法 http://www.byvoid.com/blog/scc-tarjan/
//2. 统计出度和入度为 0 的点的个数，输出其中的最大的一个即可。
#include <bits/stdc++.h>
using namespace std;
const int N = 20000+5;
const int M = 50000+5;

struct Edge{
	int to, next;
};

Edge e[M];
int vis[N], DNF[N], low[N], head[N], scc[N];
int in[N], out[N];
bool inStack[N];
int t, ans, c1, c0;
stack<int> s;

void addEdge(int from, int to, int &edgeCount){
	e[edgeCount].to = to;
	e[edgeCount].next = head[from];
	head[from] = edgeCount++;
}

void tarjan(int u) {
	low[u] = DNF[u] = t++;		//时间戳
	inStack[u] = true;
	s.push(u);
	for(int i = head[u]; i != -1; i = e[i].next){
		int v = e[i].to;
		if(DNF[v] == -1) {
			tarjan(v);
			low[u] = min(low[v], low[u]);
		}
		else if(inStack[v]){
			low[u] = min(low[u], DNF[v]);	
		}
	}
	if(low[u] == DNF[u]) {
		int v;
		do{
			v = s.top();
			scc[v] = ans;		//标记联通分量，缩点
			inStack[v] = false;
			s.pop();
		}while(v != u);
		ans ++;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	int n, m, T;
	cin >> T;
	while(T --) {
		cin >> n >> m;
		memset(low, -1, sizeof(low));
		memset(head, -1, sizeof(head));
		memset(DNF, -1, sizeof(DNF));
		memset(inStack, false, sizeof(inStack));
		memset(in, 0, sizeof(in));
		ans = t = c1 = c0 = 0;
		int edgeCount = 0;
		while(m --) {
			int x, y;
			cin >> x >> y;
			addEdge(x, y, edgeCount);
			in[y] ++;
		}
		for(int i = 1; i <= n; ++ i) {
			in[i] = out[i] = 0;
			if(DNF[i] == -1) {
				tarjan(i);
			}
		}
		if(ans == 1) {
			cout << "0" << endl;
		}
		else {
			for(int i = 1; i <= n; ++ i) {
				for(int j = head[i]; j != -1; j = e[j].next) {
					int v = scc[i], u = scc[e[j].to];
					if(u != v) {
						in[u] ++;			//统计每个联通分量的出度与入度
						out[v] ++;
					}
				}
			}
			for(int i = 0; i < ans; ++ i) {
				c0 += (in[i] == 0);
				c1 += (out[i] == 0);
			}
			cout << max(c0, c1) << endl;
		}
	}
	return 0;
}
