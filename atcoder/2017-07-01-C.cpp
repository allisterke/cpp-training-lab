#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct BinaryIndexedTree {
    vector<LL> tree;
    BinaryIndexedTree(int capacity) : tree(capacity + 1){

    }

    void update(int index, int diff) {
        for(int i = index; i < tree.size(); i += (i & -i)) {
            tree[i] += diff;
        }
    }

    LL query(int limit) {
        LL total = 0;
        for(int i = limit; i; i -= (i & -i)) {
            total += tree[i];
        }
        return total;
    }
};

class Solution {
public:
    LL solve0(int n, int m, vector<int> &a) {
        BinaryIndexedTree b1(m<<1), b2(m<<1), c1(m<<1), c2(m<<1);
        LL cost = 0;
        for(int i = 0; i + 1 < a.size(); ++ i) {
            b1.update(a[i], a[i]);
            c1.update(a[i], 1);
            if(a[i] < a[i+1]) {
                b2.update(a[i+1], a[i]);
                c2.update(a[i+1], 1);
                cost += a[i+1] - a[i];
            }
            else {
                b2.update(a[i+1] + m, a[i]);
                c2.update(a[i+1] + m, 1);
                cost += a[i+1] + m - a[i];
            }
        }
        LL reduce = 0;
        for(int i = 1; i <= m; ++ i) {
            LL r = 0;
            for(int k = 0; k < 2; ++ k) {
                LL j = i + k * m - 1;
                LL t1 = b1.query(j);
                LL k1 = c1.query(j);
                LL t2 = b2.query(j);
                LL k2 = c2.query(j);
                r += (k1 - k2) * j - (t1 - t2);
            }
            reduce = max(reduce, r);
        }
        return cost - reduce;
    }

    LL solve(int n, int m, vector<int> &a) {
        LL cost = numeric_limits<LL>::max();
        for(int i = 1; i <= m; ++ i) {
            LL tc = 0;
            for(int j = 0; j < a.size() - 1; ++ j) {
                if(a[j] < a[j+1]) {
                    if(a[j] < i && i <= a[j+1]) {
                        tc += 1 + a[j+1] - i;
                    }
                    else {
                        tc += a[j+1] - a[j];
                    }
                }
                else {
                    if(a[j] < i || i <= a[j+1]) {
                        if(a[j] < i) {
                            tc += 1 + a[j+1] + m - i;
                        }
                        else {
                            tc += 1 + a[j+1] - i;
                        }
                    }
                    else {
                        tc += a[j+1] + m - a[j];
                    }
                }
            }
            cost = min(cost, tc);
        }
        return cost;
    }
};

void test1() {
    Solution s;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &ai : a) {
        cin >> ai;
    }
    cout << s.solve0(n, m, a) << endl;
//    cout << s.solve(n, m, a) << endl;
}

void test2() {
    Solution s;
    int a = 1, b = int(6);
    auto g = bind(uniform_int_distribution<int>{a, b}, default_random_engine{random_device{}()});
    for(int i = 0; i < 100; ++ i) {
        int n = g();
        int m = b;
        vector<int> a(n);
        int last = -1;
        for(auto &ai : a) {
            int n = g() % m + 1;
            while (n == last) {
                n = g() % m + 1;
            }
            ai = n;
            last = n;
        }
        if(s.solve(n, m, a) == s.solve0(n, m, a)) {
            cout << "case " << i << ": pass" << endl;
        }
        else {
            cout << n << ' ' << m << endl;
            for(auto ai : a) {
                cout << ai << ' ';
            }
            cout << endl;
            cout << s.solve0(n, m, a) << endl;
            cout << s.solve(n, m, a) << endl;
            break;
        }
    }
}

int main() {
    test1();
//    test2();
    return 0;
}
