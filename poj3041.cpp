//最大匹配数=最小点覆盖
//匈牙利算法（bfs）
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int N = 500+5;

std::vector<int> e[N];
int pre[N], Mx[N], My[N], vis[N];

int maxflow(int n) {
	memset(pre, -1, sizeof(pre));
	memset(My, -1, sizeof(My));
	memset(Mx, -1, sizeof(Mx));
	int cnt = 0;
	for(int i = 1; i <= n; ++ i) {
		if(Mx[i] == -1) {
			queue<int> Q;
			Q.push(i);
			bool flag = false;
			while(!Q.empty() && !flag) {
				int v = Q.front();
				Q.pop();
				for(size_t j = 0; j < e[v].size(); ++ j) {
					int to = e[v][j];
					if(vis[to] != i) {
						vis[to] = i;
						if(My[to] > 0) {
							pre[My[to]] = v;
							Q.push(My[to]);
						}
						else {
							flag = true;
							int d = v, e = to;
							while(d != -1) {
								int t = Mx[d];
								Mx[d] = e;
								My[e] = d;
								d = pre[d];
								e = t;
							}
							break;
						}
					}
				}
			}
			cnt += (Mx[i] > 0);
		}
	}
	return cnt;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int n, k;
	while(cin >> n >> k) {
		while(k --) {
			int x, y;
			cin >> x >> y;
			e[x].push_back(y);
		}
		cout << maxflow(n) << endl;
		for(int i = 1; i <= n; ++ i) {
			e[i].clear();
		}
	}
	return 0;
}
