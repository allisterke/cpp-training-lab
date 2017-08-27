#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<LL> &sticks) {
        map<LL, LL> sc;
        for(auto stick : sticks) {
            ++ sc[stick];
        }
        vector<double> dsl;
        vector<LL> dsc;
        for(auto &kv : sc) {
            dsl.push_back(kv.first);
            dsc.push_back(kv.second);
        }
        vector<LL> comb2{0}, acc{0};
        for(auto &c : dsc) {
            comb2.push_back(c * (c-1) / 2 + comb2.back());
            acc.push_back(c + acc.back());
        }
        LL total = 0;
        for(int i = 0; i < dsl.size(); ++ i) {
            for(int j = i+1; j < dsl.size(); ++ j) {
                double L1 = dsl[i];
                double L2 = dsl[j];
                double L3 = (L2 - L1) / 2;
                int k = upper_bound(dsl.begin(), dsl.end(), L3) - dsl.begin();
//                for(; k < dsl.size(); ++ k) {
//                    if(k != i && k != j) {
//                        total += dsc[i] * dsc[j] * dsc[k] * (dsc[k] - 1) / 2;
//                    }
//                }
                total += dsc[i] * dsc[j] * ((comb2[dsl.size()] - comb2[k])
                                            - (k <= i) * (comb2[i+1] - comb2[i])
                                            - (k <= j) * (comb2[j+1] - comb2[j]));
            }
            if(dsc[i] >= 3) {
                double L = dsl[i] * 3;
                int limit = lower_bound(dsl.begin() + i + 1, dsl.end(), L) - dsl.begin();
//                for(int k = 0; k < limit; ++ k) {
//                    if(k != i) {
//                        total += dsc[i] * (dsc[i] - 1) * (dsc[i] - 2) / 6 * dsc[k];
//                    }
//                }
                total += dsc[i] * (dsc[i] - 1) * (dsc[i] - 2) / 6 * (acc[limit] - dsc[i]);
            }
        }
        return total;
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;

    for(int i = 1; i <= T; ++ i) {
        int N;
        cin >> N;
        vector<LL> sticks(N);
        for(auto &stick : sticks) {
            cin >> stick;
        }
        printf("Case #%d: %lld\n", i, s.solve(sticks));
    }
    return 0;
}
