#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

int main() {
    Solution s;
    int K;
    double a;
    cin >> K >> a;
    vector<double> w(K);
    for(auto &wi : w) {
        cin >> wi;
    }
    double ws = accumulate(begin(w), end(w), 0.0);
    double lambda = ws / a;
    double magic = 0;
    vector<double> x(K);
    for(int i = 0; i < K; ++ i) {
        x[i] = w[i] / lambda;
        magic += w[i] * log(x[i]);
    }
    printf("%.5lf\n", magic);
    for(int i = 0; i < K; ++ i) {
        if(i) {
            printf(" ");
        }
        printf("%.5lf", x[i]);
    }
    printf("\n");
    return 0;
}
