#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(vector<int> &A) {
//        int preMax = numeric_limits<int>::min();
//        int maxInverted = numeric_limits<int>::min();
        int preMax = 0;
        int maxInverted = 0;
        for(auto a : A) {
            if(a < preMax) {
                maxInverted = max(maxInverted, a);
            }
            preMax = max(preMax, a);
        }
        return maxInverted;
//        sort(A.begin(), A.end());
//        auto it = lower_bound(A.begin(), A.end(), maxInverted);
//        return maxInverted == numeric_limits<int>::min() ? 0 : distance(A.begin(), it) + 1;
    }
};

int main() {
    Solution s;
    int N;
    while(cin >> N) {
        vector<int> A(N);
        for(auto &a : A) {
            cin >> a;
        }
        cout << s.solve(A) << endl;
    }
    return 0;
}
