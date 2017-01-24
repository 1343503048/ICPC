#include <iostream>
#include <cstring>
using namespace std;

char key[10005], s[1000005];
int Next[10005];

void make_Next() {
	int i, j, l = strlen(key);
	Next[0] = -1;
	for (int i = 1; i < l; ++ i) {
		j = Next[i-1];
		while(key[j+1] != key[i] && (j >= 0)) {
			j = Next[j];
		}
		if(key[i] == key[j+1]) {
			Next[i] = j + 1;
		}
		else {
			Next[i] = -1;
		}
	}
}

int query() {
	int si = 0, pi = 0, sl = strlen(s), pl = strlen(key);
	int ans = 0;
	while(si < sl && pi < pl) {
		if(s[si] == key[pi]) {
			si ++;
			pi ++;
			if(pi == pl) {
				ans ++;
				pi = Next[pi-1] + 1;
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		cin >> key >> s;
		memset(Next, 0, sizeof(Next));
		make_Next();
		cout << query() << endl;
	}
	return 0;
}