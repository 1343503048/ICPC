#include <bits/stdc++.h>
using namespace std;
const int MAX = 30000+5;

int f[MAX], num[MAX], dist[MAX];

int find(int x) {
	if(f[x] == x) {
		return f[x];
	}
	int temp = f[x];
	f[x] = find(f[x]);
	dist[x] += dist[temp];
	return f[x];
}

void merge(int x, int y) {
	int x0 = find(x);
	int y0 = find(y);
	if(x0 != y0) {
		dist[x0] += num[y0];
		num[y0] += num[x0];
		f[x0] = y0;
	}
}

int main(){
	long long p;
	//ifstream cin("data.in");
	while(cin >> p) {
		for(int i = 0; i < MAX; ++ i) {
			f[i] = i;
			dist[i] = 0;
			num[i] = 1;
		}
		while(p --) {
			char ch;
			int a, b;
			cin >> ch;
			if(ch == 'C') {
				cin >> a;
				cout << dist[a] << endl;
			}
			else {
				cin >> a >> b;
				merge(a, b);
			}
		}
	}
	return 0;
}