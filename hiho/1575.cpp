#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(int N, int M, const vector<string> &maze) {
        if(N == 1 && M == 1 || maze[0][0] == '1' || maze[N-1][M-1] == '1') {
            return -1;
        }
        unordered_map<int, int> visited{{make_key(0, 0, N-1, M-1), 0}};
        queue<tuple<int, int, int, int>> qu{{make_tuple(0, 0, N-1, M-1)}};
        while(!qu.empty()) {
            int i, j, p, q;
            tie(i, j, p, q) = qu.front();
            qu.pop();
            int k = make_key(i, j, p, q);

            // down/up
            int i1 = i+1 < N && maze[i+1][j] == '0' ? i+1 : i;
            int p1 = p-1 >= 0 && maze[p-1][q] == '0' ? p-1 : p;
            // check: moved, not same place, not switch
            if((i1 != i || p1 != p) && !(i1 == p1 && j == q) && !(j == q && i+1 == p)) {
                int k1 = make_key(i1, j, p1, q);
                if(visited.find(k1) == visited.end()) {
                    visited[k1] = visited[k] + 1;
                    qu.push(make_tuple(i1, j, p1, q));
                }
            }
            // right/left
            int j1 = j+1 < M && maze[i][j+1] == '0' ? j+1 : j;
            int q1 = q-1 >= 0 && maze[p][q-1] == '0' ? q-1 : q;
            if((j1 != j || q1 != q) && !(i == p && j1 == q1) && !(i == p && j+1 == q)) {
                int k1 = make_key(i, j1, p, q1);
                if(visited.find(k1) == visited.end()) {
                    visited[k1] = visited[k] + 1;
                    qu.push(make_tuple(i, j1, p, q1));
                }
            }
        }
        int k = make_key(N-1, M-1, 0, 0);
        return visited.find(k) != visited.end() ? visited[k] : -1;
    }

    int make_key(int i, int j, int p, int q) {
        return (i << 24) | (j << 16) | (p << 8) | q;
    }
};

int main() {
    Solution s;
    int N, M;
    cin >> N >> M;
    vector<string> maze(N);
    for(auto &row : maze) {
        cin >> row;
    }
    cout << s.solve(N, M, maze) << endl;
    return 0;
}
