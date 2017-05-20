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

class Solution {
public:
	int try_base(ULL N, ULL b, int bits) {
		ULL n = 0;
		for(int i = 0; i < bits; ++ i) {
			ULL nn = n * b + 1;
			if(nn <= n || (nn - 1) / b != n) { // overflow
				return 1;
			}
			else {
				n = nn;
			}
		}

		return n == N ? 0 : (n > N ? 1 : -1);
	}

	ULL base(ULL N) {
		for(int bits = 63; bits >= 1; -- bits) {
			ULL left = 2, right = N - 1;
			while(left <= right) {
				ULL mid = (left + right) >> 1;
				switch(try_base(N, mid, bits)) {
					case 0:
						return mid;
					case -1:
						left = mid + 1;
						break;
					case 1:
						right = mid - 1;
						break;
				}
			}
		}

		return N - 1;
	} 
};

int main() {
	int T;
	cin >> T;

	ULL N;
	Solution s;

	for(int i = 1; i <= T; ++ i) {
		cin >> N;
		printf("Case #%d: ", i);
		cout << s.base(N) << endl;
	}
    return 0;
}
