#include <bits/stdc++.h>
using namespace std;

using ULL = unsigned long long int;
using Point = tuple<double, double, double>;
class Solution {
public:
    double findOpt(vector<pair<double, double>> &ps) {
        vector<double> wsum {0};
        for(auto &p : ps) {
            wsum.push_back(wsum.back() + p.second);
        }
        int i = 1;
        for(; i < wsum.size() && wsum[i] - (wsum.back() - wsum[i]) < 0; ++ i) ;
        return ps[i-1].first;
    }
    double solve(const vector<Point> &points) {
        vector<pair<double, double>> ps;
        for(auto &p : points) { // x + y = a;
            ps.emplace_back(get<0>(p) + get<1>(p), get<2>(p));
        }
        sort(ps.begin(), ps.end(), [](const pair<double, double> &a, const pair<double, double> &b) {
            return a.first < b.first;
        });
        double a = findOpt(ps); // best a
        ps.clear();
        for(auto &p : points) { // x + y = b;
            ps.emplace_back(get<1>(p) - get<0>(p), get<2>(p));
        }
        sort(ps.begin(), ps.end(), [](const pair<double, double> &a, const pair<double, double> &b) {
            return a.first < b.first;
        });
        double b = findOpt(ps); // best b
        double x = (a - b) / 2, y = (a + b) / 2; // the best point
        double result = 0;
        for(auto &p : points) {
            result += max(abs(get<0>(p) - x), abs(get<1>(p) - y)) * get<2>(p);
        }
        return result;
    }
    double solve0(const vector<Point> &points) {
        double sum = numeric_limits<double>::max();
        vector<double> line1;
        for(auto &p : points) {
            line1.push_back(get<1>(p) - get<0>(p)); // y - x = get<1>(p) - get<0>(p)
        }
        for(auto &p : points) {
            double b = get<1>(p) + get<0>(p); // y + x = b
            for(auto a : line1) { // y - x = a
                double x = (b - a) / 2;
                double y = (b + a) / 2;
                double ts = 0;
                bool finished = true;
                for(auto &p : points) {
                    ts += max(abs(x - get<0>(p)), abs(y - get<1>(p))) * get<2>(p);
                    if(ts >= sum) {
                        finished = false;
                        break;
                    }
                }
                if(finished) {
                    sum = min(sum, ts);
                }
            }
        }
        return sum;
    }
};

int main() {
	int T;
	cin >> T;

	Solution s;

	for(int i = 1; i <= T; ++ i) {
		int N;
        cin >> N;
        vector<tuple<double, double, double>> points;
        double x, y, w;
        for(int j = 0; j < N; ++ j) {
            cin >> x >> y >> w;
            points.push_back(make_tuple(x, y, w));
        }
		printf("Case #%d: %lf\n", i, s.solve(points));
	}
    return 0;
}
