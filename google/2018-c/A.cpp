#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    string solve(const string &W) {
        if(W.length() & 1) {
            return "AMBIGUOUS";
        }
        else {
            string w = W;
            for(auto &c : w) {
                c -= 'A';
            }
            for(int i = 2; i < w.size(); i += 2) {
                w[i] = (w[i] - w[i-2] + 26) % 26;
            }
            for(int i = w.size() - 3; i > 0; i -= 2) {
                w[i] = (w[i] - w[i+2] + 26) % 26;
            }
            for(auto &c : w) {
                c += 'A';
            }
            for(int i = 0; i < w.size(); i += 2) {
                swap(w[i], w[i+1]);
            }
            return w;
        }
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;
    string W;
    for(int i = 1; i <= T; ++ i) {
        cin >> W;
        printf("Case #%d: %s\n", i, s.solve(W).c_str());
    }
    return 0;
}
