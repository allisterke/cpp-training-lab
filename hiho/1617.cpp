#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;
pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

class Solution {
public:
    int solve(vector<vector<int>> &board) {
        int N = board.size();
        vector<vector<vector<int>>> dp(N*2-1, vector<vector<int>>(N, vector<int>(N)));
        dp[0][0][0] = board[0][0] * 2;
        for(int k = 1; k < 2*N - 1; ++ k) {
            for(int i = max(0, k - N + 1); i <= min(k, N-1); ++ i) {
                for(int j = i; j <= min(k, N-1); ++ j) {
                    for(int p = -1; p <= 0; ++ p) {
                        for(int q = -1; q <= 0; ++ q) {
                            int x = i+p;
                            int y = j+q;
                            if(x >= 0 && k - x >= 0 && y >= 0 && k - y >= 0 && (k == 1 || x != y)) {
                                dp[k][i][j] = max(dp[k][i][j], dp[k - 1][x][y]);
                            }
                        }
                    }
                    dp[k][i][j] += board[i][k-i] + board[j][k-j];
                }
            }
        }
        return dp.back().back().back();
    }
};

void test() {
    Solution s;
    vector<vector<int>> board{
            {1, 2, 3, 4},
            {2, 3, 4, 5},
            {5, 3, 2, 1},
            {2, 4, 6, 2},
    };
    cout << s.solve(board) << endl;
}

void run() {
    Solution s;
    int N;
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    for(int i = 0; i < N; ++ i) {
        for(int j = 0; j < N; ++ j) {
            cin >> board[i][j];
        }
    }
    cout << s.solve(board) << endl;
}

int main() {
//    test();
    run();
    return 0;
}
