#include <iostream>
using namespace std;

int f[11][11];

int main() {
	for(int i = 1; i < 11; i ++) {
		for(int j = 1; j < 11; ++ j) {
			if(j == 1 || i == 1) {
				f[i][j] = 1;
			}
			else if(i == j) {
				f[i][j] = 1 + f[i][i-1];
			}
			else if(i < j) {
				f[i][j] = f[i][i];
			}
			else if(i > j) {
				f[i][j] = f[i][j-1] + f[i-j][j];
			}
		}
	}
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		cout << f[n][m] << endl;
	}
	return 0;
}