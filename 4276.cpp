#include <bits/stdc++.h>
using namespace std;
const int N = 100+5;

map<int, int> e[N];

int val[N];
int dp[N][505];     //在点i时有t个时间能获取的最大能量
int n, T, top;
int st[N];
bool flag;

//首先寻找一条路径从１到ｎ，将路径上的所有时间花费计算后清零，找不到则逃跑失败
void findPath(int u, int fa, int cost) {		
	if(flag) {
		return ;
	}
	if(u == n) {
		if(cost <= T) {
			T -= cost;
			flag = true;
		}
		for(int i = 1; i < top; ++ i) {
			int u = st[i-1], v = st[i];
			e[u][v] = e[v][u] = 0;
		}
	}
	else {
		for(map<int, int>::iterator it = e[u].begin(); it != e[u].end(); ++ it) {
			int to = it->first, w = it->second;
			if(to != fa) {
				st[top++] = to;
				findPath(to, u, cost+w);
				top --;
			}
		}
	}
	
}

// 使用多余的时间获取最大价值的方法在最短路径上的每个节点上分配合理的时间,
// 并在每个节点上合理的遍历
void dfs(int u, int fa) {
	for(int i = 0; i <= T; ++ i) {
		dp[u][i] = val[u];
	}
	for(map<int, int>::iterator it = e[u].begin(); it != e[u].end(); ++ it) {
		int to = it->first, w = it->second;
		if(to != fa) {
			dfs(to, u);
			int t = 2 * w;
			for(int j = T; j >= 0; j --) {
				for(int k = j-t; k >= 0; k --) {
					//dp[u][j] 代表在ｕ点分配ｊ时间能够得到的最大价值
					dp[u][j] = max(dp[u][j], dp[u][k] + dp[to][j-k-t]);
				}
			}
		}
	}		
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int u, v, w;
	while(cin >> n >> T) {
		for(int i = 1; i <= n; ++ i) {
			e[i].clear();
		}
		for(int i = 1; i < n; ++ i) {
			cin >> u >> v >> w;
			e[u][v] = w;
			e[v][u] = w;	
		}
		for(int i = 1; i <= n; ++ i) {
			cin >> val[i];
		}
		flag = false, top = 0;
		st[top++] = 1;
		findPath(1, -1, 0);
		if(!flag) {
			cout << "Human beings die in pursuit of wealth, and birds die in pursuit of food!\n";
			continue;
		}
		memset(dp, 0, sizeof(dp));
		dfs(1, -1);
		cout << dp[1][T] << "\n";
	}
	return 0;
}
