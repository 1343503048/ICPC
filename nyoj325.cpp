#include <iostream>
#include <cstring>
using namespace std;
int dp[10005];
int w[30];

#include <cstring>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while(cin >> n) {
	int v, s = 0;
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n; ++ i){
	    cin >> w[i];
	    s += w[i];
	}
	v = s >> 1;
	for(int i = 0; i < n; ++ i) {
	    for(int j = v; j >= w[i]; -- j) {
		dp[j] = dp[j] > dp[j-w[i]] + w[i] ? dp[j] : dp[j-w[i]]+w[i];
	    }
	}

	cout << s - 2 * dp[v] << "\n";
    }
    return 0;
}
