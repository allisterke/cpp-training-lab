#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

struct Segment {
    int begin, end, value;
};

struct SegmentTreeForCount {
    vector<Segment> tree;
    SegmentTreeForCount(int capacity) : tree{capacity << 2} {
        init(0, 0, capacity);
    }
    SegmentTreeForCount(const vector<int> &h) : tree(h.size() << 2) {
        init(0, 0, h.size(), h);
    }
    void init(int root, int begin, int end, const vector<int> &h) {
        tree[root] = {begin, end, numeric_limits<int>::max()};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid, h);
            init(root * 2 + 2, mid, end, h);
            tree[root].value = tree[root * 2 + 1].value + tree[root * 2 + 2].value;
        }
        else {
            tree[root].value = h[begin];
        }
    }
    void init(int root, int begin, int end) {
        tree[root] = {begin, end, 0};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid);
            init(root * 2 + 2, mid, end);
        }
    }
    void update(int root, int index, int value) {
        if(tree[root].begin <= index && tree[root].end > index) {
            if(tree[root].begin + 1 == tree[root].end) {
                tree[root].value += value;
            }
            else {
                update(root * 2 + 1, index, value);
                update(root * 2 + 2, index, value);
                tree[root].value = tree[root * 2 + 1].value + tree[root * 2 + 2].value;
            }
        }
    }

    int query(int root, int begin, int end) {
        if(tree[root].begin >= end || tree[root].end <= begin) {
            return 0;
        }
        else if(tree[root].begin >= begin && tree[root].end <= end){
            return tree[root].value;
        }
        else {
            return query(root * 2 + 1, begin, end) + query(root * 2 + 2, begin, end);
        }
    }
};

class Solution {
public:
    LL solve(vector<int> &A) {
        LL total = 0;
        sort(begin(A), end(A));
        for(int i = 0; i < A.size(); ++ i) {
            double low = A[i] / 8.0 + 8;
            double high = A[i] * 8 + 8;
            if(A[i] < 88888) {
                high = min(high, 88888.);
            }
            total += distance(lower_bound(begin(A), end(A), low),
                              upper_bound(begin(A), end(A), high));
            if(A[i] >= low && A[i] <= high) {
                -- total;
            }
        }
        return total;
    }
};

void test() {
    Solution s;
    vector<int> A{10, 80};
    cout << s.solve(A) << endl;
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<int> A(N);
    for(auto &a : A) {
        cin >> a;
    }
    cout << s.solve(A) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
