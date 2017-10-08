#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL MOD = 1000000007;

class Solution {
public:
    int solve0(int n) {
        LL f = 0, F = 0;
        for(int i = 1; i <= n; ++ i) {
            f = (f + F + 1) % MOD;
            F = (F + f) % MOD;
        }
        return f;
    }

    int solve(int n) {
        vector<vector<LL>> m{{1, 1, 1}, {1, 2, 1}, {0, 0, 1}};
        m = fastPow(m, n);
        return m[0].back();
    }

    vector<vector<LL>> matmul(const vector<vector<LL>> &a, const vector<vector<LL>> &b) {
        vector<vector<LL>> c(a.size(), vector<LL>(b[0].size()));
        for(int i = 0; i < c.size(); ++ i) {
            for(int j = 0; j < c[0].size(); ++ j) {
                for(int k = 0; k < b.size(); ++ k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
                c[i][j] %= MOD;
            }
        }
        return c;
    }

    vector<vector<LL>> fastPow(const vector<vector<LL>> &a, int n) {
        if(n == 0) {
            auto m = a;
            for(int i = 0; i < a.size(); ++ i) {
                for(int j = 0; j < a.size(); ++ j) {
                    m[i][j] = i == j;
                }
            }
            return m;
        }
        else {
            auto m = fastPow(a, n >> 1);
            m = matmul(m, m);
            if (n & 1) {
                m = matmul(m, a);
            }
            return m;
        }
    }
};

void test() {
    Solution s;
}

void run() {
    Solution s;
    int n;
    while(cin >> n) {
        cout << s.solve(n) << endl;
    }
}

int main() {
//    test();
    run();
    return 0;
}
