#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MAX = 300+5;

int checkY[MAX];
int match[MAX];
vector<vector<int> > e(MAX);

bool find(int v) {
    for(size_t i = 0; i < e[v].size(); ++ i) {
        int to = e[v][i];
        if(!checkY[to]) {
            checkY[to] = 1;
            if(match[to] == -1 || find(match[to])) {
                match[to] = v;
                return true;
            }
        }
    }
    return false;
}

int hungary(int n) {
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n; ++ i) {
        memset(checkY, 0, sizeof(checkY));
        cnt += find(i);
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    //ifstream cin("data.in");
    int n;
    while(cin >> n) {
        for(int i = 0; i < n; i ++) {
            e[i].clear();
            int t, p, q;
            cin >> t;
            while(t --) {
                cin >> p >> q;
                e[i].push_back((p-1)*12 + q);
            }
        }
        cout << hungary(n) << endl;
    }
    return 0;
}