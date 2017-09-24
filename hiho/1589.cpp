#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct Segment {
    int begin, end, value;
};

struct SegmentTree {
    vector<Segment> tree;
    SegmentTree(int capacity) : tree{capacity << 2} {
        init(0, 0, capacity);
    }
    SegmentTree(const vector<int> &h) : tree(h.size() << 2) {
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

class Solution {
public:
    LL solve0(const string &str) {
        LL total = 0;
        vector<vector<int>> dp(str.size(), vector<int>(str.size()));
        for(int k = 0; k < str.size(); ++ k) {
            for(int i = 0; i + k < str.size(); ++ i) {
                if(k == 0) {
                    dp[i][i+k] = true;
                }
                else if(k == 1) {
                    dp[i][i+k] = str[i] == str[i+k];
                }
                else {
                    dp[i][i+k] = dp[i+1][i+k-1] && str[i] == str[i+k];
                }
                if(dp[i][i+k]) {
                    ++ total;
                }
            }
        }
        return total;
    }

    LL solve(const string &s) {
        string str = "*";
        for(auto c : s) {
            str.push_back(c);
            str.push_back('*');
        }
        vector<int> cache(str.size());
        LL total = 0;
        int last = -1;
        for(int i = 1; i + 1 < str.size(); ++ i) {
            if(last == -1 || i > last + cache[last]) {
                int j = 1;
                for(; i+j < str.size() && i-j >= 0 && str[i-j] == str[i+j]; ++ j);
                last = i;
                cache[i] = j-1;
            }
            else {
                int k = 2 * last - i;
                if(cache[k] < last + cache[last] - i) {
                    cache[i] = cache[k];
                }
                else {
                    int j = last + cache[last] - i;
                    for(; i+j < str.size() && i-j >= 0 && str[i-j] == str[i+j]; ++ j);
                    last = i;
                    cache[i] = j-1;
                }
            }
            if(str[i] == '*') {
                total += (cache[i] + 1) / 2;
            }
            else {
                total += cache[i] / 2 + 1;
            }
        }
        return total;
    }

    LL solve1(const string &s) {
        string str = "*";
        for(auto c : s) {
            str.push_back(c);
            str.push_back('*');
        }
        str += "#" + string(str.rbegin(), str.rend());

        vector<int> cnta(max((int)str.size() + 1, 128)),
                cntb(max((int)str.size() + 1, 128)),
                sa(str.size()),
                tsa(str.size()),
                rank(str.size()),
                ranka(str.size()),
                rankb(str.size());
        for(auto c : str) {
            ++ cnta[c];
        }
        for(int i = 1; i < cnta.size(); ++ i) {
            cnta[i] += cnta[i - 1];
        }
        for(int i = str.size() - 1; i >= 0; -- i) {
            sa[-- cnta[str[i]]] = i;
        }
        rank[sa[0]] = 1;
        for(int i = 1; i < str.size(); ++ i) {
            rank[sa[i]] = rank[sa[i-1]];
            if(str[sa[i]] != str[sa[i-1]]) {
                ++ rank[sa[i]];
            }
        }
        for(int k = 1; k < str.size(); k <<= 1) {
            for(int i = 0; i < cnta.size(); ++ i) {
                cnta[i] = 0;
                cntb[i] = 0;
            }
            for(int i = 0; i < str.size(); ++ i) {
                ++ cnta[ranka[i] = rank[i]];
                ++ cntb[rankb[i] = i + k < str.size() ? rank[i + k] : 0];
            }
            for(int i = 1; i < cnta.size(); ++ i) {
                cnta[i] += cnta[i-1];
                cntb[i] += cntb[i-1];
            }
            for(int i = str.size() - 1; i >= 0; -- i) {
                tsa[-- cntb[rankb[i]]] = i;
            }
            for(int i = str.size() - 1; i >= 0; -- i) {
                sa[-- cnta[ranka[tsa[i]]]] = tsa[i];
            }
            rank[sa[0]] = 1;
            for(int i = 1; i < str.size(); ++ i) {
                rank[sa[i]] = rank[sa[i-1]];
                if(ranka[sa[i]] != ranka[sa[i-1]] || rankb[sa[i]] != rankb[sa[i-1]]) {
                    ++ rank[sa[i]];
                }
            }
        }
        vector<int> height(str.size());
        for(int i = 0; i < str.size(); ++ i) {
            int index = rank[i] - 1;
            if(index == 0) {
                continue;
            }
            int o1 = sa[index - 1], o2 = sa[index];
            int j = i > 0 ? max(height[rank[i-1] - 1] - 1, 0) : 0;
            for(; o1 + j < str.size() && o2 + j < str.size() && str[o1 + j] == str[o2 + j]; ++ j);
            height[index] = j;
        }

//        SegmentTree tree(height.size());
//        for(int i = 0; i < height.size(); ++ i) {
//            tree.update(0, i, height[i]);
//        }
        LL total = 0;
        SegmentTree tree(height);
        for(int i = 1; str[i+1] != '#'; ++ i) {
            int o1 = rank[i+1];
            int o2 = rank[str.size() - i];
            if(o1 > o2) {
                swap(o1, o2);
            }
            int k = tree.query(0, o1, o2);
            if(str[i] == '*') {
                total += (k + 1) / 2;
            }
            else {
                total += k / 2 + 1;
            }
        }
        return total;
    }

    inline vector<int> first_order(const string &str) {
        set<int> cs(begin(str), end(str));
        vector<int> cso{begin(cs), end(cs)};
        map<int, int> com;
        for(int i = 0; i < cso.size(); ++ i) {
            com[cso[i]] = i+1;
        }
        vector<int> order(str.size());
        for(int i = 0; i < order.size(); ++ i) {
            order[i] = com[str[i]];
        }
        return order;
    }
};

void test() {
    Solution s;
//    cout << s.solve("a") << endl;
    cout << s.solve("abbab") << endl;
//    cout << s.solve1("abbab") << endl;
}

void extreme_test() {
    Solution s;
    int N = 8e5;
    string str(N, 'a');
    cout << s.solve(str) << endl;
    cout << s.solve1(str) << endl;
}

void run() {
    Solution s;
    string str;
    cin >> str;
    cout << s.solve(str) << endl;
}

int main() {
//    extreme_test();
//    test();
    run();
    return 0;
}
