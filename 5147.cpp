//树状数组
//对于每一个位置上的数,首先求出在他之前且比他要小的数的个数，即能和他组成二元组的个数
//然后求出在他之后能形成二元组的对数，然后将两数想乘即为当b为该位置时能形成四元组的数目，
//然后逐一列举即可得到结果
#include <bits/stdc++.h>
using namespace std;
const int N = 60000+5;

long long up[N], lower[N];
int sum[N], val[N];
int n;

int getSum(int x) {
	int ans = 0;
	while(x > 0) {
		ans += sum[x];
		x -= (x & (-x));
	}
	return ans;
}

void update(int x, int d) {
	while(x <= n) {
		sum[x] += d;
		x += (x & (-x));
	}
}

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		long long ans = 0;
		cin >> n;
		memset(up, 0, sizeof(up));
		memset(lower, 0, sizeof(lower));
		memset(sum, 0, sizeof(sum));
		for(int i = 1; i <= n; ++ i) {
			cin >> val[i];
			lower[i] = getSum(val[i]);		//比val[i]小且在i之前的数的个数
			update(val[i], 1);
		}
		memset(sum, 0, sizeof(sum));
		for(int i = n; i >= 1; -- i) {
			up[i] = getSum(n) - getSum(val[i]) + up[i+1];	//i之后能形成二元组的对数
			update(val[i], 1);
		}
		for(int i = 2; i <= n-2; ++ i) {
			long long a = up[i+1];
			long long b = lower[i];	
			ans += a * b;	//相乘得到结果
		}
		cout << ans << endl;
	}
	return 0;
}
