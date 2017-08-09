
/***********************************************************
   
        FileName：2896.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-08-09 10:15:12
    Descripttion：字典树
   
*************************************************************/

#include <cstdio>
#include <set>
#include <cstring>
#include <queue>
using namespace std;

struct node {
    int cnt;
    node *fail, *next[130];
};

node ret[100000];
char key[205], s[10005];
node *rt;
int tot;

// 建立字典树
void insert(int num) {
    int l = strlen(key);
    node *cur = rt;
    for(int i = 0; i < l; ++ i) {
        int id = key[i];
        if(cur->next[id] == NULL) {
            cur->next[id] = &ret[++tot];
        }
        cur = cur->next[id];
    } 
    cur->cnt = num;
}

// 
void build() {
    queue<node *> Q;
    Q.push(rt);
    while(!Q.empty()) {
        node *cur = Q.front();
        Q.pop();
        for(int i = 0; i < 130; ++ i) {
            if(cur->next[i] == NULL) continue;
            if(cur == rt) {
                cur->next[i]->fail = rt;
            }
            else {
                node *tmp = cur->fail;
                if(tmp == NULL) {   // 首次遍历
                    cur->next[i]->fail = rt;
                }
                while(tmp != NULL) {
                    if(tmp->next[i] != NULL) {
                        cur->next[i]->fail = tmp->next[i];
                        break;
                    }
                    tmp = tmp->fail;
                }
            }
            Q.push(cur->next[i]);
        }
    }
}

int query(int num) {
    set<int> st;
    node *cur = rt;
    int l = strlen(s);
    for(int i = 0; i < l; ++ i) {
        int id = s[i];
        while(cur->next[id] == NULL && cur != rt) {
            cur = cur->fail;
        }
        cur = cur->next[id];
        if(cur == NULL) {
            cur = rt;
        }
        node *tmp = cur;
        while(tmp != rt) {
            if(tmp->cnt > 0) {
                st.insert(tmp->cnt);
            }
            tmp = tmp->fail;
        }
    }
    if(st.size() > 0) {
        printf("web %d:", num);
        for(auto x : st) {
            printf(" %d", x);
        }
        printf("\n");
        return 1;
    }
    return 0;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        tot = 0;
        rt = &ret[++tot];
        for(int i = 1; i <= n; ++ i) {
            scanf("%s", key);
            insert(i);
        }
        build();
        int m;
        scanf("%d", &m);
        int ans = 0;
        for(int i = 1; i <= m; ++ i) {
            scanf("%s", s);
            ans += query(i);
        }

        printf("total: %d\n", ans);
        for(int i = 0; i <= tot; ++ i) {
            ret[i].cnt = 0;
            ret[i].fail = NULL;
            for(int j = 0; j < 130; ++ j) {
                ret[i].next[i] = NULL;
            }
        }
    }
    return 0;
}
