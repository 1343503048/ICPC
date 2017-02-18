//题意：给定n的一个排列，问你最少交换多少次才能使序列升序。
//思路：一个元素个数为cnt的置换群最少需要cnt-1交换。
//统计置换群的每个循环节的元素的个数

#include <iostream>
#include <fstream>
using namespace std;

int arr[105];

int main(int argc, char const *argv[]) {
	// ifstream cin("data.in");
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++ i) {
		int ans = 0, n;
		cin >> n;

		for(int j = 1; j <= n; ++ j) {
			cin >> arr[j];
		}

		for(int j = 1; j <= n; ++ j) {
			int cnt = 0, temp = j, a;
			while(arr[temp] != -1) {
				cnt ++;
				a = temp;
				temp = arr[temp];
				arr[a] = -1;
			}
			if(cnt > 0) {
				ans += cnt-1;
			}
		}
		cout << "Case " << i << ": " << ans << endl;
	}
	return 0;
}