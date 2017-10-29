#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;
pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

class Solution {
    struct Status {
        int status;
        int mi, ma;
    };
public:
    string solve(int N, vector<pair<int, int>> &pcmap) {
        int root = getRoot(N, pcmap);
        if(root < 0) {
            return "ERROR1";
        }
        vector<vector<int>> childNodes(N);
        bool binary = true;
        for(auto &pc : pcmap) {
            if(childNodes[pc.first].size() >= 2) {
                binary = false;
            }
            childNodes[pc.first].push_back(pc.second);
        }
        if(!visitAll(root, childNodes)) {
            return "ERROR1";
        }
        else if(!binary) {
            return "ERROR2";
        }
        if(checkBST(root, childNodes).status) {
            string builder;
            stringifyBST(root, childNodes, builder);
            return builder;
        }
        else {
            return "ERROR3";
        }
    }

    void stringifyBST(int root, vector<vector<int>> &childNodes, string &builder) {
        builder += "(";
        builder += to_string(root+1);
        switch (childNodes[root].size()) {
            case 0:
                builder += "()()";
                break;
            case 1:
                if(childNodes[root][0] < root) {
                    stringifyBST(childNodes[root][0], childNodes, builder);
                    builder += "()";
                }
                else {
                    builder += "()";
                    stringifyBST(childNodes[root][0], childNodes, builder);
                }
                break;
            case 2:
                stringifyBST(childNodes[root][0], childNodes, builder);
                stringifyBST(childNodes[root][1], childNodes, builder);
                break;
        }
        builder += ")";
    }

    Status checkBST(int root, vector<vector<int>> &childNodes) {
        if(childNodes[root].empty()) {
            return {true, root, root};
        }
        if(childNodes[root].size() == 1) {
            int child = childNodes[root][0];
            auto status = checkBST(child, childNodes);
            if(status.status && (child < root && status.ma < root || child > root && status.mi > root)) {
                return {true, min(root, status.mi), max(root, status.ma)};
            }
        }
        else {
            int left = childNodes[root][0];
            int right = childNodes[root][1];
            auto s1 = checkBST(left, childNodes);
            if(s1.status && s1.ma < root) {
                auto s2 = checkBST(right, childNodes);
                if(s2.status && s2.mi > root) {
                    return {true, s1.mi, s2.ma};
                }
            }
        }
        return {false, 0, 0};
    }

    bool visitAll(int root, vector<vector<int>> &childNodes) {
        vector<int> visited(childNodes.size(), false);
        dfs(root, childNodes, visited);
        return find(begin(visited), end(visited), false) == end(visited);
    }
    void dfs(int root, vector<vector<int>> &childNodes, vector<int> &visited) {
        visited[root] = true;
        if(childNodes[root].size() == 2) {
            sort(begin(childNodes[root]), end(childNodes[root]));
        }
        for(auto child : childNodes[root]) {
            dfs(child, childNodes, visited);
        }
    }
    int getRoot(int N, vector<pair<int, int>> &pcmap) {
        vector<int> hasParent(N, false);
        for(auto &pc : pcmap) {
            hasParent[pc.second] = true;
        }
        auto it = find(begin(hasParent), end(hasParent), false);
        return find(it+1, end(hasParent), false) == end(hasParent) ? it - begin(hasParent) : -1;
    }
};

void test() {
    Solution s;
    vector<int> ns{3, 4, 3, 3};
    vector<vector<pair<int, int>>> pcmaps {
            {{1, 2}, {3, 2}},
            {{1, 2}, {1, 3}, {1, 4}},
            {{1, 2}, {1, 3}},
            {{2, 1}, {2, 3}}
    };
    for(int i = 0; i < ns.size(); ++ i) {
        for(auto &pc : pcmaps[i]) {
            -- pc.first;
            -- pc.second;
        }
        cout << s.solve(ns[i], pcmaps[i]) << endl;
    }
}

void run() {
    Solution s;
    int T;
    cin >> T;
    while(T -- > 0) {
        int N;
        cin >> N;
        vector<pair<int, int>> pcmap(N-1);
        for(auto &pc : pcmap) {
            cin >> pc.first;
            -- pc.first;
            cin >> pc.second;
            -- pc.second;
        }
        cout << s.solve(N, pcmap) << endl;
    }
}

int main() {
//    test();
    run();
    return 0;
}
