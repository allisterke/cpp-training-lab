#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

auto leftMost = [](int N, int M, int i, int j, vector<string> &maze) -> pair<int, int> {
    int x = j-1;
    for(; x >= 0 && maze[i][x] != '#'; -- x) {
        if(maze[i][x] == 'T') {
            return make_pair(i, x);
        }
    }
    return make_pair(i, x+1);
};
auto rightMost = [](int N, int M, int i, int j, vector<string> &maze) -> pair<int, int> {
    int x = j+1;
    for(; x < M && maze[i][x] != '#'; ++ x) {
        if(maze[i][x] == 'T') {
            return make_pair(i, x);
        }
    }
    return make_pair(i, x-1);
};
auto upMost = [](int N, int M, int i, int j, vector<string> &maze) -> pair<int, int> {
    int x = i-1;
    for(; x >= 0 && maze[x][j] != '#'; -- x) {
        if(maze[x][j] == 'T') {
            return make_pair(x, j);
        }
    }
    return make_pair(x+1, j);
};
auto downMost = [](int N, int M, int i, int j, vector<string> &maze) -> pair<int, int> {
    int x = i+1;
    for(; x < N && maze[x][j] != '#'; ++ x) {
        if(maze[x][j] == 'T') {
            return make_pair(x, j);
        }
    }
    return make_pair(x-1, j);
};

class Solution {
public:
    int solve(int N, int M, vector<string> &maze) {
        for(int i = 0; i < N; ++ i) {
            for(int j = 0; j < M; ++ j) {
                if(maze[i][j] == 'S') {
                    return leastTurn(N, M, i, j, maze);
                }
            }
        }
        return -1;
    }

    int leastTurn(int N, int M, int i, int j, vector<string> &maze) {
        vector<vector<int>> dist(N, vector<int>(M, -1));
        dist[i][j] = 0;
        queue<pair<int, int>> q;
        q.emplace(i, j);
        function<pair<int, int>(int, int, int, int, vector<string> &)> foo[] = { leftMost, rightMost, upMost, downMost };
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            for(auto &f : foo) {
//            for(int k = 0; k < 4; ++ k) {
//                auto &f = foo[k];
                tie(i, j) = f(N, M, front.first, front.second, maze);
                if(dist[i][j] == -1) {
                    dist[i][j] = dist[front.first][front.second] + 1;
                    if(maze[i][j] == 'T') {
                        return dist[i][j] - 1;
                    }
                    q.emplace(i, j);
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    int N, M;
    while(cin >> N >> M) {
        vector<string> maze(N);
        for (auto &row : maze) {
            cin >> row;
        }
        cout << s.solve(N, M, maze) << endl;
    }
    return 0;
}
