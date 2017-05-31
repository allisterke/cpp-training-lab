#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int largestRectangleArea(const vector<int>& heights) {
        int largest = 0;
        stack<pair<int, int>> leftAscendingStack;
        for(int i = 0; i < heights.size(); ) {
            leftAscendingStack.emplace(heights[i], i);
            int j = i+1;
            for(; j < heights.size() && heights[j] >= leftAscendingStack.top().first; ++ j) {
                leftAscendingStack.emplace(heights[j], j);
            }
            int k = j;
            for(; k < heights.size() && heights[k] <= heights[k-1]; ++ k)
                ;
            auto lastLeft = leftAscendingStack.top();
            auto lastRight = lastLeft;
            leftAscendingStack.pop();
            largest = max(largest, lastLeft.first);
            while(!leftAscendingStack.empty() && j < k) {
                if(leftAscendingStack.top().first > heights[j]) {
                    lastLeft = leftAscendingStack.top();
                    leftAscendingStack.pop();
                    largest = max(largest, lastLeft.first * (lastRight.second - lastLeft.second + 1));
                }
                else {
                    lastRight = make_pair(heights[j], j);
                    ++ j;
                    largest = max(largest, lastRight.first * (lastRight.second - lastLeft.second + 1));
                }
            }
            if(leftAscendingStack.empty()) {
                for(; j < k; ++ j) {
                    largest = max(largest, heights[j] * (j - lastLeft.second + 1));
                }
                leftAscendingStack.emplace(heights[k-1], lastLeft.second);
            }
            else {
                if(k < heights.size()) {
                    leftAscendingStack.emplace(lastRight.first, lastLeft.second);
                }
                else {
                    leftAscendingStack.emplace(lastRight.first, lastRight.second);
                }
            }
            i = k;
        }
        if(!leftAscendingStack.empty()) {
            auto peek = leftAscendingStack.top();
            leftAscendingStack.pop();
            while(!leftAscendingStack.empty()) {
                auto top = leftAscendingStack.top();
                leftAscendingStack.pop();
                largest = max(largest, top.first * (peek.second - top.second + 1));
            }
        }
        return largest;
    }
};

int main() {
    Solution s;
    cout << s.largestRectangleArea(vector<int>{2,1,5,6,2,3,4,7,1,5,9,5}) << endl;
    return 0;
}
