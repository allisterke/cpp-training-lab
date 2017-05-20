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

const long MOD = 1000000007L;

struct Word {
	int alphabet[26];
	void reset(const string &str) {
		clear();
		for(auto c : str) {
			++ alphabet[c - 'a'];
		}
	}
	void addc(char c) {
		++ alphabet[c - 'a'];
	}
	bool operator==(const Word &w) const {
		return !memcmp(alphabet, w.alphabet, sizeof(alphabet));
	}
	void clear() {
		memset(alphabet, 0, sizeof(alphabet));
	}
	Word() : alphabet{} {}
};

namespace std {
	template<>
	struct hash<Word> {
		size_t operator()(const Word &w) const {
			size_t code = 0;
			hash<int> hi;
			for(int i = 0; i < 26; ++ i) {
				code = (code << 1) ^ hi(w.alphabet[i]);
			}
			return code;
		}
	};
};

using WCMAP = unordered_map<Word, int>;
using IWCMAP = map<int, WCMAP>;

class Solution {

public:

void parse(string &sentence, IWCMAP &iwc, long long total[]) { 

	memset(total, 0, sentence.length() * sizeof(long long));
	total[sentence.length()] = 1;

	for(int i = sentence.length(); i > 0; -- i) { 
		Word word;
//		int length(0);

		for(auto &kv : iwc) {
			auto n = kv.first; 
			if(n > i) {
				break;
			} 
			auto &wc = kv.second;
		
			word.clear();

			for(int j = 1; j <= n; j ++) {
				word.addc(sentence[i-j]);
			}
//			length = n;
			
			auto it = wc.find(word);
			if(it != wc.end()) {
				total[i-n] += it->second * total[i] % MOD;
			}
			
		}
	}
}
};

int main() {
	int T, V, S;
	cin >> T;

	Word word;
	IWCMAP iwc;
	long long total[4001];

	Solution s;

	for(int i = 1; i <= T; ++ i) {
		cin >> V >> S;

		for(int j = 0; j < V; ++ j) {
			string str;
			cin >> str;
			word.reset(str);

			++ iwc[str.length()][word];
		}

		printf("Case #%d: ", i);

		for(int j = 0; j < S; ++ j) { 
			string sentence;
			cin >> sentence;

			if(j) {
				cout << ' ';
			}

			s.parse(sentence, iwc, total);
			cout << total[0]; 
		}

		cout << endl; 

		iwc.clear();
	}
    return 0;
}
