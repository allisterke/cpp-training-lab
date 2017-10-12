#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

class Solution {
public:
    pair<int, int> solve(int n) {
        if(n > 3) {
            int p = 2;
            for(; p<=sqrt(n) && n%p; ++ p) ;
            if(n%p) {
                p = n;
            }
            if(p % 3 != 2) {
                for(int i = 2; i <= n; ++ i) {
                    if(i % p) {
                        int phi = LL(n) * (p-1) / p;
                        while (true) {
                            int a = fast_pow(i, phi, n);
                            if(a != 1) {
                                int b = LL(a) * a % n;
                                if(a > b) {
                                    swap(a, b);
                                }
                                return make_pair(a, b);
                            }
                            if(phi % 3) {
                                break;
                            }
                            phi /= 3;
                        }
                    }
                }
            }
        }
        return make_pair(0, 0);
    }

    int fast_pow(int n, int e, int m) {
        if(e == 0) {
            return 1;
        }
        LL r = fast_pow(n, e >> 1, m);
        r *= r;
        r %= m;
        if(e & 1) {
            r *= n;
            r %= m;
        }
        return r;
    }
};

void test() {
    Solution s;
    auto p = s.solve(7);
    cout << p.first << ' ' << p.second << endl;
}

void run() {
    Solution s;
    int T;
    cin >> T;
    while(T -- > 0) {
        int N;
        cin >> N;
        auto p = s.solve(N);
        if(p.first) {
            cout << 1 << ' ' << p.first << ' ' << p.second << endl;
        }
        else {
            cout << -1 << endl;
        }
    }
}

int main() {
//    test();
    run();
    return 0;
}
