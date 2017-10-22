#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

struct Circle {
    double x, y, r;
};

class Solution {
public:
    double distance(Circle &c1, Circle &c2) {
        return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
    }
    vector<int> solve(vector<Circle> &circle) {
        vector<int> root(circle.size());
        for(int i = 0; i < circle.size(); ++ i) {
            for(int j = 0; j < circle.size(); ++ j) {
                if(circle[j].r <= circle[i].r) {
                    continue;
                }
                if(distance(circle[i], circle[j]) <= circle[j].r - circle[i].r) {
                    if(root[i] == 0 || circle[j].r < circle[root[i] - 1].r) {
                        root[i] = j + 1;
                    }
                }
            }
        }
        return root;
    }
};

void test() {
    Solution s;
    vector<Circle> circles{
            {5,5,5},
            {1.58,5,1.49},
            {6.54,5,3.36},
            {5,4.11,1.49},
            {8.08,4.11,1.49},
            {6.54,6.77,1.49}
    };
    for (auto r : s.solve(circles)) {
        cout << r << endl;
    }
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<Circle> circles(N);
    for(auto &c : circles) {
        cin >> c.x >> c.y >> c.r;
    }
    for (auto r : s.solve(circles)) {
        cout << r << endl;
    }
}

int main() {
//    test();
    run();
    return 0;
}
