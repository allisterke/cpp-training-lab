#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL MOD = 1e9 + 7;

class Solution {
public:
    vector<int> solve(int n, vector<int> &c) {
        int i, j;
        tie(i, j) = find_dup(c);
        ++ i;
        ++ j;
        ++ n;
        LL a = n, b = 1;
        vector<int> result(n);
        result[0] = n - 1;
        for(int k = 2; k <= n; ++ k) {
            a = comb(a, n, k);
            if(k <= i-1+n-j+1) {
                b = comb(b, i-1+n-j, k-1);
            }
            else {
                b = 0;
            }
            result[k-1] = (a - b + MOD) % MOD;
        }
        return result;
    }

    LL comb(LL a, LL n, LL k) {
        LL r = fast_power(k, MOD - 2);
        r *= a;
        r %= MOD;
        r *= n - k + 1;
        r %= MOD;
        return r;
    }

    LL fast_power(LL a, LL b) {
        if(b == 0) {
            return 1;
        }
        LL r = fast_power(a, b >> 1);
        r *= r;
        r %= MOD;
        if(b & 1) {
            r *= a;
            r %= MOD;
        }
        return r;
    }

    pair<int, int> find_dup(vector<int> &a) {
        vector<char> occurrences(a.size());
        for(auto ai : a) {
            ++ occurrences[ai];
        }
        int n = distance(begin(occurrences), find(begin(occurrences), end(occurrences), 2));
        int i = distance(begin(a), find(begin(a), end(a), n));
        int j = distance(begin(a), find(begin(a) + i + 1, end(a), n));
        return make_pair(i, j);
    };
};

int main() {
    Solution s;
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(auto &ai : a) {
        cin >> ai;
    }
    for(auto bi : s.solve(n, a)) {
        cout << bi << endl;
    }
    return 0;
}
