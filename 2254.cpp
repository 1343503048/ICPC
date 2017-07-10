
/*************************************************

       Filename: 2254.cpp
         Author: zQ
          Email: zq216991@foxmail.com
         Create: 2017-07-09 15:50:14
    Description: 矩阵快速幂+map

*************************************************/
// 题解: http://www.cnblogs.com/cumulonimbus/p/5698434.html

#include <bits/stdc++.h>
using namespace std;
const int mod = 2008;

typedef vector<int> vec;
typedef vector<vec> mat;

struct point{
    int x, y;
};

mat mulity(const mat& a, const mat& b) {
    mat c(a.size(), vec(b[0].size()));
    for(size_t i = 1; i < a.size(); ++ i) {
	for(size_t k = 1; k < a[0].size(); ++ k) {
	    if(a[i][k] == 0) continue;
	    for(size_t j = 1; j < b[0].size(); ++ j) {
		c[i][j] += a[i][k] * b[k][j];
		c[i][j] %= mod;
	    }
	}
    }
    return c;
}

mat _pow(const mat& a, int n) {
    mat res(a.size(), vec(a[0].size()));
    mat k = a;
    for(size_t i = 1; i < a.size(); ++ i) {
	res[i][i] = 1;
    }
    while(n > 0) {
	if(n&1) res = mulity(res, k);
	n >>= 1;
	k = mulity(k, k);
    }
    return res;
}

int main() {
    int n;
    while(~scanf("%d", &n)) {
	map<int, int> mp;
	int id = 0;
	vector<point> v;
	for(int i = 0; i < n; ++ i) {
	    int x, y;
	    scanf("%d%d", &x, &y);
	    if(!mp[x]) {
		mp[x] = ++ id;
	    }
	    if(!mp[y]) {
		mp[y] = ++ id;
	    }
	    v.push_back(point{mp[x], mp[y]});
	}
	mat ori(2*id+1, vec(2*id+1));
	for(int i = 1; i <= id; ++ i) {
	    ori[i][i] = ori[i][id+i] = 1;
	}
	mat c(2*id+1, vec(id+1));
	for(size_t i = 0; i < v.size(); ++ i) {
	    int x = v[i].x, y = v[i].y;
	    c[x+id][y] ++;
	    ori[x+id][y+id] ++;
	}
	int k;
	scanf("%d", &k);
	while(k --) {
	    int x, y, t1, t2;
	    scanf("%d%d%d%d", &x, &y, &t1, &t2);
	    if(!mp.count(x) || !mp.count(y)) {
		puts("0");
		continue;
	    }
	    x = mp[x];
	    y = mp[y];
	    if(t1 > t2) swap(t1, t2);
	    mat tmp = _pow(ori, t1-1);
	    tmp = mulity(tmp, c);
	    int a = tmp[x][y];
	    tmp = _pow(ori, t2);
	    tmp = mulity(tmp, c);
	    int b = tmp[x][y];
	    printf("%d\n", (b - a + mod)%mod);
	}
    }
    return 0;
}
