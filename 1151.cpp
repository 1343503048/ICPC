/*************************************************

       Filename: 1151.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-04-22 15:55:33
    Description: 最小路径覆盖 

*************************************************/

// http://www.cnblogs.com/justPassBy/p/5369930.html
// 最小路径覆盖数=DAG图中的节点数-相应二分图的最大匹配数
//     一开始每个点都是独立的为一条路径，总共有n条不相交路径。
// 我们每次在二分图里找一条匹配边就相当于把两条路径合成了
// 一条路径，也就相当于路径数减少了1。所以找到了几条匹配边，
// 路径数就减少了多少。所以有最小路径覆盖=原图的结点数-新图的最大匹配数。
//
#include <bits/stdc++.h>
using namespace std;
const int N = 125;
vector<int> e[N];
int match[N];
bool vis[N];

int find(int v) {
    for(size_t i = 0; i < e[v].size(); ++ i) {
	int to = e[v][i];
	if(!vis[to]) {
	    vis[to] = true;
	    if(match[to] == -1 || find(match[to])) {
		match[to] = v;
		return 1;
	    }
	}
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    while(t --) {
	int n, m;
	cin >> n >> m;
	memset(match, -1, sizeof(match));
	for(int i = 0; i <= n; ++ i) {
	    e[i].clear();
	}
	while(m --) {
	    int x, y;
	    cin >> x >> y;
	    e[x].push_back(y);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++ i) {
	    memset(vis, false, sizeof(vis));
	    if(find(i)) {
		cout << "-" << i << endl;
		ans ++;
	    }
	}
	cout << n - ans << endl;
    }
    return 0;
}
