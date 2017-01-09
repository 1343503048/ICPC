//1.求出图中的所有联通分量，缩点,同时用cost数组记录每个连通分量中所需要的最小花费
//2.统计连通分量的入度,
//3.若一个连通分量入度不为0，则代表可以由属于其他连通分量的人连通他；若为0则代表必须由Wiskey来联系，
//此时连通此个连通分量的花费为此连通分量的最小hua费
#include <bits/stdc++.h>
using namespace std;
const int N = 1000+5;

struct Edge{
	int to, next;
};

Edge e[3000];
int val[N], head[N], dnf[N], low[N], scc[N], indegree[N], cost[N];
bool in[N];
int ans, t;
stack<int> s;

void addEdge(int from, int to, int &edgeCount) {
	e[edgeCount].to = to;
	e[edgeCount].next = head[from];
	head[from] = edgeCount ++;
}

void tarjan(int v) {
	dnf[v] = low[v] = t ++;
	s.push(v);
	in[v] = true;
	for(int i = head[v]; i != -1; i = e[i].next) {
		int u = e[i].to;
		if(dnf[u] == -1) {
			tarjan(u);
			low[v] = min(low[v], low[u]);
		}
		else if(in[u]) {
			low[v] = min(low[v], dnf[u]);
		}
	}
	if(low[v] == dnf[v]) {
		int j;
		do{
			j = s.top();
			in[j] = false;
			scc[j] = ans;
			cost[ans] = min(cost[ans], val[j]);		//找出此连通分量的最小花费
			s.pop();
		}while(j != v);
		ans ++;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in");
	int n, m;
	while(cin >> n >> m) {
		for(int i = 1; i <= n; ++ i) {
			cin >> val[i];
			head[i] = low[i] = dnf[i] = -1;
			in[i] = false;
			indegree[i] = 0;
			cost[i] = INT_MAX;
		}
		int edgeCount = 0;
		ans = t = 1;
		while(m --) {
			int a, b;
			cin >> a >> b;
			addEdge(a, b, edgeCount);
		}
		for(int i = 1; i <= n; ++ i) {
			if(dnf[i] == -1) {
				tarjan(i);
			}
		}
		for(int i = 1; i <= n; ++ i) {
			for(int j = head[i]; j != -1; j = e[j].next) {
				int v = e[j].to;
				if(scc[v] != scc[i]) {
					indegree[scc[v]] ++;		//统计入度
				}
			}
		}
		int a = 0, b = 0;
		for(int i = 1; i <= ans; ++ i) {
			if(indegree[i] == 0) {	//连通分量入度为0，需要Wiskey联系
				a ++;
				b += cost[i];
			}
		}
		cout << a << " " << b << endl;
	}
	return 0;
}
