//删边游戏（anti-SG）
//1.叶子节点的sg值为0，中间节点的sg值为它的所有节点的sg值加1后的异或
//2.ANTI-SG:先手必胜当且仅当：
//（1）游戏的SG函数不为0且游戏中某个单一游戏的SG函数大于1；
//（2）游戏的SG函数为0且游戏中没有单一游戏的SG函数大于1。
#include <bits/stdc++.h>
using namespace std;
std::vector<int> e[105];

int sg[105];
bool vis[105];

int getSg(int x) {
	if(sg[x] != -1) {
		return sg[x];
	}
	vis[x] = true;
	sg[x] = 0;
	for(size_t i = 0; i < e[x].size(); ++ i) {
		int to = e[x][i];
		if(!vis[to]){
			sg[x] ^= getSg(to) + 1;
		}
	}
	return sg[x];
}

int main() {
	// ifstream cin("data.in");
	int n, m, a, b;
	while(cin >> n) {
		int ans = 0, cnt = 0;;
		while(n --) {
			memset(sg, -1, sizeof(sg));
			memset(vis, false, sizeof(vis));
			cin >> m;
			for(int i = 1; i <= m; ++ i) {
				e[i].clear();
			}
			for(int i = 1; i < m; ++ i) {
				cin >> a >> b;
				e[a].push_back(b);
				e[b].push_back(a);
			}
			int t = getSg(1);
			ans ^= t;
			if(t > 1) {
				cnt ++;
			}
		}
		if((ans == 0 && cnt == 0) || (ans != 0 && cnt > 0)) {
			cout << "PP" << endl;
		}
		else {
			cout << "QQ" << endl;
		}
	}
	return 0;
}