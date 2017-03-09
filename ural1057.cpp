#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

int digit[30];
int k;
ll dp[40][20][25];

ll dfs(int pos, int num, int b, bool inf) {			//inf用来判断是否沿n的路径遍历
		if(pos == -1) {
				return num == k;
		}
		if(num > k) {
				return 0;
		}
		if(!inf && dp[pos][num][b] != -1) {
				return dp[pos][num][b];
		}
		int end = inf ? min(1, digit[pos]) : 1;
		int ans = dfs(pos-1, num, b, inf && digit[pos] == 0);
		if(end == 1) {
		     ans += dfs(pos-1, num+1, b, inf && digit[pos] == 1);
		}	
		if(!inf)   //当沿n的路经便利时可能存在只遍历一颗子树的情况
		    dp[pos][num][b] = ans;
		return ans;
}

ll calu(int t, int b) {
	int pos = 0;
	while(t) {
			digit[pos++] = t % b;
			t /= b;
	}
	return dfs(pos-1, 0, b, true);
}

int main() {
		int x, y, b;
		memset(dp, -1, sizeof(dp));
		while(cin >> x >> y >> k >> b) {
				cout << calu(y, b) - calu(x-1, b) << endl;
		}
		return 0;
}
