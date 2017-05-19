//S(k) = I + A + ...... + A ^ (k-1)
//(A^k )     (A | 0 )(A^(k-1))   (A | 0)^k( I )
//(----)  == (------)(-------) = (-----)  (---)
//(S(k))     (I | I )( S(k-1))   (I | I)  ( 0 )
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

int n, m, k;

// calu A * B
mat mul(mat &A, mat &B) {
	mat c(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); ++ i) {
		for(int j = 0; j < B[0].size(); ++ j) {
			for(int k = 0; k < A.size(); ++ k) {
				c[i][j] += A[i][k] * B[k][j];
				c[i][j] %= m;
			}
		}
	}
	return c;
}

// calu A ^ n
mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	for (int i = 0; i < A.size(); ++ i ) {
		B[i][i] = 1;
	}
	while(n > 0) {
		if(n & 1) {
			B = mul(B, A);
		}
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}

int main(int argc, char const *argv[]) {
	freopen("data.in", "r", stdin);
	scanf("%d%d%d", &n, &k, &m);
	mat A(n, vec(n));
	mat B(n*2, vec(2*n));
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < n; ++ j) {
			scanf("%d", &B[i][j]);
		}
		B[n+i][i] = B[n+i][n+i] = 1;
	}
	B = pow(B, k+1);
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < n; ++ j) {
			int a = B[n+i][j] % m;
			if(i == j) {
				a = (a + m - 1) % m;
			}
			printf("%d%c", a, j + 1 == n ? '\n' : ' ');
		}
	}
	return 0;
}
