// 本题为Lucas定理推导题，我们分析一下 C(n,m)%2,那么由lucas定理，我们可以写
// * 成二进制的形式观察，比如 n=1001101，m是从000000到1001101的枚举，我们知道在该定理中
// * C(0,1)=0,因此如果n=1001101的0对应位置的m二进制位为1那么C(n,m) % 2==0,因此m对应n为0的
// * 位置只能填0，而1的位置填0，填1都是1（C(1,0)=C(1,1)=1)，不影响结果为奇数，并且保证不会
// * 出n的范围，因此所有的情况即是n中1位置对应m位置0，1的枚举，那么结果很明显就是：2^(n中1的个数)
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	int n;
	while(cin >> n) {
		int ans = 0;
		while(n) {
			ans += n&1;
			n >>= 1;
		}
		cout << (1<<ans) << endl;
	}
	return 0;
}