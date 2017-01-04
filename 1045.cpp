#include <iostream>
#include <fstream>
using namespace std;
const int go[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};

int map[5][5], n;
int num;

bool ok(int x, int y) {
	if(map[x][y] != 0) {
		return false;
	}
	for(int i = 0; i < 4; ++ i) {
		int a = x + go[i][0], b = y + go[i][1];
		while(a >= 0 && a < n && b >= 0 && b < n) {
			if(map[a][b] == 2) {
				return false;
			}
			if(map[a][b] == 1) {
				break;
			}
			a += go[i][0];
			b += go[i][1]; 
		}	
	}
	return true;
}

void dfs(int x, int y, int k) {
	if(x == n) {
		num = max(num, k);
		return;
	}
	if(y + 1 == n) {
		dfs(x + 1, 0, k);
	}
	else {
		dfs(x, y + 1, k);
	}
	if(ok(x, y)) {
		map[x][y] = 2;
		if(y + 1 == n) {
			dfs(x+1, 0, k + 1);
		}
		else {
			dfs(x, y + 1, k + 1);
		}
		map[x][y] = 0;
	}
}

int main() {
	ifstream cin("data.in");
	while(cin >> n && n != 0) {
		for(int i = 0; i < n; ++ i) {
			for(int j = 0; j < n; ++ j) {
				char c;
				cin >> c;
				map[i][j] = (c == 'X');
			}
		}
		num = 0;
		dfs(0, 0, 0);
		cout << num << endl;
	}
	return 0;
}