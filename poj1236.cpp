#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
const int N = 100+5;

vector<int> e[N];
bool vis[N];
int dnf[N], in[N], out[N], scc[N], low[N];
int t, ans;
stack<int> s;

void tarjan(int v) {
	dnf[v] = low[v] = t ++;
	vis[v] = true;
	s.push(v);
	for(size_t i = 0; i < e[v].size(); ++ i) {
		int to = e[v][i];
		if(dnf[to] == -1) {
			tarjan(to);
			low[v] = min(low[to], low[v]);
		}
		else if(vis[to]) {
			low[v] = min(low[v], dnf[to]);
		}
	}
	if(low[v] == dnf[v]) {
		int j;
		do{
			j = s.top();
			vis[j] = false;
			s.pop();
			scc[j] = ans;
		}while(j != v);
		ans ++;
	}
}

int main(){
    // ifstream cin("data.in");
    int n;
    while(cin >> n) {
    	memset(dnf, -1, sizeof(dnf));
    	memset(vis, false,sizeof(vis));
    	memset(in, 0, sizeof(in));
    	memset(out, 0, sizeof(out));
        for(int i = 1; i <= n; ++ i) {
    		int a;
    		while(cin >> a && a != 0){
    			e[i].push_back(a);
    		}
    	}
        ans = t = 0;
    	for(int i = 1; i <= n; ++ i) {
    		if(dnf[i] == -1) {
    	        tarjan(i);
    		}
    	}
        for(int i = 1; i <= n; ++ i) {
        	for(size_t j = 0; j < e[i].size(); ++ j) {
        		int to = e[i][j];
        		if(scc[i] != scc[to]) {
        			in[scc[to]] ++;
        			out[scc[i]] ++;
        		}
        	}
        	e[i].clear();
        }
        if(ans == 1) {
        	cout << "1\n0" << endl;		//!!!
        	continue;
        }
        int c1 = 0, c2 = 0;
        for(int i = 0; i < ans; ++ i) {
        	c1 += (in[i] == 0);
        	c2 += (out[i] == 0);
        }
        cout << c1 << "\n" << max(c1, c2) << endl;
    }
    return 0;
}
