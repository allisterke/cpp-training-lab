#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL convert(const string &ans) {
        LL a = 0;
        for(char c : ans) {
            a = (a << 1) | (c == 'T');
        }
        return a;
    }
    int solve(int N, int Q, vector<string> &anss, vector<int> &scores) {
        if (N == 1) {
            ++N;
            anss.insert(anss.begin(), anss.front());
            scores.insert(scores.begin(), scores.front());
        }
        auto &A = anss[0];
        auto &B = anss[1];
        auto &C = anss[2];
        int M1 = 0, M2 = 0, M3 = 0, M4 = 0;
        for (int i = 0; i < Q; ++i) {
            if (A[i] == B[i]) {
                if(C[i] == A[i]) {
                    ++ M1;
                }
                else {
                    ++ M2;
                }
            }
            else {
                if (A[i] == C[i]) {
                    ++ M3;
                }
                else {
                    ++ M4;
                }
            }
        }
        int S1 = scores[0];
        int S2 = scores[1];
        int S3 = 0;
        for(int t11 = 0; t11 <= M1; ++ t11) {
            for(int t12 = 0; t12 <= M2; ++ t12) {
                for(int t21 = 0; t21 <= M3; ++ t21) {
                    for(int t22 = 0; t22 <= M4; ++ t22) {
                        int f11 = M1 - t11;
                        int f12 = M2 - t12;
                        int f21 = M3 - t21;
                        int f22 = M4 - t22;
                        if(t11 + t12 + t21 + t22 == S1 && t11 + t12 + f21 + f22 == S2) {
                            S3 = max(S3, t11 + f12 + t21 + f22);
                        }
                    }
                }
            }
        }
        return S3;
    }
    int solve0(int N, int Q, const vector<string> &anss, const vector<int> &scores) {
        vector<LL> ianss;
        for(auto &ans : anss) {
            ianss.push_back(convert(ans));
        }
        int left = 64 - Q;
        int ms = 0;
        for(LL i = 0; i < (1 << Q); ++ i) {
            int j = 0;
            for(; j < N; ++ j) {
                int count = __builtin_popcountll(~ (i ^ ianss[j]));
                if(count - left != scores[j]) {
                    break;
                }
            }
            if(j == N) {
                ms = max(ms, __builtin_popcountll(~ (i ^ ianss.back())) - left);
            }
        }
        return ms;
    }
};

int main() {
    int T;
    cin >> T;

    Solution s;
    int N, Q;
    for(int i = 1; i <= T; ++ i) {
        cin >> N >> Q;
        vector<string> anss(N+1);
        for(auto &ans : anss) {
            cin >> ans;
        }
        vector<int> scores(N);
        for(auto &score : scores) {
            cin >> score;
        }
        printf("Case #%d: %d\n", i, s.solve(N, Q, anss, scores));
    }
    return 0;
}
