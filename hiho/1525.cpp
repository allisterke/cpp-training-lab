#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
array<pair<int, int>, 4> fourDirections = {
        make_pair(0, 1),
        make_pair(0, -1),
        make_pair(1, 0),
        make_pair(-1, 0)
};

array<pair<int, int>, 8> eightDirections = {
        make_pair(0, 2),
        make_pair(1, 1),
        make_pair(2, 0),
        make_pair(1, -1),
        make_pair(0, -2),
        make_pair(-1, -1),
        make_pair(-2, 0),
        make_pair(-1, 1)
};

class Solution {
public:
    int solve(int X, int Y) {
        if(checkZeroStep(X, Y)) {
            return 0;
        }
        if(checkOneStep(X, Y)) {
            return 1;
        }
        if(checkTwoStep(X, Y)) {
            return 2;
        }
        if(checkThreeStep(X, Y)) {
            return 3;
        }
        return 4;
    }

    inline bool checkZeroStep(int X, int Y) {
        return abs(X) + abs(Y) == 0;
    }

    inline bool checkOneStep(int X, int Y) {
        return abs(X) + abs(Y) == 1 || charAt(X, Y) == 'A';
    }

    inline bool checkTwoStep(int X, int Y) {
        if(abs(X) + abs(Y) == 2) {
            return true;
        }
        char c = charAt(X, Y);
        for(auto &d : fourDirections) {
            if(c == charAt(d.first, d.second)) {
                return true;
            }
            if('A' == charAt(X+d.first, Y+d.second)) {
                return true;
            }
        }
        return false;
    }

    inline bool checkThreeStep(int X, int Y) {
        char c = charAt(X, Y);
        if(abs(X) + abs(Y) == 3 || abs(c - 'A') % 2 == 1) {
            return true;
        }
        for(auto &d : eightDirections) {
            if(c == charAt(d.first, d.second)) {
                return true;
            }
            if('A' == charAt(X+d.first, Y+d.second)) {
                return true;
            }
        }
        for(auto &d1 : fourDirections) {
            for(auto &d2 : fourDirections) {
                if(charAt(d1.first, d1.second) == charAt(X+d2.first, Y+d2.second)) {
                    return true;
                }
            }
        }
        return false;
    }

    char charAt(int i, int j) {
        LL p = max(abs(i), abs(j));
        LL index = (2*p-1)*(2*p-1);
        if(j == p && i > -p && i <= p) {
            index += p + i;
        }
        else if(i == p && j < p && j >= -p) {
            index += 2*p + p - j;
        }
        else if(j == -p && i < p && i >= -p) {
            index += 4*p + p - i;
        }
        else if(i == -p && j > -p && j <= p) {
            index += 6*p + p + j;
        }
        char c = char(-- index % 26) + 'A';
        return c;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    for(int i = 0; i < N; ++ i) {
        int X, Y;
        cin >> X >> Y;
        cout << s.solve(X, Y) << endl;
    }
    return 0;
}
