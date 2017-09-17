
/***********************************************************
   
        FileName：bzoj1878_1.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-18 00:43:00
    Descripttion：树状数组
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 5e4+5;

namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
using namespace fastIO;

struct Query{
    int l, r, id;
    bool operator < (const Query &a) const {
        return l < a.l;
    }
};

Query q[N*4];
int head[N*20];
int np[N];
int a[N];
int s[N];
int res[N*4];

void add(int i, int v) {
    while(i < N) {
        s[i] += v;
        i += i&(-i);
    }
}

int getSum(int i) {
    int res = 0;
    while(i > 0) {
        res += s[i];
        i -= i&-i;
    }
    return res;
}

int main() {
    int n;
    while(~scanf("%d", &n)) {
        memset(head, 0, sizeof(head));
        memset(s, 0, sizeof(s));
        for(int i = 1; i <= n; ++ i) {
            read(a[i]);
            if(!head[a[i]]) {
                add(i, 1);
                head[a[i]] = -1;
            }
        }


        for(int i = n; i; -- i) {
            np[i] = head[a[i]];
            head[a[i]] = i;
        }

        int m;
        read(m);

        for(int i = 0; i < m; ++ i) {
            read(q[i].l);
            read(q[i].r);
            q[i].id = i;
        }

        sort(q, q+m);

        int l = 1;
        for(int i = 0; i < m; ++ i) {
            while(l < q[i].l) {
                if(np[l]!=-1) {
                    add(np[l], 1);
                }
                ++ l;
            }
            res[q[i].id] = getSum(q[i].r) - getSum(q[i].l-1);
        }

        for(int i = 0; i < m; ++ i) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
