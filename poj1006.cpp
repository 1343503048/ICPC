#include <iostream>
#include <fstream>
using namespace std;

int exgcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	int ans = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return ans;
}

int main(int argc, char const *argv[]) {
	//ifstream cin("data.in");
	int p, e, i, d, cnt = 1, x, y;
	while(cin >> p >> e >> i >> d && p != -1) {
		int MI = 23 * 28 * 33;
		exgcd(MI / 23, 23, x, y);		//x为逆元
		int a = x;
		exgcd(MI / 28, 28, x, y);
		int b = x;
		exgcd(MI / 33, 33, x, y);
		int c = x;
		d = (MI * a / 23 * p + MI * b / 28 * e + MI * c / 33 * i - d + 21252) % 21252;
		if(d <= 0) {
			d += 21252;
		}
		cout << "Case " << cnt ++ << ": the next triple peak occurs in " << d << " days."  << endl;
	}
	return 0;
}