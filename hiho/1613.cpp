#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

struct Ink {
    int X, Y, G;
    bool operator<(const Ink &b) const {
        return G < b.G;
    }
};
class Solution {
public:
    vector<vector<int>> solve(int N, vector<Ink> &inks) {
        priority_queue<Ink> qu(begin(inks), end(inks));
        vector<vector<int>> board(N, vector<int>(N, 0));
        while (!qu.empty()) {
            auto top = qu.top();
            qu.pop();
            if(board[top.X][top.Y] != 0 || top.G == 0) {
                continue;
            }
            board[top.X][top.Y] = top.G;
            pair<int, int> directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
            for(int i = 0; i < 4; ++ i) {
                int x = top.X + directions[i].first;
                int y = top.Y + directions[i].second;
                if(x >= 0 && x < N && y >= 0 && y < N) {
                    int g = top.G - 1;
                    qu.push({x, y, g});
                }
            }
        }
        return board;
    }
};

void test() {
    Solution s;
    int N = 3;
    vector<Ink> inks{
            {0, 0, 10},
            {2, 2, 10}
    };
    auto board = s.solve(N, inks);
    for(auto &row : board) {
        for(int i = 0; i < row.size(); ++ i) {
            if(i) {
                cout << ' ';
            }
            cout << row[i];
        }
        cout << endl;
    }
}

void run() {
    Solution s;
    int N, K;
    cin >> N >> K;
    vector<Ink> inks(K);
    for(auto &ink : inks) {
        cin >> ink.X >> ink.Y >> ink.G;
    }
    auto board = s.solve(N, inks);
    for(auto &row : board) {
        for(int i = 0; i < row.size(); ++ i) {
            if(i) {
                cout << ' ';
            }
            cout << row[i];
        }
        cout << endl;
    }
}

int main() {
//    test();
    run();
    return 0;
}
