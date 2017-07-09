
/*************************************************

       Filename: 5451.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-07-08 15:55:18
    Description: 快速幂 & 广义Fibonacci数列

*************************************************/

// (5 + 2 * sqrt(6)) ^ n = xn + yn * sqrt(6);
// (5 - 2 * sqrt(6)) ^ n = xn - yn * sqrt(6) == (0.101) ^ n;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1024;

struct Mat{
    ll val[2][2];
    Mat(int a, int b, int c, int d) {
	val[0][0] = a;
	val[0][1] = b;
	val[1][0] = c;
	val[1][1] = d;
    }
};

Mat mulity(Mat a, Mat b) {
    Mat c(0, 0, 0, 0);
    for(int i = 0; i < 2; ++ i) {
	for(int j = 0; j < 2; ++ j) {
	    for(int k = 0; k < 2; ++ k) {
		c.val[i][j] += a.val[i][k] * b.val[k][j];
		c.val[i][j] %= mod;
	    }
	}
    }
    return c;
}

Mat _pow(Mat a, int n) {
    Mat res(1, 0, 0, 1);
    while(n) {
	if(n&1) res = mulity(res, a);
	n >>= 1;
	a = mulity(a, a);
    }
    return res;
}

ll _pow(ll n, ll x, ll mod) {
    ll res = 1;
    while(x) {
	if(x & 1) res = res * n % mod;
	x >>= 1;
	n = n * n % mod;
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    for(int t = 1; t <= T; ++ t) {
	int n;
	cin >> n >> mod;
	Mat k(5, 12, 2, 5);
	n = _pow(2, n, mod * mod - 1) + 1;			// fibo循环节为(mod ^ 1 - 1);
	k = _pow(k, n-1);
	ll xn = 5 * k.val[0][0] + 2 * k.val[0][1];
	ll res = (2 * xn - 1) % mod;
	cout << "Case #" << t << ": " << res << "\n";
    }
    return 0;
}

