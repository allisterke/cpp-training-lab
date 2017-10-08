#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(const vector<int> &prices) {
        priority_queue<pair<int, int>> pq;
        for(int i = 0; i < prices.size(); ++ i) {
            pq.emplace(prices[i], i);
        }
        int last = -1;
        LL profit = 0;
        while(!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            if(top.second < last) {
                continue;
            }
            else {
                for(++ last; last < top.second; ++ last) {
                    profit += top.first - prices[last];
                }
            }
        }
        return profit;
    }
};

void test() {
    Solution s;
    vector<int> prices{1, 2, 3, 4, 5};
    cout << s.solve(prices) << endl;
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<int> prices(N);
    for(auto &price : prices) {
        cin >> price;
    }
    cout << s.solve(prices) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
