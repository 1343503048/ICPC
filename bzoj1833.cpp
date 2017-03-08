#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

ll p[20];
ll num[10];

void init() {
		p[0] = 1;
		for(int i = 1; i < 18; ++ i) {
			p[i] = p[i-1] * 10;
		}
}

void slove(ll n, ll f) {
		if(n == -1) { //当ｎ为0时函数后面部分无法统计统计
			num[0] ++;
			return ;
		}	
		for(int k = 1; k < 10; ++ k) {
				for(int i = 1; ; ++ i) {
						ll l = n / p[i];
						ll r = n % p[i-1];
						ll now = n % p[i] / p[i-1];
						if(now > k) {			//当前位大于k时,前面取值为0-l;
							num[k] += (l+1) * p[i-1] * f; 
						}
						else if(now == k) {    //当前小于等于ｋ时,前面取值0 - l-1;
							num[k] += (l * p[i-1] + r + 1)*f;
						}
						else {                
							num[k] += l * p[i-1] * f;
						}
						if(p[i] > n) {
								break;
						}
				}
		}
		for(int i = 1; ; ++ i) {		//当某一位取0时，前面部分不能为0，只能为1-l;
				ll l = n / p[i];
				ll r = n % p[i-1];
				ll now = n % p[i] / p[i-1];
				if(now > 0) {
						num[0] += l * p[i-1] * f;
				}
				else {
						num[0] += ((l-1)*p[i-1] + r + 1) * f;
				}
				if(p[i] > n) {
						break;
				}
		}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ll n, m;
	init();
    cin >> n >> m;
    slove(m, 1);
	slove(n-1, -1);
	for(int i = 0; i <= 9; ++ i) {
			if(i) {
					cout << " ";
			}
			cout << num[i];
	}
	cout << endl;
		return 0;
}


