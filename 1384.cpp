//差分约束
#include <bits/stdc++.h>
using namespace std;
const int N = 50000+5;

struct Edge {
	int to, w, next;
} e[3*N];
int dist[N], head[N];
bool vis[N];

void addEdge(int from, int to, int w, int &edgeCount) {
	e[edgeCount].to = to;
	e[edgeCount].w = w;
	e[edgeCount].next = head[from];
	head[from] = edgeCount++;
}

void spfa(int l, int r) { 
	for(int i = l; i <= r; ++ i) {
		dist[i] = INT_MIN;
	}
	queue<int> Q;
	vis[l] = true;
	Q.push(l);
	dist[l] = 0;
	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		vis[v] = false;
		for(int i = head[v]; i != -1; i = e[i].next){
			int to = e[i].to;
			if(dist[to] < dist[v] + e[i].w) {
				dist[to] = dist[v] + e[i].w;
				if(!vis[to]){
					vis[to] = true;
					Q.push(to);
				}
			}
		}
	}
	cout << dist[r] << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	int n;
	while(cin >> n){
		memset(head, -1, sizeof(head));
		int edgeCount = 0, a, b, c;
		int l = INT_MAX, r = 0;
		while(n --) {
			cin >> a >> b >> c;
			addEdge(a, b+1, c, edgeCount);
			l = min(l, a);
			r = max(r, b+1);
		}
		for(int i = l; i < r; ++ i) {
			addEdge(i+1, i, -1, edgeCount);
			addEdge(i, i+1, 0, edgeCount);
		}
		spfa(l, r);
	}
	return 0;
}
