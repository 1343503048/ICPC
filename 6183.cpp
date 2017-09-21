
/***********************************************************
   
        FileName：6183.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-21 07:38:37
    Descripttion：线段树
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
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
int rt[51];
int ls[N*4], rs[N*4], v[N*4];
int sz;
int flag;

void update(int &o, int l, int r, int x, int y) {
    if(o == 0) {
        o = ++ sz;
        v[o] = x;
    }
    else if(v[o] > x) {
        v[o] = x;
    }
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(y <= mid) {
        update(ls[o], l, mid, x, y);
    }
    else {
        update(rs[o], mid+1, r, x, y);
    }
}

void query(int o, int l, int r, int y1, int y2, int x) {
    if(flag || o == 0) {
        return ;
    } 
    if(y1 <= l && r <= y2) {
        if(v[o] <= x) flag = 1;
        return ;
    }
    int mid = (l + r) >> 1;
    if(y1 <= mid) {
        query(ls[o], l, mid, y1, y2, x);
    }
    if(y2 > mid) {
        query(rs[o], mid+1, r, y1, y2, x);
    }
}

int main() {
    int type;
    while(1) {
        read(type);
        if(type == 3) break;
        if(type == 0) {
            sz = 0;
            memset(rs, 0, sizeof(rs));
            memset(ls, 0, sizeof(ls));
            memset(rt, 0, sizeof(rt));
        }
        else if(type == 1) {
            int x, y, c;
            read(x);
            read(y);
            read(c);
            update(rt[c], 1, 1e6, x, y);    
        }
        else {
            int x, y1, y2;
            read(x), read(y1), read(y2);
            int res = 0;
            for(int i = 0; i < 51; ++ i) {
                flag = 0;
                query(rt[i], 1, 1e6, y1, y2, x);
                res += flag;
            }
            printf("%d\n", res); 
        } 
    }
    return 0;
}
