#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;
pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

class Solution {
public:

};

void test() {
    Solution s;
}

void run() {
    Solution s;
}

int main() {
//    test();
//    run();
    using Status = bitset<26>;
    string s;
    while (cin >> s) {
        vector<int> dp(s.size() + 1);
        unordered_map<Status, int> pos;
        Status status;
        pos[status] = 0;
        for(int i = 0; i < s.size(); ++ i) {
            dp[i+1] = i+1; // init
            int index = s[i] - 'a';
            status.flip(index);
            if(pos.find(status) != pos.end()) { // all same
                dp[i+1] = min(dp[i+1], 1 + dp[pos[status]]);
            }
            for(int j = 0; j < 26; ++ j) { // one different
                status.flip(j);
                if(pos.find(status) != pos.end()) {
                    dp[i+1] = min(dp[i+1], 1 + dp[pos[status]]);
                }
                status.flip(j);
            }
            if(pos.find(status) == pos.end()) {
                pos[status] = i + 1;
            }
            else {
                int last = pos[status];
                if(dp[i+1] < dp[last]) {
                    pos[status] = i+1;
                }
            }
        }
        cout << dp.back() << endl;
    }
    return 0;
}
