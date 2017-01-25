#include <bits/stdc++.h>
using namespace std;
const int N = 500000+10;
char s[1000000], key[51];

struct node {
	node *fail, *next[26];
	int cnt;
	node() {
		fail = NULL;
		cnt = 0;
		for (int i = 0; i < 26; ++i) {
			next[i] = NULL;
		}
	}
};

node *root;

void insert(char *s) {
	int id, l = strlen(s);
	node *cur = root;
	for(int i = 0; i < l; ++ i) {
		id = s[i] - 'a';
		if(cur->next[id] == NULL) {
			cur->next[id] = new node();
		}
		cur = cur->next[id];
	}
	cur->cnt ++ ;
}

void build() {
	queue<node *> Q;
	Q.push(root);
	while(!Q.empty()) {
		node *cur = Q.front(), *temp = NULL;
		Q.pop();
		for(int i = 0; i < 26; ++ i) {
			if(cur->next[i] != NULL) {
				if(cur == root) {//第一个元素的fail必指向根
					cur->next[i]->fail = root;
				}
				else {
					temp = cur->fail;    //失败指针, root
					while(temp != NULL) {    //2种情况结束：匹配为空or找到匹配
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
 
int query() {
	int id, l = strlen(s), result = 0;
	node *cur = root;
	for (int i = 0; i < l; ++ i) {
		id = s[i] - 'a';
		while (cur->next[id] == NULL && cur != root) {	//跳转失败指针
			cur = cur->fail;
		}
		cur = cur->next[id];
		if(cur == NULL) {
			cur = root;
		}
		node *temp = cur;
		while (temp != root) {
			result += temp->cnt;
			temp->cnt = 0;
			temp = temp->fail;
		}
	}
	return result;
}

int main() {
	int t, n;
	scanf("%d", &t);
	while(t --) {
		root = new node();
		scanf("%d", &n);
		while(n --) {
			scanf("%s", key);
			insert(key);
		}
		build();
		scanf("%s", s);
		printf("%d\n" ,query());
	}
	return 0;
}