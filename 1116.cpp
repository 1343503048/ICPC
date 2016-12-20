#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX = 100000+5;

int in[26], out[26];
int f[26];
bool vis[26];

int find(int x) {
	if(f[x] != x){
		f[x] = find(f[x]);
	}
	return f[x];
}

void unit(int x, int y) {
	x = find(x);
	y = find(y);
	if(x != y){
		f[y] = x;
	}
}


int main(){
	//freopen("data.in", "r", stdin);
	int t;
	char s[1005];
	scanf("%d", &t);
	while(t -- ) {
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		for(int i = 0; i < 26; ++ i){
			f[i] = i;
			vis[i] = false;
		}
		int n;
		scanf("%d", &n);
		while(n -- ) {
			scanf("%s", s);
			int x = s[0] - 'a';
			int y = s[strlen(s)-1] - 'a';
			unit(x, y);
			in[y] ++;
			out[x] ++;
			vis[x] = vis[y] = true;
		}
		int root = 0, front = 0, rear = 0, ok = 1;
		for(int i = 0; i < 26; ++ i) {
			if(vis[i]){
				if(f[i] == i){
					root ++;
					if(root > 1){
						ok = 0;
						break;
					}
				}
				if(in[i] != out[i]){
					if(in[i] + 1 == out[i]){
						front ++;
					}
					else if(in[i] == out[i]+1){
						rear ++;
					}
					else {
						ok = 0;
						break;
					}
				}
			}
		}													
		if(ok && root & 1 && ((rear & 1 && front & 1) || (rear+front == 0) /*可能出现ko ok*/)) {
			cout << "Ordering is possible." << endl;
		}
		else {
			cout << "The door cannot be opened." << endl;
		}
	}
	return 0;
}
