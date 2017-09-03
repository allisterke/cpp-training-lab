#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

map<char, int> symbols{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

class Solution {
public:
    void sort(vector<pair<string, string>> &names) {
        std::sort(begin(names), end(names),
             [this] (const pair<string, string> &a, const pair<string, string> &b) {
                 if(a.first != b.first) {
                     return a.first < b.first;
                 }
                 else {
                     return roman(a.second) < roman(b.second);
                 }
            }
        );
    }

    int roman(const string &num) {
        int n = 0;
        for(int i = 0; i < num.size(); ) {
            int j = i;
            for(; j < num.size() && num[j] == num[i]; ++ j) ;
            int k = j - i;
            if(k == 1 && j <= num.size() && is_minus(num[i], num[j])) {
                n += symbols[num[j]] - symbols[num[i]];
                i = j + 1;
            }
            else {
                n += symbols[num[i]] * k;
                i = j;
            }
        }
        return n;
    }

    bool is_minus(char a, char b) {
        if(a == 'I' && (b == 'V' || b == 'X')) {
            return true;
        }
        if(a == 'X' && (b == 'L' || b == 'C')) {
            return true;
        }
        if(a == 'C' && (b == 'D' || b == 'M')) {
            return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    vector<pair<string, string>> names(N);
    for(auto &name : names) {
        cin >> name.first >> name.second;
    }
    s.sort(names);
    for(auto &name : names) {
        cout << name.first << ' ' << name.second << endl;
    }
    return 0;
}
