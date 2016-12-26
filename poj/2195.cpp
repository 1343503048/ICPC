#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 105;
const int INF = 10000;

int x[MAX], y[MAX];

int num[MAX][MAX];
int lx[MAX], ly[MAX], linky[MAX];
bool visx[MAX], visy[MAX];
int slack[MAX];
int mp[MAX][MAX];
int n, cnt;

bool dfs(int x) {
	int y, d;
	visx[x] = true;
	for(int i = 0; i < cnt; ++ i) {
		d = lx[x] + ly[i] - mp[x][y];
		if(d == 0 && !visy[i]) {
			visy[i] = true;
			if(linky[i] == -1 || dfs(linky[i])) {
				linky[i] = x;
				return true;
			}
		}
		else {
			slack[i] = min(slack[i], d);
		}
	}
	return false;
}

void KM() {
	for(int i = 0; i < cnt; ++ i) {
		ly[i] = 0;
		linky[i] = -1;
		lx[i] = -INF;
		for(int j = 0; j < cnt; j ++) {
			lx[i] = max(lx[i], mp[i][j]);
		}
	}
	for(int i = 0; i < cnt; ++ i) {
		memset(visy, false, sizeof(visy));
		memset(visx, false, sizeof(visx));
		for(int j = 0; j < cnt; j ++) {
			slack[j] = INF;
		}
		while(!dfs(i)) {
			int d = INF;
			for(int k = 0; k < cnt; k ++) {
				if(!visy[k]) {
					d = min(d, slack[k]);
				}
			}
			for(int k = 0; k < cnt; k ++) {
				if(visx[k]) {
					visx[k] = false;
					lx[k] -= d;
				}
				if(visy[k]) {
					visy[k] = false;
					ly[k] += d;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < cnt; ++ i) {
		ans += lx[i] + ly[i];
	}
	cout << ans / 2 << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	ifstream cin("data.in");
	int m;
	while(cin >> n >> m && (n != 0 || m != 0)) {
		char s[105][105];
		cnt = 0;
		for(int i = 0; i < n; ++ i)  {
			cin >> s[i];
			for(int j = 0; j < m; j ++) {
				if(s[i][j] == 'H') {
					x[cnt] = i;
					y[cnt] = j;
					cnt ++;
				}
			}
		}
		int l = cnt;
		for(int i = 0; i < n; ++ i)  {
			for(int j = 0; j < m; j ++) {
				if(s[i][j] == 'm') {
					x[cnt] = i;
					y[cnt] = j;
					cnt ++;
				}
			}
		}
		for(int i = 0; i < cnt; i ++) {
			for(int j = 0; j < cnt; j ++) {
				mp[i][j] = -INF;
			}
		}
		for(int i = 0; i < l; i ++) {
			for(int j = l; j < cnt; ++ j) {
				mp[i][j] = mp[j][i] = -(abs(x[i]-x[j]) + abs(y[i]-y[i]));
			}
		}
		KM();
	}
	return 0;
}