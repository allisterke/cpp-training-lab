#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;
pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct Node {
    bitset<64> r;
    int n;
};

class Solution {
public:
    int topbit(bitset<64> &r) {
        int t = 63;
        for(; !r[t]; -- t) ;
        return t;
    }

    int solve(vector<LL> &nodes) {
        vector<Node> bnodes(nodes.size());
        for(int i = 0; i < nodes.size(); ++ i) {
            auto &bnode = bnodes[i];
            bnodes[i].r = nodes[i];
            int &t = bnode.n;
            t = 63;
            for(; !bnode.r[t]; -- t) ;
            for(int i = 0, j = t; i < j; ++i, --j) {
                bool tmp = bnode.r[i];
                bnode.r[i] = bnode.r[j];
                bnode.r[j] = tmp;
            }
        }
        return calculate(bnodes, 0, nodes.size(), 1);
    }

    int calculate(vector<Node> &bnodes, int b, int e, int n) {
        if(b+1 == e) {
            return bnodes[b].n - n + 1;
        }
        else {
            vector<Node> split[2];
            for(int i = b; i < e; ++ i) {
                auto &bnode = bnodes[i];
                if(bnode.n >= n) {
                    split[bnode.r[n]].push_back(bnode);
                }
            }
            copy(begin(split[0]), end(split[0]), begin(bnodes) + b);
            copy(begin(split[1]), end(split[1]), begin(bnodes) + e - split[1].size());
            int s1 = split[0].size();
            split[0].clear();
            int s2 = split[1].size();
            split[1].clear();
            int total = 0;
            if(s1 != 0) {
                total += 1 + calculate(bnodes, b, b + s1, n+1);
            }
            if(s2 != 0) {
                total += 1 + calculate(bnodes, e - s2, e, n+1);
            }
            return total;
        }
    }
};

void test() {
    Solution s;
    vector<vector<LL>> nodesList{
            {6, 7},
            {10},
            {3, 4, 5},
            {10, 6, 2, 15}
    };
    for(auto &nodes : nodesList) {
        cout << s.solve(nodes) << endl;
    }
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<LL> nodes(N);
    for(auto &n : nodes) {
        cin >> n;
    }
    cout << s.solve(nodes) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
