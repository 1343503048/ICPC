#include <bits/stdc++.h>
using namespace std;
const int N = 100000+5;

int loc[N];

void update(int x, int d) {
	while(x < N) {
		loc[x] += d;
		x += x&(-x);
	}
}

int query(int x) {
	int ans = 0;
	while(x > 0) {
		ans += loc[x];
		x -= x & (-x);
	}
	return ans;
}

int main(){
	ifstream cin("data.in");
	int n;
	while(cin >> n && n != 0) {
		memset(loc, 0, sizeof(loc));
		for(int i = 0; i < n; ++ i) {
			int a, b;
			cin >> a >> b;
			update(a, 1);
			update(b+1, -1);
		}
		for(int i = 1; i <= n; ++ i) {
			if(i > 1) {
				cout << " ";
			}
			cout << query(i);
		}
		cout << endl;
	}
	return 0;
}