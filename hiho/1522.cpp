#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

int main() {
    Solution s;
    int N;
    while(cin >> N) {
        int TP, TN, FP, FN;
        TP = TN = FP = FN = 0;
        for(int i = 0; i < N; ++ i) {
            char t, p;
            cin >> t >> p;
            if(t == '+' && p == '+') {
                ++ TP;
            }
            else if(t == '+' && p == '-') {
                ++ TN;
            }
            else if(t == '-' && p == '+') {
                ++ FP;
            }
            else {
                ++ FN;
            }
        }
//        double precision = 1.0 * TP / (TP + FP);
//        double recall = 1.0 * TP / (TP + TN);
//        double f1 = 2.0 * precision * recall / (precision + recall);
        double f1 = 2.0 * TP / (2 * TP + FP + TN);
        printf("%.2lf%%\n", f1*100);
    }
    return 0;
}
