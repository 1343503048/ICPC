#include <iostream>
//#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

class node{
public:
	int count;
	node* next[26];
	node(){
		memset(next, 0, sizeof(next));
		count = 0;
	}
};

void build(node *root, char s[]) {
	node *cur = root;
	int l = strlen(s);
	for(int i = 0; i < l; ++ i){
		int id = s[i] - 'a';
		if(cur->next[id] == NULL) {
			cur->next[id] = new node();
		}
		cur = cur->next[id];
		cur->count ++;
	}
}

int query(node *root, char s[]) {
	node *cur = root;
	int l = strlen(s);
	for(int i = 0; i < l; ++ i) {
		int id = s[i] - 'a';
		cur = cur->next[id];
		if(cur == NULL) {
			return 0;
		}
	}
	return cur->count;
}

int main() {
	// ifstream cin("data.in");
	char str[12];
	node *root = new node();
	while(gets(str)){
		if(strlen(str) == 0) {
			break;
		}
		build(root, str);
	}
	while(gets(str)){
		cout << query(root, str) << endl;
	}
	return 0;
}