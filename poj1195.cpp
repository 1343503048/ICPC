#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
using namespace std;
const int N = 1030;

int sum[N][N];

int getSum(int i, int j) {
	int t, s = 0;
	while(i > 0) {
		t = j;
		while(t > 0) {
			s += sum[i][t];
			t -= t & -t;
		}
		i -= i & -i;
	}
	return s;
}

void update(int i, int j, int val) {
	while(i < N) {
		int t = j;
		while(t < N) {
			sum[i][t] += val;
			t += t & -t;
		}
		i += i & -i;
	}
}

int main(int argc, char const *argv[]) {
	// freopen("data.in", "r", stdin);
	int n, m;
	while(~scanf("%d%d", &n, &m)) {
		memset(sum, 0, sizeof(sum));
		int temp, x, y, i, j;
		while(scanf("%d", &temp) && temp != 3) {

			if(temp == 1) {
				scanf("%d%d%d", &x, &y, &i);
				x ++;
				y ++;
				update(x, y, i);
			}
			else {
				scanf("%d%d%d%d", &x, &y, &i, &j);
				x ++, y++, i ++, j ++;
				int ans = getSum(i, j) - getSum(x-1, j) - getSum(i, y - 1) + getSum(x-1, y -1);
				printf("%d\n", ans);
			}
		}

	}
	return 0;
}