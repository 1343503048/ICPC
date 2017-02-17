#include <bits/stdc++.h>
using namespace std;
const int N = 200+5;
const int inf = 0xffffff;

int n, m;
int pre[N];			//存储前驱节点
int dist[N];		//存储到源点s的距离

bool inq[N];		//每个顶点是否在队列中
int min_c_f; 		//记录增广路径中的残余容量
int vertex;			//顶点数
int sum;			//保存最小费用

struct Node {
	int c_f, v;	//残余容量,费用
};

Node g[N][N];

struct Man {
	int x, y;
};

Man man[N];

struct House {
	int x, y;
};

House house[N];

void spfa(int s) {
	queue<int> Q;
	int u, v;
	for(int i=0; i<=vertex; i++)//初始化  
    {  
        dist[i] = INT_MAX;  
        pre[i] = -1;  
        inq[i] = 0;  
    }  
	dist[s] = 0;
	Q.push(s);
	while(!Q.empty()) {
		u = Q.front();
		Q.pop();
		inq[u] = false;
		for(int i = 0; i <= vertex; ++ i) {
			if(g[u][i].c_f == 0) {
				continue;
			}
			if(g[u][i].v == INT_MAX) {
				g[u][i].v = -g[i][u].v;    //逆向费用
			}
			if(dist[i] > dist[u] + g[u][i].v) {
				dist[i] = dist[u] + g[u][i].v;
				pre[i] = u;
				if(!inq[i]) {
					Q.push(i);
					inq[i] = true;
				}
			}
		}
	}
}

void ford_fulkerson(int s, int t) {
	spfa(s);
	while(pre[t] != -1) {
		sum += dist[t];
		min_c_f = INT_MAX;
		int u = pre[t], v = t;
		while(u != -1) {
			if(min_c_f > g[u][v].c_f) {			//c_f为残余容量
				min_c_f = g[u][v].c_f;
			}
			v = u;
			u = pre[u];
		}
		u = pre[t], v = t;
		while(u != -1) {
			g[u][v].c_f -= min_c_f;
			g[v][u].c_f += min_c_f;
			v = u;
			u = pre[u];
		}
		spfa(s);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	while(cin >> n >> m && n != 0){
		sum = 0;
		int mcnt = 0, hcnt = 0, w;
		char temp;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				cin >> temp;
				if(temp == 'm') {
					mcnt ++;
					man[mcnt].x = i;
					man[mcnt].y = j;
				}else if(temp == 'H'){
					hcnt ++;
					house[hcnt].x = i;
					house[hcnt].y = j;
				}
			}
		}
		vertex = mcnt + hcnt + 1;
		//初始化
		for (int u = 0; u <= vertex; ++ u) {
			for (int v = 0; v <= vertex; ++ v) {
				g[u][v].c_f = g[v][u].c_f = 0;
				g[u][v].v = g[v][u].v = INT_MAX;
			}
		}

		for(int i = 1; i <= mcnt; ++ i) {
			g[0][i].v = 0;
			g[0][i].c_f = 1;
			for(int j = 1; j <= hcnt; ++ j) {
				g[i][j+mcnt].v = abs(house[j].x - man[i].x) + abs(house[j].y - man[i].y);
				g[i][j+mcnt].c_f = 1;
				g[j+mcnt][vertex].v = 0;
				g[j+mcnt][vertex].c_f = 1;
			}
		}
		ford_fulkerson(0, vertex);
		cout << sum << endl;
	}
	return 0;
}
