#include <bits/stdc++.h>
using namespace std;
char p[1005], s[1005];
int Next[1005], pl, sl;

void cal_next() {
	int i, j;
	Next[0] = -1;
	for(int i = 1; i < pl; ++ i) {
		int j = Next[i-1];
		while(p[j+1] != p[i] && (j >= 0)) {
			j = Next[j];
		}
		if(p[i] == p[j+1]) {
			Next[i] = j + 1;
		}
		else {
			Next[i] = -1;
		}
	}
}

int kmp() {
	int ans = 0, si = 0, pi = 0;
	while(si < sl && pi < pl) {
		if(s[si] == p[pi]) {
			si ++;
			pi ++;
			if(pi == pl) {
				ans ++ ;
				pi = 0;
			}
		}
		else {
			if(pi == 0) {
				si ++;
			}
			else {
				pi = Next[pi-1] + 1;
			}
		}
	}
	return ans;
}

int main(int argc, char const *argv[]) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	while(cin >> s && s[0] != '#') {
		cin >> p;
		pl = strlen(p);
		sl = strlen(s);
		cal_next();
		cout << kmp() << endl;
	}
	return 0;
}