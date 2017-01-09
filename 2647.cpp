//TopSort
#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000+15;

vector<int> e[MAX];
int in[MAX], money[MAX]; //jilujiangjin

void topSort(int n) {
	queue<int> Q;	//注意此处使用队列，因为是求最小值，所以只有当排在叫前面的点出队时才能让一个值竟可能的小
	//比如有1--->3、2-->4 和 3--->4三个条件,如果用栈的话4会为3的等级+1，假设1为888,那么显然3
	//为889,而2为888，那么此时4就为890;如果用队列的话4就是889；
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
