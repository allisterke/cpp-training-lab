#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
private:
    bool checkVanishable(int N, LL A, LL B, const vector<LL> &hs, int K) {
        LL C = A - B;
        LL sum = 0;
        for(auto h : hs) {
            LL hi = h - K * B;
            if(hi > 0) {
                sum += hi / C;
                sum += hi % C > 0;
            }
        }
        return sum <= K;
    }
public:
    LL solve(int N, LL A, LL B, const vector<LL> &hs) {
        LL low = 0, high = numeric_limits<int>::max();
        while (low < high) {
            LL mid = (low + high) / 2;
            if(checkVanishable(N, A, B, hs, mid)) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }
        return high;
    }
};

int main() {
    Solution s;
    int N;
    LL A, B;
    cin >> N >> A >> B;
    vector<LL> hs(N);
    for(auto &h : hs) {
        cin >> h;
    }
    cout << s.solve(N, A, B, hs) << endl;
    return 0;
}
