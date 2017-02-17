#include <bits/stdc++.h>
using namespace std;
const int N = 100000+5;
int f[N];

struct Node {
	int l, r, dist, val, dad;
};

Node node[N];

int merge(int u, int v) {
	if(!u) return v;
	if(!v) return u;
	if(node[u].val < node[v].val) {
		swap(u, v);
	}
	node[u].r = merge(node[u].r, v);
	node[node[u].r].dad = u;
	if(node[node[u].l].dist < node[node[u].r].dist) {
		swap(node[u].l, node[u].r);
	}
	if(node[u].r == 0) {
		node[u].dist = 0;  //距离为右子树的距离家1，当右子树为空时dist=0.	
	}
	else {
		node[u].dist = node[node[u].r].dist + 1;
	}
	return u;
}

int find(int x) {		   //寻找根
	if(node[x].dad != x) {
		node[x].dad = find(node[x].dad);
	}
	return node[x].dad;
}

int pop(int x) {
	int l = node[x].l;
	int r = node[x].r;
	node[l].dad = l;
	node[r].dad = r;
	node[x].l = node[x].r = node[x].dist = 0;
	return merge(l, r);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	int n, m, a, b;
	while(cin >> n) {
		for(int i = 1; i <= n; ++ i) {
			cin >> node[i].val;
			node[i].dad = i;
			node[i].r = node[i].l = node[i].dist = 0;
		}
		cin >> m;
		while(m --) {
			cin >> a >> b;
			int x = find(a), y = find(b);
			if(x == y) {
				cout << "-1" << endl;
			}
			else {
				node[x].val /= 2;
				int xx = merge(pop(x), x);
				node[y].val /= 2;
				int yy = merge(pop(y), y);
				cout << node[merge(xx, yy)].val << endl;
			}
		}
	}
	return 0;
}
