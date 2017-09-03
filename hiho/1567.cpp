#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    vector<int> find_leaves(map<int, set<int>> &graph) {
        vector<int> leaves;
        for(auto &kv : graph) {
            if(kv.second.size() == 1) {
                leaves.push_back(kv.first);
            }
        }
        return leaves;
    }

    int cut(map<int, set<int>> &graph, int N) {
        auto leaves = find_leaves(graph);
        vector<int> weight(N+1, 1);
        int total = 0;
        while(!leaves.empty()) {
            vector<int> next;
            for(auto leaf : leaves) {
                int parent = *graph[leaf].begin();
                graph[parent].erase(leaf);
                if(graph[parent].size() == 1) {
                    next.push_back(parent);
                }
                if(weight[leaf] & 1) {
                    weight[parent] += weight[leaf];
                }
                else {
                    ++ total; // one cut
                }
            }
            leaves = move(next);
        }
        return total - 1;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    int a, b;
    map<int, set<int>> tree;
    for(int i = 0; i < N-1; ++ i) {
        cin >> a >> b;
        tree[a].insert(b);
        tree[b].insert(a);
    }
    cout << s.cut(tree, N) << endl;
    return 0;
}
