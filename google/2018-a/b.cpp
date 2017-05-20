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

class Solution {
public:
    bool match(const string &s1, const string &s2) {
        vector<vector<int>> matched(s1.size()+1, vector<int>(s2.size()+1));
        matched[0][0] = true;
        for(int i = 0; i < s1.size() && s1[i] == '*'; ++ i) {
            matched[i+1][0] = true;
        }
        for(int j = 0; j < s2.size() && s2[j] == '*'; ++ j) {
            matched[0][j+1] = true;
        }
        for(int i = 0; i < s1.size(); ++ i) {
            for(int j = 0; j < s2.size(); ++ j) {
                if(matched[i][j]) {
                    if(s1[i] == '*' || s2[j] == '*' || s1[i] == s2[j]) {
                        matched[i+1][j+1] = true;
                        for(int k = i+1; k < s1.size() && s1[k] == '*'; matched[k++ + 1][j+1] = true) ;
                        for(int k = j+1; k < s2.size() && s2[k] == '*'; matched[i+1][k++ +1] = true) ;
                    }
                    if(s1[i] == '*') {
                        int k = j;
                        for(int n = 0; n < 4 && k < s2.size(); ++ k) {
                            n += (s2[k] != '*');
                        }
                        for(; k < s2.size() && s2[k] == '*'; ++ k) ;
                        for(int n = j; n < k; ++ n) {
                            matched[i+1][n+1] = true;
                        }
                    }
                    if(s2[j] == '*') {
                        int k = i;
                        for(int n = 0; n < 4 && k < s1.size(); ++ k) {
                            n += (s1[k] != '*');
                        }
                        for(; k < s1.size() && s1[k] == '*'; ++ k) ;
                        for(int n = i; n < k; ++ n) {
                            matched[n+1][j+1] = true;
                        }
                    }
                }
            }
        }
        return matched.back().back();
    }
};

int main() {
	int T;
	cin >> T;

	Solution s;
    string s1, s2;

	for(int i = 1; i <= T; ++ i) {
        cin >> s1 >> s2;
		printf("Case #%d: %s\n", i, s.match(s1, s2) ? "TRUE" : "FALSE");
	}
    return 0;
}
