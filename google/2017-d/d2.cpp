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

using Band = tuple<int, int, long long int>;

const int MAX_L = 10001;

long long int cost[MAX_L];

class Solution {
public:
int try_band(vector<Band> &bs, int N, int M, int L) {
	memset(cost, 0, (L+1)*sizeof(cost[0]));
	cost[0] = 1;

	for(int i = 0; i < N; ++ i) {
		int a, b;
		long long int c;
		tie(a, b, c) = bs[i];

		for(int j = L; j >= 0; -- j) {
			if(cost[j]) {
				int nc = cost[j] + c;
				if(nc > M)
					continue;

				for(int k = 0; a + k <= b && a + j + k <= L; ++ k) {
					int index = a + j + k;
					if(cost[index] == 0 || nc < cost[index]) {
						cost[index] = nc;
					}
				}
			}
		}
	}

	return cost[L];
}

};

int main() {
	int T, N, M, L;
	Solution s;

	cin >> T;

	for(int i = 1; i <= T; ++ i) {
		cin >> N >> M >> L;
		vector<Band> bs(N);
		for(int j = 0; j < N; ++ j) {
			cin >> get<0>(bs[j]) >> get<1>(bs[j]) >> get<2>(bs[j]);
		}

//		sort(bs.begin(), bs.end(), [](const Band &a, const Band &b) {
//			return get<0>(a) < get<0>(b) || get<0>(a) == get<0>(b) && get<2>(a) < get<2>(b);
//		});

		printf("Case #%d: ", i);

		int cost = s.try_band(bs, N, M, L);

		if(cost) {
			cout << cost - 1 << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
    return 0;
}



