#include <iostream>
#include <cstring>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

const int N = 500+5;

int dist[N], p[N], val[N];
bool vis[N];
map<int, int> e[N];

void spfa(int s, int t) {
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f3f3f, sizeof(dist));
    memset(p, 0, sizeof(p));
    dist[s] = 0;
    p[s] = val[s];
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int v = Q.front();
        Q.pop();
        vis[v] = false;
        map<int, int>::iterator it;
        for(it = e[v].begin(); it != e[v].end(); it ++) {
            int to = it->first;
            int w = it->second;
            if(dist[to] > dist[v] + w || (dist[to] == dist[v] + w && p[to] < p[v] + val[to])) {
                dist[to] = dist[v] + w;
                p[to] = p[v] + val[to];
                if(!vis[to]) {
                    vis[to] = true;
                    Q.push(to);
                }
            }
        }
    }
    cout << dist[t] << " " << p[t] << endl;
}

int main() {
    //ifstream cin("data.in");
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, s, t;
    while(cin >> n >> m >> s >> t) {
        for(int i = 0; i < n; ++ i) {
            cin >> val[i];
        }
        while(m --) {
            int x, y, w;
            cin >> x >> y >> w;
            e[x][y] = w;
            e[y][x] = w;
        }
        spfa(s, t);
        for(int i = 0; i < n; ++ i) {
            e[i].clear();
        }
    }
    return 0;
}