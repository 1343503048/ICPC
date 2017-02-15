#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int N = 100+5;

int p, n;
int matrix[N][N], ans[N];
char s[N];

void init() {
	int i, j, k;
	for(i = 0; i < n; ++ i) {
		if(s[i] == '*') {
			matrix[i][n] = 0;
		}
		else {
			matrix[i][n] = s[i] - 'a' + 1;
		}
	}

	for(i = 0; i < n; ++ i) {
		k = 1;
		for(j = 0; j < n; ++ j) {
			matrix[i][j] = k;
			k = (k * (i + 1)) % p;
		}
	}
}

int find(int a, int y, int p = 1000007) {
	a = (a%p + p) % p;
	y = (y%p + p) % p;
	for(int i = 0; i < p; ++ i) {
		if((a*i)%p == y) {
			return i;
		}
	}
}

void gauss(int p = 100007) {
	int i, j, k, row = 0, col = 0;
	int a, b, c, sum;
	while(row < n && col < n) {
		for(i = row, j = -1; i < n; ++ i) {
			if(matrix[i][col] != 0) {
				j = i;
				break;
			}
		}

		for(i = col; i < n; ++ i) {
			k = matrix[row][i];
			matrix[row][i] = matrix[j][i];
			matrix[j][i] = k;
		}

		a = matrix[row][col];

		for(i = row+1; i < n; ++ i) {
			b = matrix[i][col];
			for(j = col; j <= n; ++ j) {
				matrix[i][j] = (matrix[i][j] * a - matrix[row][j] * b) % p;
			}
		}
		row ++;
		col ++;
	}

	for(i = n-1; i >= 0; i --) {
		sum = 0;
		for(j = i + 1; j < n; ++ j) {
			sum = (sum + matrix[i][j] * ans[j]) % p;
		}
		ans[i] = find(matrix[i][i], matrix[i][n]-sum, p);
	}

	for(i = 0; i < n; ++ i) {
		if(i > 0) {
			cout << " ";
		}
		cout << ans[i];
	}
	cout << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		cin >> p >> s;
		n = strlen(s);
		init();
		gauss(p);
	}
	return 0;
}