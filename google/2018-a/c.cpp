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
    int minTwoCubes(vector<vector<int>> &stars) {
        auto points = startPoints(stars);
		int left = 0, right = numeric_limits<int>::max() - 1;
		while(left < right) {
			int mid = (left + right) / 2;
			if(tryTwoCubes(stars, points, mid)) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return tryTwoCubes(stars, points, left) ? left : left + 1;
    }

	bool testFit(vector<int> &star, vector<pair<int, int>> &point, int edge) {
		for(int i = 0; i < 3; ++ i) {
			int mind = min(point[i].first, point[i].first + point[i].second * edge);
			int maxd = max(point[i].first, point[i].first + point[i].second * edge);
			int p = star[i] + star[3];
			if(p < mind || p > maxd) {
				return false;
			}
			p = star[i] - star[3];
			if(p < mind || p > maxd) {
				return false;
			}
		}
		return true;
	}

    bool tryTwoCubes(vector<vector<int>> &stars, vector<vector<pair<int, int>>> &points, int edge) {
        for(int i = 0; i < points.size(); ++ i) {
            for(int j = 0; j < points.size(); ++ j) {
                bool allFit = true;
                for(auto &star : stars) {
                    if(!testFit(star, points[i], edge) && !testFit(star, points[j], edge)) {
                        allFit = false;
                        break;
                    }
                }
				if(allFit) {
					return true;
				}
			}
		}
		return false;
	}

    vector<vector<pair<int, int>>> startPoints(vector<vector<int>> &stars) {
		auto xyz = minMaxXYZ(stars);
        vector<vector<pair<int, int>>> points;
        vector<pair<int, int>> point;
        for(int i = 0; i < 2; ++ i) {
            point.push_back(make_pair(xyz[0][i], i == 0 ? 1 : -1));
            for(int j = 0; j < 2; ++ j) {
                point.push_back(make_pair(xyz[1][j], j == 0 ? 1 : -1));
                for(int k = 0; k < 2; ++ k) {  
                    point.push_back(make_pair(xyz[2][k], k == 0 ? 1 : -1));
                    points.push_back(point);
                    point.pop_back();
                }
                point.pop_back();
           }
            point.pop_back();
        }
        return points;
    }
        

    vector<vector<int>> minMaxXYZ(vector<vector<int>> &stars) {
        vector<vector<int>> xyz(3, {numeric_limits<int>::max(), numeric_limits<int>::min()});
        for(auto &star : stars) {
            for(int i = 0; i < 3; ++ i) {
                xyz[i][0] = min(xyz[i][0], star[i] - star[3]);
                xyz[i][1] = max(xyz[i][1], star[i] + star[3]);
            }
        }
        return xyz;
    }
};

int main() {
	int T;
	cin >> T;

	Solution s;

	for(int i = 1; i <= T; ++ i) {
        int N;
        cin >> N;
        vector<vector<int>> stars(N, vector<int>(4));
        for(int j = 0; j < N; ++ j) {
            for(int k = 0; k < 4; ++ k) {
                cin >> stars[j][k];
            }
        }
		printf("Case #%d: %d\n", i, s.minTwoCubes(stars));
	}
    return 0;
}
