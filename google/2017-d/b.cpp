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

class Solution {
public:
void try_put(vector<vector<int>> &current, int i, int j, int count, int R, int C, vector<vector<int>> &best_square, int &best_count) {
	if(i >= R || j >= C) {
		return;
	}

	// set point
	current[i][j] = 1;
	if(check_valid(current, i, j, R, C)) {
		if(i + 1 == R && j + 1 == C) { // last point finished
			check_best(current, count+1, best_square, best_count);
		}
		else {
			try_put(current, j+1 == C ? i+1 : i, j+1 == C ? 0 : j+1, count+1, R, C, best_square, best_count);
		}
	}

	// do not set point
	current[i][j] = 0;
	if(i + 1 == R && j + 1 == C) { // last point finished
		check_best(current, count, best_square, best_count);
	}
	else {
		try_put(current, j+1 == C ? i+1 : i, j+1 == C ? 0 : j+1, count, R, C, best_square, best_count);
	}
}

bool check_valid(vector<vector<int>> &current, int i, int j, int R, int C) {
	return check_row_valid(current, i, j, R, C) && check_column_valid(current, i, j, R, C);
}

inline bool check_row_valid(vector<vector<int>> &current, int i, int j, int R, int C) {
	return j < 2 || !current[i][j-1] || !current[i][j-2];
}

inline bool check_column_valid(vector<vector<int>> &current, int i, int j, int R, int C) {
	return i < 2 || !current[i-1][j] || !current[i-2][j];
}

void check_best(vector<vector<int>> &current, int count, vector<vector<int>> &best_square, int &best_count) {
	if(count > best_count) {
		best_square = current;
		best_count = count;
	}
}
};

int main() {

	int T, R, C;
	cin >> T;

	for(int i = 1; i <= T; ++ i) {
		cin >> R >> C;
	
		vector<vector<int>> current(R, vector<int>(C));
		auto best_square = current;
		int count = 0;
		auto best_count = count;
	
		Solution().try_put(current, 0, 0, count, R, C, best_square, best_count);

		printf("Case #%d: %d\n", i, best_count);

		for(auto &v : best_square) {
			for(auto n : v) {
				cout << n << '\t';
			}
			cout << endl;
		}

	}

	return 0;
}
