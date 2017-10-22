#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

struct Segment {
    int begin, end, value;
};

struct SegmentTreeForMin {
    vector<Segment> tree;
    SegmentTreeForMin(int capacity) : tree{capacity << 2} {
        init(0, 0, capacity);
    }
    SegmentTreeForMin(const vector<int> &h) : tree(h.size() << 2) {
        init(0, 0, h.size(), h);
    }
    void init(int root, int begin, int end, const vector<int> &h) {
        tree[root] = {begin, end, numeric_limits<int>::max()};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid, h);
            init(root * 2 + 2, mid, end, h);
            tree[root].value = min(tree[root * 2 + 1].value, tree[root * 2 + 2].value);
        }
        else {
            tree[root].value = h[begin];
        }
    }
    void init(int root, int begin, int end) {
        tree[root] = {begin, end, numeric_limits<int>::max()};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid);
            init(root * 2 + 2, mid, end);
        }
    }
    void update(int root, int index, int value) {
        if(tree[root].begin <= index && tree[root].end > index) {
            if(tree[root].begin + 1 == tree[root].end) {
                tree[root].value = value;
            }
            else {
                update(root * 2 + 1, index, value);
                update(root * 2 + 2, index, value);
                tree[root].value = min(tree[root * 2 + 1].value, tree[root * 2 + 2].value);
            }
        }
    }

    int query(int root, int begin, int end) {
        if(tree[root].begin >= end || tree[root].end <= begin) {
            return numeric_limits<int>::max();
        }
        else if(tree[root].begin >= begin && tree[root].end <= end){
            return tree[root].value;
        }
        else {
            return min(query(root * 2 + 1, begin, end), query(root * 2 + 2, begin, end));
        }
    }
};

struct SegmentTreeForMax {
    vector<Segment> tree;
    SegmentTreeForMax(int capacity) : tree{capacity << 2} {
        if(capacity > 0) {
            init(0, 0, capacity);
        }
    }
    SegmentTreeForMax(const vector<int> &h) : tree(h.size() << 2) {
        if(h.size()) {
            init(0, 0, h.size(), h);
        }
    }
    void init(int root, int begin, int end, const vector<int> &h) {
        tree[root] = {begin, end, numeric_limits<int>::min()};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid, h);
            init(root * 2 + 2, mid, end, h);
            tree[root].value = max(tree[root * 2 + 1].value, tree[root * 2 + 2].value);
        }
        else {
            tree[root].value = h[begin];
        }
    }
    void init(int root, int begin, int end) {
        tree[root] = {begin, end, numeric_limits<int>::min()};
        if(begin + 1 != end) {
            int mid = (begin + end) / 2;
            init(root * 2 + 1, begin, mid);
            init(root * 2 + 2, mid, end);
        }
    }
    void update(int root, int index, int value) {
        if(tree[root].begin <= index && tree[root].end > index) {
            if(tree[root].begin + 1 == tree[root].end) {
                tree[root].value = value;
            }
            else {
                update(root * 2 + 1, index, value);
                update(root * 2 + 2, index, value);
                tree[root].value = max(tree[root * 2 + 1].value, tree[root * 2 + 2].value);
            }
        }
    }

    int query(int root, int begin, int end) {
        if(tree[root].begin >= end || tree[root].end <= begin) {
            return numeric_limits<int>::min();
        }
        else if(tree[root].begin >= begin && tree[root].end <= end){
            return tree[root].value;
        }
        else {
            return max(query(root * 2 + 1, begin, end), query(root * 2 + 2, begin, end));
        }
    }
};

class Solution {
    int TOTAL = 314159;
public:
    int solve(vector<pair<int, int>> &votes, unordered_set<int> &group) {
        sort(begin(votes), end(votes));
        unordered_map<int, int> r = reorder(group);
        vector<int> nvc(TOTAL - group.size()), svc(group.size());
        SegmentTreeForMin stree(svc);
        SegmentTreeForMax ntree(nvc);
        int totalTime = 0;
        for(int i = 0, j = 0; i < votes.size(); i = j) {
            for(j = i; j < votes.size() && votes[j].first == votes[i].first; ++ j) {
                if(group.find(votes[j].second) != group.end()) {
                    ++ svc[r[votes[j].second]];
                    stree.update(0, r[votes[j].second], svc[r[votes[j].second]]);
                }
                else {
                    ++ nvc[r[votes[j].second]];
                    ntree.update(0, r[votes[j].second], nvc[r[votes[j].second]]);
                }
            }
            bool valid = stree.query(0, 0, svc.size()) > (nvc.size() ? ntree.query(0, 0, nvc.size()) : -1);
            if(valid) {
                if(j < votes.size()) {
                    totalTime += votes[j].first - votes[i].first;
                }
            }
        }
        return totalTime;
    }

    unordered_map<int, int> reorder(unordered_set<int> &group) {
        unordered_map<int, int> r;
        int normal = 0, special = 0;
        for(int i = 1; i <= TOTAL; ++ i) {
            if(group.find(i) != group.end()) {
                r[i] = special ++;
            }
            else {
                r[i] = normal ++;
            }
        }
        return r;
    };
};

void test() {
    Solution s;
    vector<pair<int, int>> votes {
            {3,1}, {4,1}, {5,1}, {4,3}, {6,5}, {8,3}, {7,5}, {8,5}, {9,1}, {10,5}
    };
    unordered_set<int> group{1, 2, 3, 4, 5};
    cout << s.solve(votes, group) << endl;
}

void run() {
    Solution s;
    int N, K;
    cin >> N >> K;
    vector<pair<int, int>> votes(N);
    for(auto &vote : votes) {
        cin >> vote.first >> vote.second;
    }
    unordered_set<int> group;
    while(K -- > 0) {
        int sp;
        cin >> sp;
        group.insert(sp);
    }
    cout << s.solve(votes, group) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
