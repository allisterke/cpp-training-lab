#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class BinaryIndexedTree {
private:
    vector<int> tree;
public:
    BinaryIndexedTree(int capacity) : tree(capacity + 1) {

    }

    void update(int index, int val) {
        int diff = val - (query(index) - query(index-1));
        while(index < tree.size()) {
            tree[index] += diff;
            index += (index & (-index));
        }
    }

    int query(int end) {
        int sum = 0;
        while (end > 0) {
            sum += tree[end];
            end -= (end & (-end));
        }
        return sum;
    }
};

int main() {
    int n = 20;
    vector<int> nums(n);
    for(auto &n : nums) {
        n = rand() % 20;
    }
    BinaryIndexedTree bit(n);
    for(int i = 0; i < nums.size(); ++ i) {
        bit.update(i+1, nums[i]);
    }
    vector<pair<int, int>> ranges{{1,3}, {4,8}, {2, 20}, {7, 17}};
    for(auto &r : ranges) {
        assert(accumulate(nums.begin() + (r.first - 1), nums.begin() + r.second, 0) == bit.query(r.second) - bit.query(r.first - 1));
    }
    return 0;
}
