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
	ULL base(ULL N) {
		for(ULL b = 2; ; ++ b) {
			ULL exp = 2;
			ULL last = 1;
			ULL pr = b;
			for(; ; ++ exp) {
				ULL npr = pr * b;
				if(npr < pr) {
					break;
				}

				pr = npr;

				ULL current = (pr - 1) / (b - 1);
				if(current == N && current * (b - 1) == (pr - 1)) {
					return b;
				}
				else if(current > N) {
					break;
				}
				else if(current < last) { // overflow
					break;
				}
				else {
					last = current;
				}
			}
			if(exp == 2) { // we have but only last choice
				break;
			}
		}
		return N;
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
