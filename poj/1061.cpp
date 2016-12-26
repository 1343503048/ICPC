#include <iostream>
using namespace std;
typedef long long ll;

int extend_gcd(ll m, ll n, ll &a, ll &b){
	if(b == 0) {
		x = 1; 
		y = 0;
		return a;
	}
	int d = extend_gcd(n, m % n, a, b);
	ll temp = a;
	a = b;
	b = temp - m / n * b;
	return d;
}

int main(){
	ll x, y, m, n, l;
	while (cin >> x >> y >> m >> n >> l) {
			
	}
	return 0;
}