#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(string &target) {
        vector<int> dp(target.size() + 1);
        for(int i = 0; i < target.size(); ++ i) {
            // input
            dp[i+1] = dp[i] + 1;
            // copy and paste
            for(int k = 2; k <= (i+1)/2; ++ k) {
                string r(target.begin() + i - k + 1, target.begin() + i + 1);
                string l(target.begin(), target.begin() + i - k + 1);
                if(l.find(r) == string::npos) {
                    break;
                }
                for(int j = i - k + 1; j >= k; -- j) {
                    string left(target.begin(), target.begin() + j);
                    string right(target.begin() + j, target.begin() + i + 1);
                    if(left.find(r) == string::npos) {
                        break;
                    }
                    int count = 0;
                    int start = 0;
                    while(true) {
                        int next = right.find(r, start);
                        if(next < 0) {
                            break;
                        }
                        ++ count;
                        start = next + r.size();
                    }
                    dp[i+1] = min(dp[i+1], (int)(dp[j] + 1 + count + right.size() - count*r.size()));
                }
                dp[i+1] = min(dp[i+1], dp[i-k+1] + 2);
            }
        }
        return dp.back();
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;
    for(int i = 1; i <= T; ++ i) {
        string target;
        cin >> target;
        printf("Case #%d: %d\n", i, s.solve(target));
    }
    return 0;
}
