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

using gmap = unordered_map<string, tuple<int, unordered_set<string>>>;

class Solution {
public:
	bool check(gmap &g) {
		for(auto &kv : g) {
			auto &var = kv.first;
			auto &state = get<0>(kv.second);
			auto &deps = get<1>(kv.second);

			switch(state) {
				case -1: // not checked
					state = 0;
					for(auto &dep : deps) {
						if(!check(g, dep)) {
							return false;
						}
					}
					state = 1;
					break;
//					return true;
				case 0: // checking
					return false; // cross dep
				case 1:
					break; // break from switch
			}
		}

		return true;
	}

	bool check(gmap &g, const string &var) {

		auto it = g.find(var);
		if(it == g.end()) {
			return false;
		}

		auto &state = get<0>(it->second);
		auto &deps = get<1>(it->second);

		switch(state) {
			case -1: // not checked
				state = 0;
				for(auto &dep : deps) {
					if(!check(g, dep)) {
						return false;
					}
				}
				state = 1;
				return true;
			case 0: // checking
				return false;
			case 1:
				return true;
		}
	}
};

void parse_dep(string &s, string &var, unordered_set<string> &deps) {
	var.clear();
	deps.clear();

	int idx = 0;
	for(; s[idx] != '='; ++ idx) {
		var.push_back(s[idx]);
	}

	++ idx;

	for(; s[idx] != '('; ++ idx) ;

	++ idx;

	string dep;
	while(true) {
		for(; s[idx] != ',' && s[idx] != ')'; ++ idx) {
			dep.push_back(s[idx]);
		}
		if(!dep.empty()) {
			deps.insert(dep);
		}
		dep.clear();

		if(s[idx] == ')') {
			break;
		}
		else {
			++ idx;
		}
	} 

//	cout << var << ": ";
//	for(auto &dep : deps) {
//		cout << dep << " ";
//	}
//	cout << endl;
}

int main() {
	int T;
	cin >> T;

	Solution s;
	gmap g;
	unordered_set<string> deps;
	string stmt;
	string var;

	for(int i = 1; i <= T; ++ i) {
		int N;
		cin >> N;

		for(int j = 0; j < N; ++ j) {
			cin >> stmt;

			parse_dep(stmt, var, deps);
			g[var] = make_tuple(-1, deps);
		}

		bool valid = s.check(g);

		printf("Case #%d: %s\n", i, valid ? "GOOD" : "BAD");

		g.clear();
	}

    return 0;
}
