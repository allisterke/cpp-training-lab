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
    // just like solving an equation: xD*a + (xD+1)*b + (xD+2)*c = N
    // where xD is divisible by D, a >= 1, b >= 0, c >= 0
    // if we fix xD and a with two loop, and let: a + b + c = K
    // then: b+2c = N - K*xD
    // solving this equation gives us that:
    // c = N - K - K*xD + a >= 0 --> K <= (N+a)/(1+xD)
    // b = K - a - c = K - a - N + K + K*xD - a = 2K + K*xD - 2a - N >= 0 --> K >= (N+2a)/(2+xD)
    // so we just count K from lower bound to higher bound to solve this problem
	ULL count(int N, int D) {
		ULL total = 0;
		for(int xD = D; xD <= N; xD += D) {
            for(int a = 1; a*xD <= N; ++ a) {
                int Kl = (N+2*a)/(2+xD);
                if(Kl*(2+xD) < (N+2*a)) {
                    ++ Kl;
                }
                int Kh = (N+a)/(1+xD);
                if(Kl <= Kh) {
                    total += (Kh - Kl + 1);
                }
            }
		}

		return total;
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
