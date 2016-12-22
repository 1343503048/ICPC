#include <bits/stdc++.h>
using namespace std;

int f[205], step[205], n;
bool vis[205];

void bfs(int s, int end) {
	queue<int> Q;
	Q.push(s);
	vis[s] = true;
	step[s] = 0;
	while(!Q.empty()) {
		int t = Q.front();
		Q.pop();
		if(t == end) {
			cout << step[t] << endl;
			return ;
		}
		int up = t+f[t], down = t-f[t];
		if(up <= n && !vis[up]) {
			vis[up] = true;
			step[up] = step[t] + 1 ;
			Q.push(up);
		}
		if(down > 0 && !vis[down]) {
			vis[down] = true;
			step[down] = step[t] + 1;
			Q.push(down);
		}
	}
	cout << "-1" << endl;
}

int main() {
	ifstream cin("data.in");
	int a, b;
	while(cin >> n && n != 0) {
		cin >> a >> b;
		for(int i = 1; i <= n; ++ i) {
			cin >> f[i];
			vis[i] = false;
		}
		bfs(a, b);
	}
	return 0;
}