#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    double solve(string &str, string &b) {
        for(auto &c : b) {
            c = c == '0' ? '1' : '0';
        }
        if(str.size() == 1) {
            return str[0] == b[0] ? 1 : 0;
        }
        vector<int> cnta(str.size() + 1),
                cntb(str.size() + 1),
                sa(str.size()),
                tsa(str.size()),
                rank(str.size()),
                ranka(str.size()),
                rankb(str.size());
        for(auto c : str) {
            ++ cnta[c - '0'];
        }
        cnta[1] += cnta[0];
        for(int i = str.size() - 1; i >= 0; -- i) {
            sa[-- cnta[str[i] - '0']] = i;
        }
        rank[sa[0]] = 1;
        for(int i = 1; i < str.size(); ++ i) {
            rank[sa[i]] = rank[sa[i-1]];
            if(str[sa[i]] != str[sa[i-1]]) {
                ++ rank[sa[i]];
            }
        }
        for(int k = 1; k < str.size(); k <<= 1) {
            for(int i = 0; i <= str.size(); ++ i) {
                cnta[i] = 0;
                cntb[i] = 0;
            }
            for(int i = 0; i < str.size(); ++ i) {
                ++ cnta[ranka[i] = rank[i]];
                ++ cntb[rankb[i] = i + k < str.size() ? rank[i + k] : 0];
            }
            for(int i = 1; i <= str.size(); ++ i) {
                cnta[i] += cnta[i-1];
                cntb[i] += cntb[i-1];
            }
            for(int i = str.size() - 1; i >= 0; -- i) {
                tsa[-- cntb[rankb[i]]] = i;
            }
            for(int i = str.size() - 1; i >= 0; -- i) {
                sa[-- cnta[ranka[tsa[i]]]] = tsa[i];
            }
            rank[sa[0]] = 1;
            for(int i = 1; i < str.size(); ++ i) {
                rank[sa[i]] = rank[sa[i-1]];
                if(ranka[sa[i]] != ranka[sa[i-1]] || rankb[sa[i]] != rankb[sa[i-1]]) {
                    ++ rank[sa[i]];
                }
            }
        }
        vector<int> height(str.size());
        for(int i = 0; i < str.size(); ++ i) {
            int index = rank[i] - 1;
            if(index == 0) {
                continue;
            }
            int o1 = sa[index - 1], o2 = sa[index];
            int j = i > 0 ? max(height[rank[i-1] - 1] - 1, 0) : 0;
            for(; o1 + j < str.size() && o2 + j < str.size() && str[o1 + j] == str[o2 + j]; ++ j);
            height[index] = j;
        }
        LL total = 0;
        int common = 0;
        for(int i = 0; i < str.size(); ++ i) {
            if(i == 0) {
                int j = 0;
                int o = sa[i];
                for(; o+j < str.size() && j < b.size() && str[o+j] == b[j]; ++ j);
                common = j;
            }
            else {
                if(common != height[i]) {
                    common = min(common, height[i]);
                }
                else {
                    int j = common;
                    int o = sa[i];
                    for(; o+j < str.size() && j < b.size() && str[o+j] == b[j]; ++ j);
                    common = j;
                }
            }
            total += 1LL * common * (common + 1) / 2;
            if(str.size() != sa[i] + common) {
                total += 1LL * common * (str.size() - sa[i] - common);
            }
        }
        LL base = 1LL * str.length() * (str.length()+1) / 2;
