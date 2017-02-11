#include <cstdio>
#include <vector>
using namespace std;
const int M = 10007;
typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

// cal A*B
mat mul(mat &A, mat &B) {
	mat c(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); ++ i) {
		for(int j = 0; j < B[0].size(); ++ j) {
			for(int k = 0; k < B.size(); ++ k) {
				c[i][j] += A[i][k] * B[k][j];
				c[i][j] %= M;
			}
		}
	}
	return c;
}

// cal A^n
mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	for(int i = 0; i < A.size(); ++ i) {
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
	int t;
	scanf("%d", &t);
	while(t --) {
		int n;
		scanf("%d", &n);
		mat A(3, vec(3));
		A[0][0] = 2; A[0][1] = 1; A[0][2] = 0;
		A[1][0] = 2; A[1][1] = 2; A[1][2] = 2;
		A[2][0] = 0; A[2][1] = 1; A[2][2] = 2;
		A = pow(A, n);
		printf("%d\n", A[0][0]);
	}
	return 0;
}