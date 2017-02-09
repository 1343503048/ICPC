#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;

bool isPrime[66000];

void judgePrime() {
	memset(isPrime, false, sizeof(isPrime));
	int sq = sqrt(65010+0.5);
	isPrime[0] = isPrime[1] = true;
	for(int i = 2; i <= sq; ++ i) {
		if(!isPrime[i]) {
			for(int j = i * i; j < 65005; j += i) {
				isPrime[j] = true;
			}
		}
	}
}

ll pow_mod(ll x, ll n, ll mod) {
	ll res = 1;
	while(n > 0) {
		if( n & 1 ) {
			res = (res * x) % mod;
		}
		x = (x * x) % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	// ifstream cin("data.in");
	ll n;
	judgePrime();
	while(cin >> n && n) {
		if(!isPrime[n]) {
			cout << n << " is normal." << endl;
			continue;
		}
		bool ok = true;
		for(ll i = 2; i < n; ++ i) {
			if(i != pow_mod(i, n, n)) {
				ok = false;
				break;
			}
		}
		if(ok) {
			cout << "The number " << n << " is a Carmichael number." << endl;
		}
		else {
			cout << n << " is normal." << endl;
		}
	}
	return 0;
}