#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

class Solution {
public:
    pair<int, int> solve(vector<int> &A) {
        vector<int> r(A.size());
        unordered_set<int> distinct;
        for(int i = A.size() - 1, last = A.size(); i >= 0; -- i) {
            for(-- last; last >= 0; -- last) {
                if(distinct.find(A[last]) == distinct.end()) {
                    distinct.insert(A[last]);
                }
                else {
                    break;
                }
            }
            r[i] = ++ last;
            distinct.erase(A[i]);
        }
        vector<int> f(A.size());
        for(int i = 0; i < A.size(); ++ i) {
            if(r[i] == 0) {
                f[i] = 1;
            }
            else {
                f[i] = f[r[i] - 1] + 1;
            }
        }
        vector<int> sp(f.back() + 1);
        vector<int> ep(f.back() + 1);
        for(int i = 0, j = 0; i < f.size(); i = j) {
            for(j = i+1; j < f.size() && f[j] == f[i]; ++ j) ;
            sp[f[i]] = i;
            ep[f[i]] = j-1;
        }
        vector<int> g(A.size());
        vector<int> s(A.size());
        for(int i = 0; i < A.size(); ++ i) {
            if(r[i] == 0) {
                g[i] = 1;
            }
            else {
//                for(int k = r[i] - 1; k <= ep[f[i] - 1]; ++ k) {
//                    g[i] += g[k];
//                }
                if(r[i] > 1) {
                    g[i] = (s[ep[f[i] - 1]] + MOD - s[r[i] - 2]) % MOD;
                }
                else {
                    g[i] = s[ep[f[i] - 1]];
                }
            }
            if(i == 0) {
                s[i] = g[i];
            }
            else {
                s[i] = (s[i-1] + g[i]) % MOD;
            }
        }
        return make_pair(f.back(), g.back());
    }

    pair<int, int> solve0(vector<int> &A) {
        vector<int> f(A.size() + 1);
        vector<vector<int>> g(A.size() + 1);
        for(int i = 0; i < A.size(); ++ i) {
            f[i+1] = f[i] + 1;
            unordered_set<int> s{A[i]};
            g[i+1].push_back(i);
            for(int j = i-1; j >= 0; -- j) {
                if(s.find(A[j]) == s.end()) {
                    s.insert(A[j]);
                    if(f[j] + 1 == f[i+1]) {
                        g[i+1].push_back(j);
                    }
                    else if(f[j] + 1 < f[i+1]) {
                        g[i+1].clear();
                        g[i+1].push_back(j);
                        f[i+1] = f[j] + 1;
                    }
                }
                else {
                    break;
                }
            }
        }
        vector<int> F(A.size() + 1);
        F[0] = 1;
        for(int i = 0; i < A.size(); ++ i) {
            for(int j : g[i+1]) {
                F[i+1] += F[j];
                F[i+1] %= MOD;
            }
        }
        return make_pair(f.back(), F.back());
    }
};

void test() {
    Solution s;
    vector<int> A{1, 2, 3, 1, 2, 1};
    auto p = s.solve(A);
    cout << p.first << ' ' << p.second << endl;
}

void compare_test() {
    Solution s;
    int N = 6;
    vector<int> A(N);
    default_random_engine g(random_device{}());
    for(int i = 0; i < 10; ++ i) {
        for (auto &a : A) {
            a = g();
        }
        auto p1 = s.solve(A);
        auto p2 = s.solve0(A);
        if(p1 != p2) {
            cout << p1.first << ' ' << p1.second << endl;
            cout << p2.first << ' ' << p2.second << endl;
            break;
        }
    }
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<int> A(N);
    for(auto &a : A) {
        cin >> a;
    }
    auto p = s.solve(A);
    cout << p.first << ' ' << p.second << endl;
}

int main() {
//    test();
    run();
//    compare_test();
    return 0;
}
