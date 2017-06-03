#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<LL> &prefix) {
        return countPairs(prefix, 0, prefix.size());
    }

    LL countPairs(vector<LL> &prefix, int begin, int end) {
        if(begin + 1 >= end) {
            return 0;
        }
        int mid = (begin + end) / 2;
        LL left = countPairs(prefix, begin, mid);
        LL right = countPairs(prefix, mid, end);
        LL self = 0;
        for(int i = begin, j = mid; i < mid; ++ i) {
            for(; j < end && prefix[j] < prefix[i]; ++ j)
                ;
            self += end - j;
        }

        static vector<LL> cache;
        cache.resize(end - begin);
        merge(prefix.begin() + begin, prefix.begin() + mid,
              prefix.begin() + mid, prefix.begin() + end,
              cache.begin()
        );
        copy(cache.begin(), cache.end(), prefix.begin() + begin);
        return left + self + right;
    }
};

int main() {
    Solution s;
    int N;
    LL K;
    cin >> N >> K;
    vector<LL> prefix(N+1);
    for(int i = 1; i <= N; ++ i) {
        cin >> prefix[i];
        prefix[i] += prefix[i-1];
    }
    for(int i = 1; i <= N; ++ i) {
        prefix[i] -= K * i;
    }
    cout << s.solve(prefix) << endl;
    return 0;
}
