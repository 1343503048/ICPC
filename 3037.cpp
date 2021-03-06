#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f[100005];

void init(int p){
	f[0] = 1;
	for(int i = 1; i < p; ++ i) {
		f[i] = (f[i-1] * i) % p;
	}
}

ll pow_mod(ll x, ll n, ll p) {
	ll ans = 1;
	while(n) {
		if(n & 1) {
			ans = (ans * x) % p;
		}
		x = (x * x) % p;
		n >>= 1;
	}
	return ans;
}

ll com(ll n, ll m, ll p) {
	if(n < m) {
		return 0;
	}
	// c(n, m) = n! / ((n-m)! * m!)  
	// 然后求((n-m)!*m!)的逆元
	return (f[n] * pow_mod((f[n-m] * f[m])%p, p-2, p)) % p; //x^(p-1) = 1(modp) = x * x ^(p-2) = 1(modp)
}

ll lucas(ll n, ll m, ll p) {
	if(m == 0) {
		return 1;
	}
	return (com(n%p, m%p, p) * lucas(n/p, m/p, p)) % p;
}

int main() {
	int t;
	ll n, m, p;
	cin >> t;
	while(t --) {
		cin >> n >> m >> p;
		init(p);
		cout << lucas(n+m, m, p) << endl;
	}
	return 0;
}
