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
	ULL count(const string &s, ULL I, ULL J) {
		vector<int> blue(s.length(), 0);
		int acc = 0;
		for(int i = 0; i < s.length(); ++ i) {
			blue[i] = (s[i] == 'B') ? (++ acc) : acc;
		}

		-- I;
		-- J;

		ULL total = 0;
		ULL start = I % s.length();
		ULL end = I - start + s.length();

		if(end >= J) {
			return blue[J % s.length()] - (start == 0 ? 0 :blue[start - 1]);
		}

		total += blue.back() - (start == 0 ? 0 : blue[start - 1]);

		total += blue.back() * (J / s.length() - I / s.length() - 1);

		total += blue[J % s.length()];

		return total; 
	}
};

int main() {
	int T;
	cin >> T;

	string S;
	ULL I, J;
	Solution s;

	for(int i = 1; i <= T; ++ i) {
		cin >> S >> I >> J;
		printf("Case #%d: ", i);
		cout << s.count(S, I, J) << endl;
	}
    return 0;
}
