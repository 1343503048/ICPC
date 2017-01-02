//fibo
#include <iostream>
#include <queue>
using namespace std;
int val[25] = {0, 0, 0, 0, 1, 1,
				  2, 3, 3, 4, 5,
				  6, 7, 7, 8, 9,
				  10, 11, 12, 13, 14};

int main() {
	int t, n;
	cin >> t;
	for(int i = 1; i <= t; ++ i) {
		cin >> n;
		cout << "Case #" << i << ": " << val[n] << endl; 
	}
}