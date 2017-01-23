#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
	string s1, s2;
	while(cin >> s1 >> s2) {
		string s(150, '0');
		reverse(s1.begin(), s1.end());
		reverse(s2.begin(), s2.end());
		for(int i = 0; i < s1.length(); ++ i) {
			for(int j = 0; j < s2.length(); ++ j) {
				int temp = (s1[i]-'0')*(s2[j]-'0');
				s[i+j+1] = (s[i+j+1] - '0' + (s[i+j] - '0' + temp) / 10) + '0';
				s[i+j] = (s[i+j] - '0' + temp) % 10 + '0';
			}
		}
		reverse(s.begin(), s.end());
		if(s.find_first_not_of('0') == string::npos){
			cout << "0" << endl;
		}
		else {
			cout << s.substr(s.find_first_not_of('0')) << endl;
		}
	}
	return 0;
}