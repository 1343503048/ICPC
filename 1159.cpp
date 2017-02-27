#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e3+5;
char a[N], b[N];
int dp[2][N];   //运用数的奇偶性，内存优化

int main() {
    while(cin >> a >> b) {
        int x = strlen(a);
        int y = strlen(b);
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < x; ++ i) {
            for(int j = 0; j < y; ++ j) {
                if(a[i] == b[j]){
                    dp[(i+1)&1][j+1] = dp[i&1][j] + 1;      
                }
                else {
                    dp[(i+1)&1][j+1] = max(dp[i&1][j+1], dp[(i+1)&1][j]);
                }
            }
        }
        cout << dp[x&1][y] << "\n";
    }
    return 0;
}
