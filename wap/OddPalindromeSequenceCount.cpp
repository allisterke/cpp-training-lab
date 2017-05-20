#include <bits/stdc++.h>
using namespace std;

long long int MOD = 1e9+7;

int main() {
	string s;
	cin >> s;
	vector<vector<int>> fc(s.size(), vector<int>(s.size()));
	vector<vector<int>> rc(s.size(), vector<int>(s.size()));
	for(int k = 0; k < s.size(); ++ k) {
		for(int i = 0; i + k < s.size(); ++ i) {
			if(k == 0) {
				fc[i][i+k] = 1;
				rc[i][i+k] = 1;
			}
			else {
				fc[i][i+k] = k > 1 && s[i] == s[i+k] ? rc[i+1][i+k-1] : 0;
				rc[i][i+k] = rc[i][i+k-1] + rc[i+1][i+k] - rc[i+1][i+k-1] + fc[i][i+k];
			}
			fc[i][i+k] %= MOD;
			rc[i][i+k] %= MOD;
		}
	}
	cout << rc[0][s.size()-1] << endl;
	return 0;
}
