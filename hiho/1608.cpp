#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

class Solution {
public:
    int solve(int N, int M, int K, vector<string> &maze, vector<pair<int, int>> &cheeses) {
        cheeses.emplace_back(0, 0);
        cheeses.emplace_back(N-1, M-1);
        for(auto &p : cheeses) {
            if(maze[p.first][p.second] == '1') {
                return -1;
            }
        }
        vector<vector<int>> dist(cheeses.size(), vector<int>(cheeses.size()));
        for(int i = 0; i < cheeses.size(); ++ i) {
            for(int j = i+1; j < cheeses.size(); ++ j) {
                int d = bfs(maze, cheeses[i].first, cheeses[i].second, cheeses[j].first, cheeses[j].second);
                if(d < 0) {
                    return -1;
                }
                dist[i][j] = dist[j][i] = d;
            }
        }
        int shortest = numeric_limits<int>::max();
        vector<int> visited(cheeses.size());
        dfs(cheeses.size() - 2, cheeses.size() - 1, dist, visited, 0, shortest);
        return shortest;
    }

    void dfs(int i, int r, vector<vector<int>> &dist, vector<int> &visited, int d, int &shortest) {
        visited[i] = true;
        if(r == 1) {
            shortest = min(shortest, d + dist[i][visited.size() - 1]);
        }
        else {
            for (int j = 0; j < visited.size() - 1; ++ j) {
                if(!visited[j]) {
                    dfs(j, r-1, dist, visited, d + dist[i][j], shortest);
                }
            }
        }
        visited[i] = false;
    }

    int bfs(vector<string> &maze, int si, int sj, int ei, int ej) {
        if(si == ei && sj == ej) {
            return 0;
        }
        vector<vector<int>> dist(maze.size(), vector<int>(maze[0].size(), -1));
        dist[si][sj] = 0;
        queue<pair<int, int>> qu{{{si, sj}}};
        while(!qu.empty()) {
            int x, y;
            tie(x, y) = qu.front();
            qu.pop();
            pair<int, int> directions[] = {
                    {0, 1},
                    {0, -1},
                    {1, 0},
                    {-1, 0}
            };
            for(auto dir : directions) {
                int i = x + dir.first;
                int j = y + dir.second;
                if(i >= 0 && j >= 0 && i < maze.size() && j < maze[0].size() &&
                        maze[i][j] == '0' && dist[i][j] == -1) {
                    dist[i][j] = dist[x][y] + 1;
                    qu.emplace(i, j);
                }
            }
            if(dist[ei][ej] > 0) {
                break;
            }
        }
        return dist[ei][ej];
    }
};

void test1() {
    Solution s;
    vector<string> maze{
            "01000",
            "01010",
            "00010",
            "01010",
            "00000"
    };
    vector<pair<int, int>> cheeses{{0, 4}, {2, 2}, {4, 0}};
    cout << s.solve(maze.size(), maze[0].size(), cheeses.size(), maze, cheeses) << endl;
}

void test2() {
    Solution s;
    vector<string> maze{
            "00"
    };
    vector<pair<int, int>> cheeses{};
    cout << s.solve(maze.size(), maze[0].size(), cheeses.size(), maze, cheeses) << endl;
}

void run() {
    Solution s;
    int N, M, K;
    cin >> N >> M >> K;
    vector<string> maze(N);
    for(auto &s : maze) {
        cin >> s;
    }
    vector<pair<int, int>> cheeses(K);
    for(auto &p : cheeses) {
        cin >> p.first >> p.second;
    }
    cout << s.solve(N, M, K, maze, cheeses) << endl;
}

int main() {
//    test1();
    run();
    return 0;
}
