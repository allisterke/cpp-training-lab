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

using ULL = unsigned long long int;
constexpr int MAX_N = 2001;
constexpr int MAX_D = 101;

// ULL cache[MAX_N][MAX_D];

class Solution {
public:
	ULL count(int N, int D) {
		ULL total = 0;
		for(int i = D; i <= N; i += D) {
			ULL tmp = 0;
			count_r(i, i, N - i, 0, tmp);
			total += tmp;
		}

		return total;
	}

	void count_r(int start, int prev, int remain, int level, ULL &total) {
		if(remain < 0) {
			return;
		}
//		for(int i = 0; i < level; ++ i) {
//			cout << '\t';
//		}
//		cout << prev << endl;

		if(remain == 0) {
//			cout << '!' << endl;
			++ total;
			return;
		}
		for(int i = prev; i <= start + 2 && i <= remain; ++ i) {
			count_r(start, i, remain - i, level+1, total);
		}
	} 

};

int main() {
	int T;
	cin >> T;
	int N, D;

	Solution s;

	for(int i = 1; i <= T; ++ i) {
		cin >> N >> D;

		printf("Case #%d: ", i);
		cout << s.count(N, D) << endl;
	}

    return 0;
}
