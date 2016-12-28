//hungary
#include <bits/stdc++.h>
using namespace std;

int match[105], check[105];
vector<int> e[105];
int m[105][105];
bool color[55];

int find(int v){
	for(size_t i = 0; i < e[v].size(); ++ i){
		int to = e[v][i];
		if(check[to]) continue;
		check[to] = true;
		if(match[to] == -1 || find(match[to])){
			match[to] = v;
			return 1;
		}
	}
	return 0;
}

int hungary(int n){
	memset(match, -1, sizeof(match));
	int ans = 0;
	for(int i = 0; i < n; ++ i){
		memset(check, false, sizeof(check));
		ans += find(i);
	}
	return ans;
}

int main(){
	//ifstream cin("data.in");
	int n, k;
	while(cin >> n >> k && (n || k)){
		memset(color, false, sizeof(color));
		for(int i = 0; i < n; ++ i){
			for(int j = 0; j < n; ++ j){
				cin >> m[i][j];
				color[m[i][j]] = true;
			}
		}
		bool ok = true;
		for(int f = 1; f <= 50; ++ f){
			if(color[f]){
				for(int i = 0; i < n; ++ i){
					e[i].clear();
					for(int j = 0; j < n; ++ j){
						if(m[i][j] == f){
							e[i].push_back(j);
						}
					}
				}
				if(hungary(n) > k){
					if(ok){
						cout << f;
						ok = false;
					}
					else {
						cout << " " << f;
					}
				}
			}
		}
		if(ok){
			cout << "-1";
		}
		cout << endl;
	}
	return 0;
}
