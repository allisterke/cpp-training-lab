#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct hashForBoard {
    size_t operator()(const vector<string> &board) const {
        size_t hashed = 0;
        std::hash<string> sh;
        for(auto &row : board) {
            hashed = hashed * 31 + sh(row);
        }
        return hashed;
    }
};

class Solution {
public:
    bool check(int N, const vector<string> &board) {
        for(int i = 0; i < N; ++ i) {
            if(board[i][i] != 'X' || board[i][N-1-i] != 'X') {
                return false;
            }
        }
        return true;
    }
    bool solve(int N, const vector<string> &board) {
        vector<vector<pair<int, int>>> rows(N), cols(N);
        for(int i = 0; i < N; ++ i) {
            for(int j = 0; j < N; ++ j) {
                if(board[i][j] == 'X') {
                    rows[i].emplace_back(i, j);
                    cols[j].emplace_back(i, j);
                }
            }
        }
        for(int i = 0; i < N; ++ i) {
            switch (rows[i].size()) {
                case 0:
                    break;
                case 1:
                    if(cols[rows[i].front().second].size() != 1) {
                        return false;
                    }
                    cols[rows[i].front().second].clear();
                    rows[i].clear();
                    break;
                case 2: {
                    int j = rows[i].back().second;
                    if (cols[j].size() != 2) {
                        return false;
                    }
                    int r = cols[j].back().first;
                    if (rows[r].size() != 2) {
                        return false;
                    }
                    if (rows[r].front().second != rows[i].front().second) {
                        return false;
                    }
                    cols[rows[i].front().second].clear();
                    cols[rows[i].back().second].clear();
                    rows[i].clear();
                    rows[r].clear();
                    break;
                }
                default: {
                    return false;
                }
            }
        }
        return true;
    }
    bool solve0(int N, const vector<string> &board) {
        unordered_set<vector<string>, hashForBoard> visited;
        queue<vector<string>> q{{board}};
        while (!q.empty()) {
            auto &front = q.front();
            if(check(N, front)) {
                return true;
            }
            for(int i = 0; i < N; ++ i) {
                for(int j = i+1; j < N; ++ j) {
                    auto next = front;
                    swap(next[i], next[j]);
                    if(visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            for(int i = 0; i < N; ++ i) {
                for(int j = i+1; j < N; ++ j) {
                    auto next = front;
                    for(int k = 0; k < N; ++ k) {
                        swap(next[k][i], next[k][j]);
                    }
                    if(visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            q.pop();
        }
        return false;
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;
    int N;
    for(int i = 1; i <= T; ++ i) {
        cin >> N;
        vector<string> board(N);
        for(auto &row : board) {
            cin >> row;
        }
        printf("Case #%d: %s\n", i, s.solve(N, board) ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return 0;
}
