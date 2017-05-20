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

class Solution {
public:
void try_band(vector<Band> &bs, int index, int a, int b, vector<Band> &cmb, long long int cost, int length, int dollar, vector<Band> &best_cmb, long long int &best_cost) {
	if(a <= length && length <= b && cost < best_cost && cost <= dollar) {
		best_cmb = cmb;
		best_cost = cost;
	}
	else if(index < bs.size()) {
		auto &band = bs[index];
		int a1 = a + get<0>(band);
		int b1 = b + get<1>(band);
		int c1 = cost + get<2>(band);

		if(a1 <= length) {
	
			cmb.push_back(band);
	
			try_band(bs, index + 1, a1, b1, cmb, c1, length, dollar, best_cmb, best_cost);
	
			cmb.pop_back();
		}

		try_band(bs, index + 1, a, b, cmb, cost, length, dollar, best_cmb, best_cost);
	} 
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

		sort(bs.begin(), bs.end(), [](const Band &a, const Band &b) {
			return get<0>(a) < get<0>(b) || get<0>(a) == get<0>(b) && get<2>(a) < get<2>(b);
		});

		vector<Band> best_cmb, cmb;
		long long int best_cost = numeric_limits<long long int>::max(), cost;

		s.try_band(bs, 0, 0, 0, cmb, 0, L, M, best_cmb, best_cost);

		printf("Case #%d: ", i);

		if(best_cost != numeric_limits<long long int>::max()) {
			cout << best_cost << endl;
//			for(auto &band : best_cmb) {
//				cout << '\t' << get<0>(band) << '\t' << get<1>(band) << '\t' << get<2>(band) << endl;
//			}
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}

	}
    return 0;
}



