#include <bits/stdc++.h>
using namespace std;
const int N = 110000+5;
char s[N];
char str[N<<1];
int p[N<<1];

int manacher() {
	int len = strlen(s);
	int l = 0;
	str[l++] = '@';
	str[l++] = '#';
	for(int i = 0; i < len; ++ i) {
		str[l++] = s[i];
		str[l++] = '#';
	}
	str[l] = 0;
	int mx = 0, id = 0;
	int ans = 0;
	for(int i = 0; i < l; ++ i) {
		if(mx > i) {
			p[i] = min(p[2*id-i], mx-i);
		}
		else {
			p[i] = 1;
		}
		while(str[i+p[i]] == str[i-p[i]]) {
			p[i] ++;
		}
		if(i + p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
		ans = max(ans, p[i]-1);
	}
	return ans;
}

int main(int argc, char const *argv[]) {
	while(~scanf("%s", s)) {
		printf("%d\n", manacher());
	}	
	return 0;
}