#include <bits/stdc++.h>
using namespace std;

struct node {
	int cnt;
	node* next[26];
	node(){
		cnt = 0;
		memset(next, 0, sizeof(next));
	}
};

char s[1000005], p[55];

void build(node *root, char *p) {
	int l = strlen(p), id;
	node *cur = root;
	for(int i = 0; i < l; ++ i) {
		id = p[i] - 'a';
		if(cur->next[id] == NULL) {
			cur->next[id] = new node();
		}
		cur = cur->next[id];
	}
	cur->cnt ++;
}

int query(node *root, char *p) {
	int l = strlen(p);
	int ans = 0, id;
	for(int i = 0; i < l; ++ i) {
		node *cur = root;
		for(int j = i; j < l; ++ j) {
			id = p[j] - 'a';
			cur = cur->next[id];
			if(cur == NULL) {
				break;
			}
			ans += cur->cnt;
			cur->cnt = 0;	//notice: clear to 0
		}
	}
	return ans;
}

int main(int argc, char const *argv[]) {
	// freopen("data.in", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t --) {
		int n;
		cin >> n;
		node *root = new node();
		while(n --) {
			scanf("%s", p);
			build(root, p);
		}
		scanf("%s", s);
		cout << query(root, s) << endl;
	}
	return 0;
}