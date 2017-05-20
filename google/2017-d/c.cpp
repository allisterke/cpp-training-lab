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

using TMSI = unordered_map<string, int>;
using TSI = set<int>;

const long MOD = 1000000007L;

class Solution {
public:

void parse(string &sentence, int index, long count, TMSI &msi, TSI &si, long &total) { 
	if(index == sentence.length()) {
		total += count % MOD;
		return;
	}

	for(auto n : si) {
		if(index + n <= sentence.length()) {
			string local(sentence, index, n);
			sort(local.begin(), local.end());
			
			auto it = msi.find(local);
			if(it != msi.end()) {
				parse(sentence, index + n, count * it->second % MOD, msi, si, total);
			}
		}
		else {
			break;
		}
	}
}
};

int main() {
	int T, V, S;
	cin >> T;

	string word;
	TMSI msi;
	TSI si;

	Solution s;
	long total = 0;

	for(int i = 1; i <= T; ++ i) {
		cin >> V >> S;
		for(int j = 0; j < V; ++ j) {
			cin >> word;
			sort(word.begin(), word.end());
			++ msi[word];
			si.insert(word.length());
		}

		printf("Case #%d: ", i);

		auto &sentence = word;

		for(int j = 0; j < S; ++ j) { 
			cin >> sentence;

			if(j) {
				cout << ' ';
			}
			s.parse(sentence, 0, 1, msi, si, total);
			cout << total;

			total = 0;
		}

		cout << endl; 

		msi.clear();
		si.clear(); 
	}
    return 0;
}
