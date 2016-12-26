#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAXN = 30000+5;
const int MAXM = 500+5;

int f[MAXN], num[MAXN];

int find(int x) {
	if(f[x] != x) {
		f[x] = find(f[x]);
	}
	return f[x];
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x < y) {
		f[y] = x;
		num[x] += num[y];
	}
	else if(x > y) {
		f[x] = y;
		num[y] += num[x];
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//ifstream cin("data.in");
	int n, m;
	while(cin >> n >> m && (n != 0 || m != 0)) {
		for(int i = 0; i < n; ++ i) {
			f[i] = i;
			num[i] = 1;
		}
		while (m --){
			int k;
			cin >> k;
			int fisrt, temp;
			cin >> fisrt;
			for(int i = 1; i < k ; ++ i) {
				cin >> temp;
				merge(fisrt, temp);
			}
		}
		cout << num[0] << endl;
	}
	return 0;
}