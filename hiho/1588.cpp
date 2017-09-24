#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct TimeStruct {
    int t[3];
    TimeStruct(int hour, int minute, int second) : t{second, minute, hour} {}
    void step() {
        ++ t[0];
        if(t[0] == 60) {
            t[0] = 0;
            ++ t[1];
            if(t[1] == 60) {
                t[1] = 0;
                ++ t[2];
                if(t[2] == 24) {
                    t[2] = 0;
                }
            }
        }
    }
};

class Solution {
public:
    void solve(const string &time) {
        TimeStruct ts((time[0] - '0') * 10 + time[1] - '0',
                      (time[3] - '0') * 10 + time[4] - '0',
                      (time[6] - '0') * 10 + time[7] - '0');
        vector<int> digit(10);
        for(auto c : time) {
            if(c != ':') {
                digit[c - '0'] = true;
            }
        }
        for(int i = 1; i <= 24*60*60; ++ i) {
            ts.step();
            bool valid = true;
            for(int j = 0; j < 3; ++ j) {
                if(!digit[ts.t[j] % 10] || !digit[ts.t[j] / 10]) {
                    valid = false;
                    break;
                }
            }
            if(valid) {
                break;
            }
        }
        printf("%02d:%02d:%02d\n", ts.t[2], ts.t[1], ts.t[0]);
    }
    void solve0(const string &time) {
        set<int> ds;
        for(auto c : time) {
            if(c != ':') {
                ds.insert(c);
            }
        }
        vector<int> dv(begin(ds), end(ds));
        for(auto &d : dv) {
            d -= '0';
        }
        int M = ((time[0] - '0') * 10 + time[1] - '0')*60*60 + ((time[3] - '0') * 10 + time[4] - '0')*60 + (time[6] - '0')*10 + time[7] - '0';
        int N = M;
        int D = 0;
        for (int i = 0; i < pow(dv.size(), 6); ++ i) {
            int t = i;
            vector<int> hm;
            for(int j = 0; j < 6; ++ j) {
                hm.push_back(dv[t % dv.size()]);
                t /= dv.size();
            }
            int hour = hm[0] * 10 + hm[1];
            int minute = hm[2] * 10 + hm[3];
            int second = hm[4] * 10 + hm[5];
            if(hour >= 24 || minute >= 60 || second >= 60) {
                continue;
            }
            int N1 = hour * 60 * 60 + minute * 60 + second;
            int D1 = N1 > M ? N1 - M : 24*60*60 + (N1 - M);
            if(N == M || D1 < D) {
                N = N1;
                D = D1;
            }
        }
        printf("%02d:%02d:%02d\n", N/60/60, N/60%60, N%60);
    }
};

void test() {
    Solution s;
    s.solve("15:10:30");
    s.solve("23:59:59");
    s.solve("00:00:00");
    s.solve("12:34:56");
}

void run() {
    Solution s;
    int N;
    cin >> N;
    while(N -- > 0) {
        string time;
        cin >> time;
        s.solve(time);
    }
}

int main() {
//    test();
    run();
    return 0;
}
