
/***********************************************************
   
        FileName：2222.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-09 13:33:17
    Descripttion：AC自动机
   
*************************************************************/

#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 5e5+5;

int np[N][26];
int fail[N];
int cnt[N];
char keyword[55];
char s[1000005];
int o;

void insert() {
    int l = strlen(keyword);
    int cur = 1;
    for(int i = 0; i < l; ++ i) {
        int id = keyword[i] - 'a';
        if(np[cur][id] == 0) {
            np[cur][id] = ++ o;
        }
        cur = np[cur][id];
    }
    ++ cnt[cur];
}

void build() {
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()){
        int cur = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++ i) {
            if(np[cur][i] == 0) continue;
            if(cur == 1) {
                fail[np[cur][i]] = 1;
            }
            else {
                int tmp = fail[cur];
                while(tmp != 0) {
                    if(np[tmp][i] != 0) {
                        fail[np[cur][i]] = np[tmp][i];
                        break;
                    }
                    tmp = fail[tmp];
                }
                if(tmp == 0) {    // 在while之后`
                    fail[np[cur][i]] = 1;
                }
            }
            Q.push(np[cur][i]);
        }
    }
}

void query() {
    int res = 0;
    int l = strlen(s);
    int cur = 1;
    for(int i = 0; i < l; ++ i) {
        int id = s[i]-'a';
        while(np[cur][id] == 0 && cur != 1) {
            cur = fail[cur];
        }
        cur = np[cur][id];
        if(cur == 0) {
            cur = 1;
        }
        int tmp = cur;
        while(tmp != 1) {
            res += cnt[tmp];
            cnt[tmp] = 0;
            tmp = fail[tmp];
        }
    }
    printf("%d\n", res);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t --) {
        memset(np, 0, sizeof(np));
        memset(fail, 0, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
        int n;
        scanf("%d", &n);
        o = 1;
        while(n --) {
            scanf("%s", keyword);
            insert();          
        }

        build();

        scanf("%s", s);

        query();
    
    }
    return 0;
}
