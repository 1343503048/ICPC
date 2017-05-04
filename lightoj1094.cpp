
/*************************************************

       Filename: lightoj1094.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-05-04 10:29:00
    Description: 树的直径

#*************************************************/

#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
const int N = 3e4+5;

int dist[N];
bool vis[N];
map<int, int> e[N];

// 求最长路
int spfa(int s) {
    memset(dist, -1, sizeof(dist));
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s] = true;
    dist[s] = 0;
    int a, b = 0;
    while(!q.empty()) {
	int u = q.front();
	q.pop();
	map<int, int>::iterator it = e[u].begin();
	for(; it != e[u].end(); ++ it) {
	    int to = it->first;
	    int w = it->second;
	    int temp = dist[u] + w;
	    if(!vis[to] && dist[to] < temp) {
		dist[to] = temp;
		vis[to] = true;
		if(b < dist[to]) {
		    b = dist[to];
		    a = to;
		}
		q.push(to);
	    }
	}
    }
    return a;
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++ i) {
	int n;
	scanf("%d", &n);
	for(int j = 0; j < n; ++ j) {
	    e[j].clear();
	}
	for(int j = 1; j < n; ++ j) {
	    int x, y, w;
	    scanf("%d%d%d", &x, &y, &w);
	    e[x][y] = e[y][x] = w;
	}
	int s = spfa(1);
	printf("Case %d: %d\n", i, dist[spfa(s)]);
    }
}
