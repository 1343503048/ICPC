#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int matrix[55][55];

int main() {
	std::ios::sync_with_stdio(false);
	std::ciitn.tie(0);
	ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		int n, m;
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < m; j ++) {
				cin >> matrix[i][j];
			}
		}
	}
	return 0;
}