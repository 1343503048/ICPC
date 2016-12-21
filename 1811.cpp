#include  <iostream>
#include  <fstream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 10000+5;

int father[MAX], in[MAX];
vector<vector<int> > v(MAX);
int n, m;
bool vis[MAX];
int l[MAX], r[MAX];
char oper[MAX];
int ans;

void init()
{
    for (int i  =  0; i  <  n; ++i)
    {
        father[i] = i;
        v[i].clear();
    }
}

int find(int x)
{
    return father[x] = (father[x] == x ? father[x] : find(father[x]));
}

void meger(int x, int y)
{
    int x0 = find(x);
    int y0 = find(y);
    father[y0] = x0;
}

void sort()
{
    queue<int> q;
    int temp = 0;
    for(int i = 0; i < n; i ++)
    {
        int x = find(i);
        if(in[x] == 0 && !vis[x])
        {
            temp ++;
            //cout << " X = " << x << endl;
            q.push(x);
            vis[x] = true;
        }
    }
    if(temp > 1)    //xinxibuquan
    {
        ans = 2;
    }
    if(temp == 0)    //chongtu.youhuan
    {
        ans = 3;
    }
    if(ans != 3)
    {
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            int temp  = 0;
            for(int i = 0; i < v[x].size(); ++ i)
            {
                int k = find(v[x][i]);
                in[k] --;
                if(in[k] == 0 && !vis[k])
                {
                    temp ++;
                    vis[k] = true;
                    q.push(k);
                }
            }
            if(temp == 0 && !q.empty()) {
                ans = 3;
                break;
            }
            if(temp > 1)
            {
                ans = 2;
            }
        }
    }
    if(ans == 1)
    {
        cout << "OK" << endl;
    }
    else if(ans == 2)
    {
        cout << "UNCERTAIN" << endl;
    }
    else
    {
        cout << "CONFLICT" << endl;
    }
}

int main()
{
    ifstream cin("data.in");
    while(cin >> n >> m)
    {
        init();
        ans = 1;
        memset(in, 0, sizeof(in));
        memset(vis, false, sizeof(vis));
        for(int i = 0; i < m; ++ i)
        {
            cin >> l[i] >> oper[i] >> r[i];
            if(oper[i] == '=')
            {
                meger(find(l[i]), find(r[i]));
            }
        }
        for (int i = 0; i < m; ++ i)
        {
            int x = find(l[i]);
            int y = find(r[i]);
            if(x == y && oper[i] != '=')
            {
                ans = 3;
                break;
            }
            switch(oper[i])
            {
                case '>':
                    v[x].push_back(y);
                    in[y] ++;
                    break;
                case '<':
                    v[y].push_back(x);
                    in[x] ++;
                    break;
            }
        }
        sort();
    }
    return 0;
}
