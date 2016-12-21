//TopSort
#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000+15;

vector<int> e[MAX];
int in[MAX], money[MAX]; //jilujiangjin

void topSort(int n) {
	queue<int> Q;
	int sum = 0;
	for(int i = 1; i <= n; ++ i) {
		if(in[i] == 0) {
			Q.push(i);
			money[i] = 888;
		}
	}
	while(!Q.empty()) {
		int t = Q.front();
		Q.pop();
		sum += money[t];
		n --;
		for(int i = 0; i < e[t].size(); ++ i) {
			int v = e[t][i];
			in[v] --;
			if(in[v] == 0) {
				Q.push(v);
				money[v] = money[t] + 1;
			}
		}
	}
	if(n > 0) {
		cout << "-1" << endl;
	}
	else {
		cout << sum << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in");
	int n, m;
	while(cin >> n >> m) {
		for(int i = 1; i <= n; ++ i) {
			e[i].clear();
			in[i] = 0;
		}
		for(int i = 0; i < m; ++ i) {
			int a, b;
			cin >> a >> b;
			e[b].push_back(a);
			in[a] ++;
		}
		topSort(n);
	}
	return 0;
}