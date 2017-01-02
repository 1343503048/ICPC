//此题的思路就是尽可能多的找出连在一起两块正方形
//因此直接用匈牙利算法求最大匹配数
//然后用法一个pair数组来表示匹配的两个正方形的坐标
#include <bits/stdc++.h>
using namespace std;
const int go[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

int land[105][105];
pair<int, int> match[105][105];
bool vis[105][105];
int n, m;

int find(int x, int y) {
	for(int i = 0; i < 4; ++ i) {
		int a = x + go[i][0], b = y + go[i][1];
		if(land[a][b] == 0 && !vis[a][b] && a > 0 && a <= n && b > 0 && b <= m) {
			vis[a][b] = true;
			int c = match[a][b].first, d = match[a][b].second;
			if(c == 0 || find(c, d)) {
				match[a][b].first = x;
				match[a][b].second = y;
				match[x][y].first = a;
				match[x][y].second = b;
				return 1;
			}
		}
	}
	return 0;
}

int hungary(int n , int m) {
	int ans = 0;
	for(int i = 1; i <= n; ++ i) {
		for(int j = 1; j <= m; ++ j) {
			if(land[i][j] == 0 && match[i][j].first == 0) {
				memset(vis, false, sizeof(vis));
				ans += find(i, j);
			}
		}
	}
	return ans;
}

int main() {
	//ifstream cin("data.in");
	while(cin >> n >> m && (n || m)) {
		memset(land, 0, sizeof(land));
		int k;
		cin >> k;
		while(k --) {
			int x, y;
			cin >> x >> y;
			land[x][y] = 1;			//当前坐标为pond
		}
		cout << hungary(n, m) << endl;
		for(int i = 1; i <= n; ++ i) {
			for(int j = 1; j <= m; ++ j) {
				int c = match[i][j].first;
				int d = match[i][j].second;
				if(land[i][j] == 0 && c != 0) {
					cout << "(" << i << "," << j << ")--(" 
						<< c << "," << d << ")" << endl;
						match[i][j].first = match[i][j].second = 0;
						match[c][d].first = match[c][d].second = 0;
				}
			}
		}
		cout << endl;
	}
	return 0;
}
