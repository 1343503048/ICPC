#include <iostream>
#include <cstring>
using namespace std;
int s[35662];

int main() {
	int n;
	while(cin >> n) {
		memset(s, 0, sizeof(s));
		s[0] = s[1] = 1;
		for(int i = 2; i <= n; ++ i) {
			for(int j = 1; j <= s[0]; ++ j) {
				s[j] *= i;
			}
			for(int j = 1; j <= s[0]; ++ j) {
				s[j+1] += s[j]/10;
				s[j] %= 10;
				if(s[s[0]+1]) {
					s[0] ++;
				}
			}
		}
		for(int i = s[0]; i > 0; -- i) {
			cout << s[i];
		}
		cout << "\n";
	}
	return 0;
}