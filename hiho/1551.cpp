#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
    struct Dir {
        map<string, Dir *> next;
    };
    Dir root;
public:
    vector<string> split(string &path) {
        replace(begin(path), end(path), '/', ' ');
        istringstream iss(path);
        vector<string> ss;
        string s;
        while (iss >> s) {
            ss.push_back(s);
        }
        return ss;
    }
    void add(string &path) {
        Dir *d = &root;
        for(auto &s : split(path)) {
            if(d->next.find(s) == d->next.end()) {
                d->next[s] = new Dir;
            }
            d = d->next[s];
        }
    }
    int dirs() {
        return count_dirs(&root) - 1;
    }

    int count_dirs(Dir *d) {
        if(d->next.size() == 0) {
            return 0;
        }
        int total = 0;
        for(auto &kv : d->next) {
            total += count_dirs(kv.second);
        }
        return total + 1;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    for(int i = 0; i < N; ++ i) {
        string path;
        cin >> path;
        s.add(path);
    }
    cout << s.dirs() << endl;
    return 0;
}
