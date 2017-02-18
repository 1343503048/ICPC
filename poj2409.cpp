// http://blog.csdn.net/lyc1635566ty/article/details/52545355
// polay
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
} 

int polay_circle(int c, int s) {
	int ans = 0;
	// 旋转
	for(int i = 1; i <= s; ++ i) {	//i为转动几个珠子
		ans += pow(c, gcd(s, i));
	}
	// 翻转
	if(s & 1) {	//奇数时只存在一种,(穿过一个珠子为对角线)
		ans += s * pow(c, s/2 + 1);
	}
	else {	// 偶数时存在两种(分别为转过0个珠子为对角线和穿过两个珠子为对角线)
		ans += (pow(c, s/2) + pow(c, s/2+1)) * s / 2;
	}
	return ans / (s * 2);
}

int main() {
	int c, s;
	while(scanf("%d%d", &c, &s) && c != 0) {
		printf("%d\n", polay_circle(c, s));
	}
	return 0;
}