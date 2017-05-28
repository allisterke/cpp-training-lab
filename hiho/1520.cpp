#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    string solve(string &N, int X, int Y) {
        if(checkZeroPossible(N, X, Y)) {
            return string(N.size(), '0');
        }
        vector<int> questions = collectQuestions(N);
        LL remainder = calculateRemainder(N, X);
        if(questions.empty()) {
            return remainder == Y ? N : "No solution";
        }
        vector<int> assignments(questions.size());
        if(questions.front() < N.size()-1) {
            return checkMinimumNumber(questions, assignments, X, Y, remainder, 0) ?
                   buildMinimum(N, questions, assignments) : "No solution";
        }
        else {
            for(int i = 1; i <= 9; ++ i) {
                assignments[0] = i;
                int r = (remainder + fastPower(N.size()-1, X) * i) % X;
                if(checkMinimumNumber(questions, assignments, X, Y, r, 1)) {
                    return buildMinimum(N, questions, assignments);
                }
            }
            return "No solution";
        }
    }

private:
    bool checkZeroPossible(const string &N, int X, int Y) {
        return Y == 0 && count(N.begin(), N.end(), '?') == N.size();
    }
    vector<int> collectQuestions(const string &N) {
        vector<int> questions;
        for(int i = 0; i < N.size(); ++ i) {
            if(N[i] == '?') {
                questions.push_back(N.size() - 1 - i);
            }
        }
        return questions;
    }
    LL fastPower(int power, int X) {
        if(power == 0) {
            return 1LL;
        }
        LL r = fastPower(power/2, X);
        r *= r;
        if(power & 1) {
            r *= 10;
        }
        return r % X;
    }
    LL calculateRemainder(const string &N, int X) {
        LL r = 0;
        for(int i = 0; i < N.size(); ++ i) {
            char c = *(N.crbegin() + i);
            if(isdigit(c)) {
                r += fastPower(i, X) * (c - '0');
                r %= X;
            }
        }
        return r;
    }
    bool checkMinimumNumber(const vector<int> &questions, vector<int> &assignments,
                            int X, int Y, int remainder, int offset) {
        if(offset >= questions.size()) {
            return remainder == Y;
        }
        for(int i = 0; i <= 9; ++ i) {
            assignments[offset] = i;
            int r = (remainder + i * fastPower(questions[offset], X)) % X;
            if(checkMinimumNumber(questions, assignments, X, Y, r, offset+1)) {
                return true;
            }
        }
        return false;
    }

    string buildMinimum(const string &N, const vector<int> &questions, const vector<int> &assignments) {
        string minimum = N;
        for(int i = 0; i < questions.size(); ++ i) {
            int index = questions[i];
            minimum[N.size() - 1 - index] = assignments[i] + '0';
        }
        return minimum;
    }
};

int main() {

    string N;
    int X, Y;
    Solution s;
    while (cin >> N >> X >> Y) {
        cout << s.solve(N, X, Y) << endl;
    }
    return 0;
}
