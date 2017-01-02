//给定一些水渠的最大流量
//1为池塘，然后问到点m的最大流量
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 1000 + 5; 
const int INF = 0x3f3f3f3f;

class Node
{
    public:
        int to, cap, rev;
        Node(int _to, int _cap, int _rev)    
        {
            to = _to;
            cap = _cap;
            rev = _rev;
        }
};

vector<vector<Node> > v(MAX);
bool vis[MAX];
int n, m;

int dfs(int s, int t, int f)
{
    if(s == t)
    {
        return f;
    }
    vis[s] = true;
    for(int i = 0; i < v[s].size(); ++ i)
    {
        Node &temp = v[s][i];                            //引用 
        if(!vis[temp.to] && temp.cap > 0)
        {
            int d = dfs(temp.to, t, min(temp.cap, f));  //找出当前路径的最小值 
            if(d > 0)
            {
                temp.cap -= d;
                v[temp.to][temp.rev].cap += d;          //反向时可抵去 
                return d;
            }
        }
    }
    return 0;   //!!!!!
}

int FF(int s, int t)
{
    int f = 0;
    int flow = 0;
    while(1)
    {
        memset(vis, false, sizeof(vis));
        f = dfs(s, t, INF);
        if(f == 0)
        {
            return flow;
        }
        flow += f;
    }
}

int main()
{
    //ifstream cin("data.in");
    while(cin >> n >> m)
    {
        for(int i = 0; i < n; i ++)
        {
            int s, t, cap;
            cin >> s >> t >> cap;
            v[s].push_back(Node(t, cap, v[t].size()));
            v[t].push_back(Node(s, 0, v[s].size()-1));
        }
        cout << FF(1, m) << endl;
        for(int i = 0; i < MAX; i ++)
        {
            v[i].clear();   //注意容器清空
        } 
    }
    return 0;
}
