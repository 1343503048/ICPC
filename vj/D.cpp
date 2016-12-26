#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f;

class Node {
	public:
	int to, w;
	Node(int _to, int _w){
		to = _to;
		w = _w;
	}
};

const int MAXN = 1000+5;
int n, t;
int dist[MAXN];
bool vis[MAXN];
vector<vector<Node> > e(MAXN);
 
int spfa() {
	queue<int> q;
	q.push(n);
	dist[n] = 0;
	vis[n] = true;
	while(!q.empty()) {
		int t = q.front();
		q.pop();
		vis[t] = false;
		for(int i = 0; i < e[t].size(); ++ i) {
			Node edge = e[t][i];
			if(dist[edge.to] > dist[t] + edge.w) {
				dist[edge.to] = dist[t] + edge.w;
				if(!vis[edge.to]) {
					vis[edge.to] = true;
					q.push(edge.to);
				}
			}
		}
	}
	return dist[1];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in");
	while(cin >> t >> n) {
		memset(dist, INF, sizeof(dist));
		memset(vis, false, sizeof(vis));
		while(t -- ) {
			int x, y, w;
			cin >> x >> y >> w;
			e[x].push_back(Node(y, w));
			e[y].push_back(Node(x, w));
		}
		cout << spfa() << endl;
	}
	return 0;
}