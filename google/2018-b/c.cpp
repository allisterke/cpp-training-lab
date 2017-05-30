#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
	int solve(int M, int N, int K, vector<string> &board) {
		int opt = 0;
        unordered_map<int, int> cache;
		for(int i = 0; i < M; ++ i) {
            for(int j = 0; j < N; ++ j) {
                opt = max(opt, dfs(i, j, K, M, N, board, cache));
            }
		}
		return opt;
	}

	int dfs(int i, int j, int k, int M, int N, vector<string> &board,
            unordered_map<int, int> &cache) {
		if(k <= 0) {
			return 0;
		}
        int key = (i << 16) | (j << 8) | k;
        if(cache.find(key) == cache.end()) {
            --k;
            int opt = -1;
            for (int h = 0; i + h < M; ++h) {
                int r = i + h;
                bool filled = true;
                for (int c = j - h; c <= j + h; ++c) {
                    if (c < 0 || c >= N || board[r][c] != '#') {
                        filled = false;
                        break;
                    }
                }
                if (!filled) {
                    break;
                }
                ++r;
                for (int c = j - h; c <= j + h; ++c) {
                    int o = dfs(r, c, k, M, N, board, cache);
                    if (o >= 0) {
                        opt = max(opt, o + (h + 1) * (h + 1));
                    }
                }
            }
            cache[key] = opt;
        }
        return cache[key];
	}
};

int main() {
	int T;
	cin >> T;

	Solution s;

	for(int i = 1; i <= T; ++ i) {
		int M, N, K;
		cin >> M >> N >> K;
		vector<string> board(M);
		for(auto &line : board) {
			cin >> line;
		}
		printf("Case #%d: %d\n", i, s.solve(M, N, K, board));
	}
    return 0;
}