//        cout << "total: " << total << endl;
//        cout << "base: " << base << endl;
//        cout << total << "*1000/" << base << "/1000.0" << endl;

        return 1.0 * total / base;
    }

    double solve0(string &str, string &b) {
        for(auto &c : b) {
            c = c == '0' ? '1' : '0';
        }
        vector<int> cache(str.size());
        iota(begin(cache), end(cache), 0);

        vector<int> current_order = first_order(str);
        vector<int> merged_next_order(str.size());
        for(int k = 2; k/2 < str.size(); k <<= 1) {
            vector<int> next_order{cache};
//            make_heap(begin(next_order), end(next_order), [&](int a, int b) -> bool {
//                if(current_order[a] < current_order[b]) {
//                    return true;
//                }
//                else if(current_order[a] == current_order[b]) {
//                    int n1 = a + k/2 < str.size() ? current_order[a + k/2] : 0;
//                    int n2 = b + k/2 < str.size() ? current_order[b + k/2] : 0;
//                    return n1 < n2;
//                }
//                else {
//                    return false;
//                }
//            });
            sort(begin(next_order), end(next_order), [&](int a, int b) -> bool {
                if(current_order[a] < current_order[b]) {
                    return true;
                }
                else if(current_order[a] == current_order[b]) {
                    int n1 = a + k/2 < str.size() ? current_order[a + k/2] : 0;
                    int n2 = b + k/2 < str.size() ? current_order[b + k/2] : 0;
                    return n1 < n2;
                }
                else {
                    return false;
                }
            });
            for(int i = 0, j = 0; i < str.size(); ++ i) {
                if(i == 0) {
                    ++ j;
                }
                else {
                    int a = next_order[i-1], b = next_order[i];
                    if(current_order[a] != current_order[b]) {
                        ++ j;
                    }
                    else {
                        int n1 = a + k/2 < str.size() ? current_order[a + k/2] : 0;
                        int n2 = b + k/2 < str.size() ? current_order[b + k/2] : 0;
                        if(n1 != n2) {
                            ++ j;
                        }
                    }
                }
                merged_next_order[next_order[i]] = j;
            }
//            current_order = move(merged_next_order);
            swap(current_order, merged_next_order);
        }
        vector<int> sa(str.size());
        for(int i = 0; i < str.size(); ++ i) {
            sa[current_order[i] - 1] = i;
        }
        vector<int> height(str.size());
        for(int i = 0; i < str.size(); ++ i) {
            int index = current_order[i] - 1;
            if(index == 0) {
                continue;
            }
            int o1 = sa[index - 1], o2 = sa[index];
            int j = i > 0 ? max(height[current_order[i-1] - 1] - 1, 0) : 0;
            for(; o1 + j < str.size() && o2 + j < str.size() && str[o1 + j] == str[o2 + j]; ++ j);
            height[index] = j;
        }
        LL total = 0;
        int common = 0;
        for(int i = 0; i < str.size(); ++ i) {
            if(i == 0) {
                int j = 0;
                int o = sa[i];
                for(; o+j < str.size() && j < b.size() && str[o+j] == b[j]; ++ j);
                common = j;
            }
            else {
                if(common != height[i]) {
                    common = min(common, height[i]);
                }
                else {
                    int j = common;
                    int o = sa[i];
                    for(; o+j < str.size() && j < b.size() && str[o+j] == b[j]; ++ j);
                    common = j;
                }
            }
            total += 1LL * common * (common + 1) / 2;
            if(str.size() != sa[i] + common) {
                total += 1LL * common * (str.size() - sa[i] - common);
            }
        }
        LL base = 1LL * str.length() * (str.length()+1) / 2;
//        cout << "total: " << total << endl;
//        cout << "base: " << base << endl;
//        cout << total << "*1000/" << base << "/1000.0" << endl;

        return 1.0 * total / base;
    }

    inline vector<int> first_order(const string &str) {
        set<int> cs(begin(str), end(str));
        vector<int> cso{begin(cs), end(cs)};
        map<int, int> com;
        for(int i = 0; i < cso.size(); ++ i) {
            com[cso[i]] = i+1;
        }
        vector<int> order(str.size());
        for(int i = 0; i < order.size(); ++ i) {
            order[i] = com[str[i]];
        }
        return order;
    }

    double solve1(string &a, string &b) {
        LL total = 0;
        for(int k = 1; k <= a.length(); ++ k) {
            for(int i = 0; i + k <= a.length(); ++ i) {
                int j = 0;
                for(; j < k && j < b.length() && a[i+j] != b[j]; ++ j) ;
                if(j) {
                    total += j;
                }
            }
        }
        return 1.0 * total * 2 / a.length() / (a.length()+1);
    }
};

void test() {
    vector<string> a = {"00110", "010101", "0", "00000"};
    vector<string> b = {"10000", "101011", "0", "11111"};
    Solution s;
    for(int i = 0; i < a.size(); ++ i) {
        cout << s.solve1(a[i], b[i]) << endl;
        cout << s.solve(a[i], b[i]) << endl;
    }
}

void extreme_test() {
    string a, b;
    default_random_engine g(random_device{}());
    int na = 1e4, nb = 1e3;
//    int na = 5, nb = 3;
    for (int i = 0; i < na; ++i) {
//        a.push_back(g() % 2 ? '1' : '0');
        a.push_back('1');
    }
    for (int i = 0; i < nb; ++i) {
//        b.push_back(g() % 2 ? '1' : '0');
//        b.push_back('1');
        b.push_back('0');
    }
//    b.front() = '0';
//    b.back() = '0';
//    b[b.size() / 2] = '0';
    Solution s;
    double x = s.solve1(a, b);
    double y = s.solve(a, b);
//    cout << y << endl;
    cout << x << '\t' << y << endl;
}

void random_test() {
    for(int i = 0; i < 10000; ++ i) {
        string a, b;
        default_random_engine g(random_device{}());
        int na = 12, nb = 10;
        for (int i = 0; i < na; ++i) {
//            a.push_back(g() % 2 ? '1' : '0');
            a.push_back('1');
        }
        for (int i = 0; i < nb; ++i) {
//            b.push_back(g() % 2 ? '1' : '0');
            b.push_back('1');
        }
        Solution s;
        double x = s.solve1(a, b), y = s.solve(a, b);
        if (abs(x-y) > 1e-3) {
            cout << a << '\t' << x << endl;
            cout << b << '\t' << y << endl;
            break;
        }
    }
}

void run() {
    Solution s;
    int n, m;
    cin >> n >> m;
    string a(n, 0), b(m, 0);
    cin >> a >> b;
//    cout << s.solve(a, b) << endl;
    printf("%.8lf\n", s.solve(a, b));
}

int main() {
//    random_test();
//    extreme_test();
//    test();
    run();
    return 0;
}
