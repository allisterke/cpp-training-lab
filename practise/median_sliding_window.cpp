#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: The median of the element inside the window at each moving
     */
    vector<int> medianSlidingWindow(vector<int> &nums, int k) {
        // write your code here
        multiset<int, std::greater<int>> left(greater<int>());
        multiset<int> right;
        vector<int> msw;
        for(int i = 0; i < k-1; ++ i) {
            left.insert(nums[i]);
        }
        for(int i = k-1; i < nums.size(); ++ i) {
            if(right.empty() || nums[i] <= *right.begin()) {
                left.insert(nums[i]);
            }
            else {
                right.insert(nums[i]);
            }
            while(right.size() > left.size()) {
                left.insert(*right.begin());
                right.erase(right.begin());
            }
            while(left.size() - right.size() > 1) {
                right.insert(*left.begin());
                left.erase(left.begin());
            }
            msw.push_back(*left.begin());
            if(nums[i-k+1] <= *left.begin()) {
                left.erase(left.find(nums[i-k+1]));
            }
            else {
                right.erase(right.find(nums[i-k+1]));
            }
        }
        return msw;
    }
};
int main() {
	vector<int> nums{1,2,7,7,2};
	int k = 3;
	for(auto m : Solution().medianSlidingWindow(nums, k)) {
		cout << m << endl;
	}
	sort(nums.data(), nums.data()+nums.size());
	for(auto n : nums) {
		cout << n << endl;
	}
	return 0;
}
