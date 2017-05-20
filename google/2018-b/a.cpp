#include <bits/stdc++.h>
using namespace std;

using ULL = unsigned long long int;
ULL MOD = (ULL)(1e9+7);

class Solution {
private:
    vector<ULL> co{1};
    void init() {
        for(int i = 0; i < 10000; ++ i) {
            co.push_back((co.back() << 1) % MOD);
        }
    }
public:
    Solution() {
        init();
    }
    int solve(const vector<ULL> &nums) {
        ULL sum = 0;
        for(int i = 1; i < nums.size(); ++ i) {
            for(int j = 0; j < i; ++ j) {
                sum += ((nums[i] - nums[j]) % MOD) * (co[i - j - 1] % MOD) % MOD;
                sum %= MOD;
            }
        }
        return sum;
    }
};

int main() {
	int T;
	cin >> T;

	Solution s;

	for(int i = 1; i <= T; ++ i) {
		int N;
        cin >> N;
        vector<ULL> nums(N);
        for(auto &n : nums) {
            cin >> n;
        }
		printf("Case #%d: %d\n", i, s.solve(nums));
	}
    return 0;
}
