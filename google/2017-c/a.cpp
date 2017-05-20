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

char rect_c[21][21];
double rect_p[21][21];

class Solution {
public:

	void catch_monster(int i, int j, int s, int R, int C, int S, double P, double Q, double expect, double &best_expect, vector<pair<int, int>> &path, vector<pair<int, int>> &best_path, vector<double> &ep, vector<double> &bep) {
		if(s <= S) { 
			if(i < 0 || i >= R || j < 0 || j >= C) {
				return;
			}

			path.push_back(make_pair(i, j));

			double ne = expect;
			double p = rect_p[i][j];
			if(s) {
				ne += p;

				rect_p[i][j] *= (rect_c[i][j] == 'A' ? (1 - P) : (1 - Q));
			} 

			ep.push_back(ne);

			++ s;
			catch_monster(i-1, j, s, R, C, S, P, Q, ne, best_expect, path, best_path, ep, bep);
			catch_monster(i+1, j, s, R, C, S, P, Q, ne, best_expect, path, best_path, ep, bep);
			catch_monster(i, j-1, s, R, C, S, P, Q, ne, best_expect, path, best_path, ep, bep);
			catch_monster(i, j+1, s, R, C, S, P, Q, ne, best_expect, path, best_path, ep, bep);
			-- s;

			ep.pop_back();

			if(s) {
				rect_p[i][j] = p;
			}

			path.pop_back();
		}
		else {
			if(expect > best_expect) {
				best_expect = expect;
				best_path = path;
				bep = ep;
			}
		}
	} 
};

int main() {
	int T;
	cin >> T;

	int R, C, Rs, Cs, S;
	double P, Q;

	Solution s;
	double best_expect;

	vector<pair<int, int>> path, best_path;
	vector<double> ep, bep;

	for(int i = 1; i <= T; ++ i) {
		cin >> R >> C >> Rs >> Cs >> S >> P >> Q;

		for(int i = 0; i < R; ++ i) {
			for(int j = 0; j < C; ++ j) {
				cin >> rect_c[i][j];
				rect_p[i][j] = (rect_c[i][j] == 'A' ? P : Q);
			}
		}

		best_expect = 0;
		s.catch_monster(Rs, Cs, 0, R, C, S, P, Q, 0, best_expect, path, best_path, ep, bep);

		printf("Case #%d: %.7lf\n", i, best_expect);
//		for(int j = 0; j < best_path.size(); ++ j) {
//			auto p = best_path[j];
//			cout << p.first << '\t' << p.second << '\t' << bep[j] << endl;
//		}
	}
    return 0;
}
