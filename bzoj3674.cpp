
/***********************************************************
   
        FileName：bzoj3674.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-09-19 11:20:33
    Descripttion：可持久化并查集
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
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

int rt[N], ls[N*40], rs[40*N], v[40*N], dep[40*N];
int sz;
int n, m;

void build(int &o, int l, int r) {
    o = ++sz;
    if(l == r) {
        v[o] = l;
        return ;
    }
    int mid = (l + r) >> 1;
    build(ls[o], l, mid);
    build(rs[o], mid+1, r);
}

void update(int x, int &y, int l, int r, int pos, int vi) {
    y = ++ sz;
    if(l == r) {
        v[y] = vi;
        return ;
    }
    ls[y] = ls[x];
    rs[y] = rs[x];
    int mid = (l + r) >> 1;
    if(pos <= mid) {
        update(ls[x], ls[y], l, mid, pos, vi);
    }
    else {
        update(rs[x], rs[y], mid+1, r, pos, vi);
    }
}

int query(int o, int l, int r, int x){
    if(l == r) {
        return o;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) {
        return query(ls[o], l, mid, x);
    }
    else {
        return query(rs[o], mid+1, r, x);
    }
}

void add(int o, int l, int r, int x) {
    if(l == r) {
        dep[o] ++;
        return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) {
        add(ls[o], l, mid, x);
    }
    else {
        add(rs[o], mid+1, r, x);
    }
}

int find(int k, int x) {
    int p = query(k, 1, n, x);
    if(x == v[p]) {
        return p;
    }
    else {
        return find(k, v[p]);
    }
}

int main() {
    read(n);
    read(m);
    build(rt[0], 1, n);
    int last = 0;
    for(int i = 1; i <= m; ++ i) {
        int type;
        read(type);
        if(type == 1) {
            rt[i] = rt[i-1];
            int a, b;
            read(a);
            read(b);
            a ^= last;
            b ^= last;
            a = find(rt[i], a);
            b = find(rt[i], b);
            // 启发式合并
            if(v[a] != v[b]) {
                if(dep[a] > dep[b]) {
                    swap(a, b);
                }
                update(rt[i-1], rt[i], 1, n, v[a], v[b]);
                if(dep[a] == dep[b]) {
                    add(rt[i], 1, n, b);
                }
            }
        }
        else if(type == 2) {
            int k;
            read(k);
            k ^= last;
            rt[i] = rt[k];        
        }
        else {
            rt[i] = rt[i-1];
            int a, b;
            read(a);
            read(b);
            a ^= last;
            b ^= last;
            a = find(rt[i], a);
            b = find(rt[i], b);
            if(v[a] != v[b]) {
                last = 0;
                puts("0");
            }
            else {
                last = 1;
                puts("1");
            }
        }
    }
    return 0;
}
