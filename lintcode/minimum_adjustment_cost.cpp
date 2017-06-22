#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    /**
     * @param A: An integer array.
     * @param target: An integer.
     */
    int MinAdjustmentCost(vector<int> A, int target) {
        // write your code here
        if(A.size() <= 1) {
            return 0;
        }
        vector<vector<int>> dp(101, vector<int>(A.size(), numeric_limits<int>::max()));
        for(int j = A.size() - 1; j >= 0; -- j) {
            for(int i = 1; i <= 100; ++ i) {
                if(j == A.size() - 1) {
                    dp[i][j] = abs(i - A[j]);
                }
                else {
                    for(int k = max(1, i - target); k <= min(100, i + target); ++ k) {
                        dp[i][j] = min(dp[i][j], abs(i - A[j]) + dp[k][j+1]);
                    }
                }
            }
        }
        int mac = numeric_limits<int>::max();
        for(int i = 1; i <= 100; ++ i) {
            mac = min(mac, dp[i][0]);
        }
        return mac;
    }
};

int main() {
    Solution s;
    cout << s.MinAdjustmentCost(vector<int>{1,4,2,3}, 1) << endl;
    return 0;
}
