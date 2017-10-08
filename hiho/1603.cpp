#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    vector<string> solve(const string &str) {
        vector<string> names;
        for(int i = 0, j = 0; i < str.size(); i = j) {
            j = i+1;
            if(str[i] == '@') {
                for(; j < str.size() && isalpha(str[j]); ++ j) ;
                if(j > i+1) {
                    names.emplace_back(begin(str) + (i+1), begin(str) + j);
                }
            }
        }
        return names;
    }
};

void test() {
    Solution s;
    for(auto &str : s.solve("@abc:@@,@littleho's code is so confusing. @abc.")) {
        cout << str << endl;
    }
}

void run() {
    Solution s;
    string text;
    getline(cin, text);
    auto names = s.solve(text);
    for(int i = 0; i < names.size(); ++ i) {
        if(i) {
            cout << ' ';
        }
        cout << names[i];
    }
    cout << endl;
}

int main() {
//    test();
    run();
    return 0;
}
