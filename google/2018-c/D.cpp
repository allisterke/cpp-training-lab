#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    string solve(int MIN, int MAX, int AVG, int MID) {
        int count = numeric_limits<int>::max();
        if(MIN <= AVG && MIN <= MID && AVG <= MAX && MID <= MAX) {
            if (MIN == MAX) {
                count = 1;
            }
            else if (AVG * 2 == MIN + MAX && AVG == MID) {
                count = 2;
            }
            else if (MIN + MID + MAX == AVG * 3) {
                count = 3;
            }
            else if(MIN + MAX + 2 * MID == AVG * 4) {
                count = 4;
            }
            else {
                count = min(tryOdd(MIN, MAX, AVG, MID), tryEven(MIN, MAX, AVG, MID));
            }
        }
        return count != numeric_limits<int>::max() ? to_string(count) : "IMPOSSIBLE";
    }

    int tryOdd(int MIN, int MAX, int AVG, int MID) {
        int A1 = 2 * AVG - MIN - MID;
        int A2 = 2 * AVG - MID - MAX;
        if(A1 <= 0 || A2 >= 0) { // impossible
            return numeric_limits<int>::max();
        }
        int A3 = MIN + MID + MAX - 3 * AVG;
        return 3 + 2 * max(max(ceil(1.0 * A3 / A1), 1.),
                           max(ceil(1.0 * A3 / A2), 1.));
    }

    int tryEven(int MIN, int MAX, int AVG, int MID) {
        int A1 = 2 * AVG - MIN - MID;
        int A2 = 2 * AVG - MID - MAX;
        if(A1 <= 0 || A2 >= 0) { // impossible
            return numeric_limits<int>::max();
        }
        int A3 = MIN + MAX + 2 * MID - 4 * AVG;
        return 4 + 2 * max(max(ceil(1.0 * A3 / A1), 1.),
                           max(ceil(1.0 * A3 / A2), 1.));
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;
    int MIN, MAX, AVG, MID;
    for(int i = 1; i <= T; ++ i) {
        cin >> MIN >> MAX >> AVG >> MID;
        printf("Case #%d: %s\n", i, s.solve(MIN, MAX, AVG, MID).c_str());
    }
    return 0;
}
