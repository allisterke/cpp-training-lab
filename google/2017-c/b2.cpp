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
int square[MAX_N][MAX_N];

class Solution {
public:
	long long int count_squares(int R, int C) {
		for(int i = 0; i <= C; ++ i) {
			square[0][C] = 0;
		}
		for(int i = 0; i < R; ++ i) {
			square[i][0] = 0;
		}

		long long int total = 0;
		for(int i = 0; i < R; ++ i) {
			for(int j = 0; j < C; ++ j) {
				if(grid[i][j]) {
					square[i][j] = 0;
				}
				else {
					square[i][j] = min(min(square[i-1][j], square[i][j-1]), square[i-1][j-1]) + 1;
				}
				total += square[i][j];
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
