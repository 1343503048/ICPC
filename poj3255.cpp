//次短路
#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <functional>
using namespace std;
const int N = 5000+5;
const int inf = 0x3f3f3f;
typedef pair<int, int> p; // <d, id>;

struct Edge {
	int to, w, next;
};

Edge e[200005];
int dist[N], distR[N];
int head[N], edgeNum;

void addEdge(int from, int to, int w) {
	e[edgeNum].to = to;
	e[edgeNum].w = w;
	e[edgeNum].next = head[from];
	head[from] = edgeNum++;	
}

int spfa(int s, int t) {
	priority_queue<p, vector<p>, greater<p> > pq;
	pq.push(p(0, s));
	dist[s] = 0;
	while(!pq.empty()) {
		p t = pq.top(); 
		pq.pop();
		int d = t.first, u = t.second;
		if(distR[u] < d) {
			continue;
		}
		for(int i = head[u]; i != -1; i = e[i].next) {
			int to = e[i].to;
			int temp = d + e[i].w;
			if(dist[to] > temp) {
				swap(temp, dist[to]);
				pq.push(p(dist[to], to));
			}
			if(temp < distR[to] && temp > dist[to]) {
				distR[to] = temp;
				pq.push(p(distR[to], to));
			}
		}
	}
	return distR[t];
}

int main() {
	// freopen("data.in", "r", stdin);
	int n, r;
	int a, b, c;
	while(~scanf("%d%d", &n, &r)) {
		memset(head, -1, sizeof(head));
		memset(dist, inf, sizeof(dist));
		memset(distR, inf, sizeof(distR));
		edgeNum = 0;
		while(r--) {
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		printf("%d\n", spfa(1, n));
	}
	return 0;
}