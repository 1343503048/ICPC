#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

bool used[11];
int loc[11];
string s;
vector<int> v;

void dfs(int l){
    if(l == v.size()) {
        for(int i = 0; i < l; ++ i){
            cout << loc[i];
        }
        cout << endl;
    }
    else{
        for(int i = 0; i < v.size(); ++ i) {
            if(!used[i]){
                used[i] = true;
                loc[l] = v[i];
                dfs(l+1);
                used[i] = false;    //回溯
                while(i < v.size() && v[i] == v[i+1]) {
                	i ++;
                }       //当出现相同的数字时候tiaoguo
            }
        }
    }
}

int main(){
    while(cin >> s){
    	for(int i = 0; i < s.size(); ++ i) {
    		v.push_back(s[i]-'0');
    	}
    	sort(v.begin(), v.end());
        memset(used, false, sizeof(used));
        dfs(0);
    }
    return 0;
}