/*************************************************
#
#       Filename: poj3348.cpp
#         Author: zQ
#          Email: zq216991@foxmail.com
#         Create: 2017-04-17 18:54:12
#    Description: 凸包模板 
#
#*************************************************/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 10000+5;

struct point{
    int x, y;
} list[N];

// calu 叉乘ab x ac
int cross(point a, point b, point c) {
    return (b.x-a.x) * (c.y-a.y) - (c.x-a.x) * (b.y-a.y);
}

double dist(point a, point b) {
    return sqrt((double)(a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

// 极角排序
bool cmp(point a, point b) {
    int temp = cross(list[0], a, b);
    if(temp > 0) {
	return true;
    }
    else if(temp == 0 && dist(list[0], a) < dist(list[0], b)) {
	return true;
    }
    return false;
}

int main() {
    int n;
    while(cin >> n) {
	cin >> list[0].x >> list[0].y;
	int mx = list[0].x, my = list[0].y , k = 0;
	for(int i = 1; i < n; ++ i) {
	    cin >> list[i].x >> list[i].y;
	    if(my > list[i].y || (my == list[i].y && mx > list[i].x)) {
		mx = list[i].x;
		my = list[i].y;
		k = i;
	    }
	}

	if(n < 3) {
	    puts("0\n");
	    continue ;
	}

	list[k] = list[0];
	list[0] = point{mx, my};

	sort(list+1, list+n, cmp);  //按极角排序
	
	int stack[N]; 
	int top = 0;
	stack[0] = 0;
	stack[1] = 1;
	top = 1;
	for(int i = 2; i < n; ++ i) {
	    while(top > 0 && cross(list[stack[top-1]], list[stack[top]], list[i]) <= 0) {
		top --;
	    }          // 当出现内凹时剔除内凹的点
	    stack[++top] = i;
	}

	double ans = 0;
	for(int i = 1; i < top; ++ i) {
    	    int a = stack[i+1];
	    int b = stack[i];
	    ans += 0.5 * fabs(1.0 * cross(list[0], list[a], list[b]));  //计算面积
	}
	cout << (int)(ans / 50.0) << "\n";	
    }
    return 0;
}
