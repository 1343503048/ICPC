//c++ 
//accepted
//312Ms

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <cstring>
using namespace std;

struct node {
	int cnt;
	node *fail, *next[130];//字符很多，注意不能仅用26
};

node memory[500000];		//动态建树需要释放内存，所以采用静态建树
char key[205], s[10005];
node *root;
int c;

void insert(int num) {
	int id, l = strlen(key);
	node *cur = root;
	for(int i = 0; i < l; ++ i) {
		id = (int)key[i];
		if(cur->next[id] == NULL) {
			cur->next[id] = &memory[c++];
		}
		cur = cur->next[id];
	}
	cur->cnt = num;
}

void build() {
	queue<node *> Q;
	Q.push(root);
	while(!Q.empty()) {
		node *cur = Q.front();
		Q.pop();
		for(int i = 0; i < 130; ++ i) {
			if(cur->next[i] != NULL){
				if(cur == root) {
					cur->next[i]->fail = root;
				}
				else {
					node *temp = cur->fail;
					while(temp != NULL) {
						if(temp->next[i] != NULL) {
							cur->next[i]->fail = temp->next[i];
							break;
						}
						temp = temp->fail;
					}
					if(temp == NULL) {
						cur->next[i]->fail = root;
					}
				}
				Q.push(cur->next[i]);
			}
		}
	}
}

int query(int num) {
	set<int> v;
	node *cur = root;
	int id, l = strlen(s);
	for (int i = 0; i < l; ++ i) {
		id = (int)s[i];
		while (cur->next[id] == NULL && cur != root) {
			cur = cur->fail;
		}
		cur = cur->next[id];
		if(cur == NULL) {
			cur = root;
		}
		node *temp = cur;
		while(temp != root) {
			if(temp->cnt > 0) {
				v.insert(temp->cnt);
			}
			temp = temp->fail;
		}
	}
	if(v.size() != 0) {
		cout << "web " << num << ":";
		for(set<int>::iterator it = v.begin(); it != v.end(); ++ it) {
			cout << " " << *it;
		}
		cout << endl;
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	// ifstream cin("data.in");
	int n, m;
	while(cin >> n) {
		c = 0;
		root = &memory[c++];
		int ans = 0;
		for(int i = 1; i <= n; ++ i) {
			cin >> key;
			insert(i);
		}
		build();
		cin >> m;
		for(int i = 1; i <= m; ++ i) {
			cin >> s;
			ans += query(i);
		}
		cout << "total: " << ans << endl;
		for(int i = 0; i < c; ++ i) {
			memory[i].cnt = 0;
			memory[i].fail = NULL;
			for(int i = 0; i < 130; ++ i){
				memory[i].next[i] = NULL;
			}
		}
	}
	return 0;
}