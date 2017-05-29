#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<int> &A) {
        return countInvertedPairs(A, 0, A.size());
    }

    LL countInvertedPairs(vector<int> &A, int begin, int end) {
        if(begin+1 >= end) {
            return 0;
        }
        int mid = (begin + end) / 2;
        LL left = countInvertedPairs(A, begin, mid);
        LL right = countInvertedPairs(A, mid, end);
        LL self = 0;
        for(int i = begin, j = mid; i < mid; ++ i) {
            for(; j < end && A[j] < A[i]; ++ j)
                ;
            self += j - mid;
        }
        static vector<int> cache;
        cache.resize(end - begin);
        merge(A.begin() + begin, A.begin() + mid, A.begin() + mid, A.begin() + end, cache.begin());
        copy(cache.begin(), cache.end(), A.begin() + begin);
        return left + right + self;
    }
};

int main() {
    Solution s;
    int N;
    while (cin >> N) {
        vector<int> A(N);
        for(auto &a : A) {
            cin >> a;
        }
        cout << s.solve(A) << endl;
    }
    return 0;
}
