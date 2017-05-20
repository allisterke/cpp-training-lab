#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;

constexpr int MAX_N = 3001;
bool grid[MAX_N][MAX_N];
pair<int, int> grid_extent[MAX_N][MAX_N];

class Solution {
public:
	void count_extent(int R, int C) {
		static int row_ext[MAX_N]; 
		memset(row_ext, 0, C*sizeof(row_ext[0]));

		// surround with '1'
		for(int i = 0; i < R; ++ i) {
			grid[i][C] = true;
		}
		for(int i = 0; i < C; ++ i) {
			grid[R][i] = true;
		}
		grid[R][C] = true;

		for(int i = 0; i <= R; ++ i) {
			int ext = 0;
			for(int j = 0; j <= C; ++ j) {
				if(grid[i][j]) {
					for(int k = 1; k <= ext; ++ k) {
						grid_extent[i][j-k].first = k;
					}
					ext = 0;
					for(int k = 1; k <= row_ext[j]; ++ k) {
						grid_extent[i-k][j].second = k;
					}
					row_ext[j] = 0;
				}
				else {
					++ ext;
					++ row_ext[j];
				}

			} 
		}
//
//		for(int i = 0; i < R; ++ i) {
//			for(int j = 0; j < C; ++ j) {
//				if(grid[i][j]) {
//					cout << "0 0";
//				}
//				else {
//					cout << grid_extent[i][j].first << ' ' << grid_extent[i][j].second;
//				}
//				cout << '\t';
//			}
//			cout << endl;
//		}
	}

	long long int count_squares(int R, int C) {
		count_extent(R, C);

		long long int total = 0;
		for(int i = 0; i < R; ++ i) {
			for(int j = 0; j < C; ++ j) {
				if(!grid[i][j]) {
					int ext = min(grid_extent[i][j].first, grid_extent[i][j].second);
					int check_ext = ext;
					for(int k = 1; k < check_ext; ++ k) {
						if(grid[i+k][j+k]) {
							check_ext = k;
							break;
						}
						else {
							int e = min(min(grid_extent[i+k][j+k].first, grid_extent[i+k][j+k].second), check_ext - k);
							check_ext = k + e;
						}
					}
					total += check_ext;
				}
			}
		}

		return total; 
	}
};

int main() {
	int T;
	cin >> T;

	int R, C, K, r, c;
	Solution s;

	for(int i = 1; i <= T; ++ i) {
		cin >> R >> C >> K;
		for(int j = 0; j < R; ++ j) {
			for(int k = 0; k < C; ++ k) {
				grid[j][k] = false;
			}
		}
		for(int j = 0; j < K; ++ j) {
			cin >> r >> c;
			grid[r][c] = true;
		}

		printf("Case #%d: %lld\n", i, s.count_squares(R, C));
	}
    return 0;
}
