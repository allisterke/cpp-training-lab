#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL MOD = 1e9 + 7;

class Solution {
public:
    int solve(int n, int k) {
        vector<vector<LL>> dp(n+1, vector<LL>(n+1));
        for(int i = 0; i <= n; ++ i) {
            for(int j = i; j <= n; ++ j) {
                if(i == 0 || j == 0) {
                    dp[i][j] = 1;
                }
                else if(i == j) {
                    for(int k = 0; k < i; ++ k) {
                        dp[i][i] += dp[k][k] * dp[i-k-1][i-k-1] % MOD;
                        dp[i][i] %= MOD;
                    }
                }
                else {
                    dp[i][j] = dp[i][j-1];
                    for(int k = 1; k <= i; ++ k) {
                        dp[i][j] += dp[i-k][j-k-1] * dp[k][k] % MOD;
                        dp[i][j] %= MOD;
                    }
                }
            }
        }
        if(k == 0) {
            return dp[n][n];
        }
        LL total = 0;
        for(int i = 0; i <= n-k; ++ i) {
            LL left = dp[n-k-i][n-i];
            LL right = dp[i][k+i-1];
            total += left * right % MOD;
            total %= MOD;
        }
        return total;
    }
};

void collect(int left, int right, vector<string> &collection, string &str) {
    if(left == 0 && right == 0) {
        collection.push_back(str);
    }
    if(left > 0) {
        str.push_back('(');
        collect(left-1, right, collection, str);
        str.pop_back();
    }
    if(right > 0) {
        str.push_back(')');
        collect(left, right - 1, collection, str);
        str.pop_back();
    }
}

int unpaired_left(string &str) {
    int left = 0;
    for(char c : str) {
        if(c == '(') {
            ++ left;
        }
        else if(left > 0){
            -- left;
        }
    }
    return left;
}

void test() {
    vector<string> collection;
    string str;
    collect(3, 3, collection, str);
    for(auto &s : collection) {
        if(unpaired_left(s) == 2) {
            cout << s << endl;
        }
    }
}

int main() {
//    test();
    Solution s;
    int N, K;
    cin >> N >> K;
    cout << s.solve(N, K) << endl;
    return 0;
}
