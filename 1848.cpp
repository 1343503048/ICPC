#include <bits/stdc++.h>
using namespace std;
const int N = 1000+5;
std::vector<int> v;
int sg[N];


int getSg(int x) {
	if(sg[x] != -1) {
		return sg[x];
	}
	bool vis[N];
	memset(vis, false, sizeof(vis));
	for(int i = 0; i < v.size(); ++ i) {
		if(v[i] <= x) 
			vis[getSg(x-v[i])] = true;
	}
	for(int i = 0; ; ++ i) {
		if(!vis[i]) {
			return sg[x] = i;
		}
	}
}

int main() {
	v.push_back(1);
	v.push_back(2);
	while(1) {
		int a = v[v.size()-1] + v[v.size()-2];
		if(a > 1000) {
			break;
		}
		v.push_back(a);
	}
	// ifstream cin("data.in");
	int n, m, p;
	while(cin >> n >> m >> p && n) {
		memset(sg, -1, sizeof(sg));
		int ans = getSg(n) ^ getSg(m) ^ getSg(p);
		if(ans == 0) {
			puts("Nacci");
		}
		else {
			puts("Fibo");
		}
	}
	return 0;
}