#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;
pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

class Solution {
public:
    int solve(vector<vector<int>> matrix) {
        int N = matrix.size();
        vector<int> csum(N);
        for(int i = 0; i < N; ++ i) {
            for(int j = 0; j < N; ++ j) {
                csum[j] += matrix[i][j];
            }
        }
        int negative = 0;
        for(auto &cs : csum) {
            if(cs < 0) {
                ++ negative;
                cs = -cs;
            }
        }
        int asum = accumulate(begin(csum), end(csum), 0);
        if(negative & 1) {
            return asum - *min_element(begin(csum), end(csum)) * 2;
        }
        else {
            return asum;
        }
    }
};

void test() {
    Solution s;
    vector<vector<int>> matrix{
            {-1,1,-9,2},
            {-2,-3,1,2},
            {-3,-2,1,2},
            {-4,-1,1,2}
    };
    cout << s.solve(matrix) << endl;
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<vector<int>> matrix(N, vector<int>(N));
    for(int i = 0; i < N; ++ i) {
        for(int j = 0; j < N; ++ j) {
            cin >> matrix[i][j];
        }
    }
    cout << s.solve(matrix) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
