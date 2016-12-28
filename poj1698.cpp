//此问题为求二分图的多重匹配
//将其转化为求最大流问题，用EK算法求解
//s = 0为源点， t = 371为汇点
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;
const int MAX = 370+5;

struct node {	
	int to, w, rev;
	node(int _to, int _w, int _rev) : to(_to), w(_w), rev(_rev){}
};

vector<node> e[MAX];
bool vis[MAX];

void addEdge(int from, int to, int w){
	e[from].push_back(node(to, w, e[to].size()));
	e[to].push_back(node(from, 0, e[from].size()-1));
}

int dfs(int s, int t, int f){
	if(s == t) {
		return f;
	}
	vis[s] = true;
	for(size_t i = 0; i < e[s].size(); ++ i) {
		node &temp = e[s][i];			//使用引用
		if(!vis[temp.to] && temp.w > 0) {
			int d = dfs(temp.to, t, min(temp.w, f));
			if(d > 0) {
				temp.w -= d;
				e[temp.to][temp.rev].w += d;
				return d;
			}
		}
	}
	return 0;
}

int EK(int n) {
	int ans = 0;
	int f;
	do{
		memset(vis, false, sizeof(vis));
		f = dfs(0, n, INT_MAX);
		ans += f;
	}while(f > 0);
	//cout << ans << endl;
	return ans;
}

int main(){
	//ifstream cin("data.in");
	int t;
	cin >> t;
	while(t --) {
		int n;
		cin >> n;
		int d = 0, w, temp;
		int data[10]; 
		for(int i = 1; i <= n; ++ i) {
			int sum = 0;
			for(int j = 1; j <= 7; ++ j) {
				cin >> data[j];
				sum += data[j];
			}
			cin >> temp >> w;
			d += temp;
			addEdge(0, i, temp);			//源点到各电影间的流量为各电影所需要的时间
			for(int j = 0; j < w; ++ j) {
				for(int k = 1; k <= 7; ++ k) {
					if(data[k]){
						addEdge(i, n+j*7+k, 1);
					}
				}
			}
		}
		for(int i = n+1; i <= 370; ++ i) {
			addEdge(i, 371, 1);
		}
		if(EK(371) == d) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
		for(int i = 0; i <= 371; ++ i) {
			e[i].clear();
		}
	}
	return 0;
}
