#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

vector<int> e[105];
int matchY[305], pre[305], matchX[105];
int vis[305];

int maxFlow(int p) {
	int ans = 0;
	memset(pre, -1, sizeof(pre));
	memset(matchY, -1, sizeof(matchY));
	memset(matchX, -1, sizeof(matchX));
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= p; ++ i) {
		if(matchX[i] == -1) {
			queue<int> Q;
			bool flag = false;
			Q.push(i);
			pre[i] = -1;
			while(!Q.empty() && !flag) {
				int v = Q.front();
				Q.pop();
				for(size_t j = 0; j < e[v].size(); ++ j) {
					int to = e[v][j];
					if(vis[to] != i) {
						vis[to] = i;
						Q.push(matchY[to]);
						if(matchY[to] >= 0) {
							pre[matchY[to]] = v;
						}
						else {
							int d = v, e = to;
							flag = true;
							while(d != -1) {
								int t = matchX[d];
								matchX[d] = e;
								matchY[e] = d;
								d = pre[d];
								e = t;
							}
							break;
						}
					}
				}
			}     
			if(matchX[i] != -1){
				ans ++;
			}
		}
	}
	return ans;
}

int main() {
	//ifstream cin("data.in");
	//std::ios::sync_with_stdio(false);
	//std::cin.tie(0);
	//freopen("data.in", "r", stdin);
	int p, n, t;
	scanf("%d", &t);
	while(t --) {
		scanf("%d%d", &p, &n);
		for(int i = 1; i <= p; ++ i) {
			e[i].clear();
			int c;
			scanf("%d", &c);
			while(c --) {
				int num;
				scanf("%d", &num);
				e[i].push_back(num);
			}
		}
		if(maxFlow(p) == p) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}