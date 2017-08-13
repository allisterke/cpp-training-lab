#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<int> &a) {
        LL total = 0;
        LL three = count(begin(a), end(a), 3);
        LL one = 0;
        for(auto ai : a) {
            switch (ai) {
                case 1:
                    ++ one;
                    break;
                case 2:
                    total += one * three;
                    break;
                case 3:
                    -- three;
                    break;
            }
        }
        return total;
    }
};

int main() {
    Solution s;
    int N;
    while(cin >> N) {
        vector<int> a(N);
        for(auto &ai : a) {
            cin >> ai;
        }
        cout << s.solve(a) << endl;
    }
    return 0;
}
