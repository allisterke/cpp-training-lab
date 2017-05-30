#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
private:
public:
    bool solve(vector<string> &board, vector<vector<vector<bool>>> &mark, vector<function<int(int, int)>> &foo) {
        for(int i = 0; i < 9; ++ i) {
            for(int j = 0; j < 9; ++ j) {
                if(board[i][j] == '.') {
                    for(char c = '1'; c <= '9'; ++ c) {
                        bool occupied = false;
                        for(int k = 0; k < 3; ++ k) {
                            int x = foo[k](i, j);
                            int y = c - '1';
                            if(mark[k][x][y]) {
                                occupied = true;
                                break;
                            }
                        }
                        if(occupied) {
                            continue;
                        }

                        board[i][j] = c;
                        for(int k = 0; k < 3; ++ k) {
                            int x = foo[k](i, j);
                            int y = c - '1';
                            mark[k][x][y] = true;
                        }
                        if(solve(board, mark, foo)) {
                            return true;
                        }
                        for(int k = 0; k < 3; ++ k) {
                            int x = foo[k](i, j);
                            int y = c - '1';
                            mark[k][x][y] = false;
                        }
                        board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<string> board {
            "179542.8.",
            "..26....7",
            ".481..5..",
            "......2.6",
            ".3.....7.",
            "2.1......",
            "..3..476.",
            "8....19..",
            ".2.365418"
    };
    vector<vector<vector<bool>>> mark(3, vector<vector<bool>>(9, vector<bool>(9)));
    vector<function<int(int, int)>> foo {
            [](int i, int j) -> int { return i; },
            [](int i, int j) -> int { return j; },
            [](int i, int j) -> int { return i/3*3+j/3; }
    };
    for(int i = 0; i < 9; ++ i) {
        for(int j = 0; j < 9; ++ j) {
            if(board[i][j] == '.') {
                continue;
            }
            for(int k = 0; k < 3; ++ k) {
                int x = foo[k](i, j);
                int y = board[i][j] - '1';
                mark[k][x][y] = true;
            }
        }
    }
    if(s.solve(board, mark, foo)) {
        for(int i = 0; i < 9; ++ i) {
            cout << board[i] << endl;
        }
    }
    else {
        cout << "No solution" << endl;
    }
    return 0;
}
