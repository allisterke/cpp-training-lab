#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

int main() {
    Solution s;
    int N;
    cin >> N;
    vector<int> V(N);
    for(auto &v : V) {
        cin >> v;
    }
    vector<int> P(N);
    vector<vector<int>> C(N);
    for(int i = 1; i < N; ++ i) {
        cin >> P[i];
        -- P[i];
        C[P[i]].push_back(i);
    }
    unordered_set<int> leaves;
    for(int i = 0; i < N; ++ i) {
        if(C[i].empty()) {
            leaves.insert(i);
        }
    }
    vector<int> M{V};
    while(!leaves.empty()) {
        unordered_set<int> next;
        for(auto leaf : leaves) {
            next.insert(P[leaf]);
            M[P[leaf]] = min(M[P[leaf]], M[leaf]);
        }
        next.erase(0);
        leaves = move(next);
    }
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; ++ i) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, u;
            cin >> x >> u;
            -- x;
            V[x] = u;
            do {
                M[x] = V[x];
                for(auto c : C[x]) {
                    M[x] = min(M[x], M[c]);
                }
                if(x == P[x]) {
                    break;
                }
                x = P[x];
            } while(true) ;
        }
        else {
            int x;
            cin >> x;
            -- x;
            cout << M[x] << endl;
        }
    }
    return 0;
}
