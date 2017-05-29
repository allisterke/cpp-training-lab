#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    bool solve(int n, vector<vector<int>> &matrix) {
        if(n == 1) {
            return matrix[0][0] == 1;
        }
        int g = matrix[0][0];
        for(int i = 1; i < n; ++ i) {
            g = gcd(g, matrix[0][i]);
        }
        if(g == 1) {
            gcd(n, matrix, 0, 1);
            return true;
        }
        return false;
    }
    int gcd(int a, int b) {
        if(a < 0 || b < 0) {
            return gcd(abs(a), abs(b));
        }
        if(a < b) {
            return gcd(b, a);
        }
        return b == 0 ? a : gcd(b, a%b);
    }
    void gcd(int n, vector<vector<int>> &matrix, int offset, int target) {
        if(offset >= n) {
            for(int k = 1; k < n; ++ k) {
                matrix[k][k] = 1;
            }
            if(target == -1) {
                matrix[1][1] = -1;
            }
            return;
        }
        if(matrix[0][offset] < 0) {
            matrix[0][offset] = -matrix[0][offset];
            gcd(n, matrix, offset, -target);
            for(int k = 0; k < n; ++ k) {
                matrix[k][offset] = -matrix[k][offset];
            }
            return;
        }
        if(offset == 0 || matrix[0][offset] == 0) {
            gcd(n, matrix, offset+1, target);
            return;
        }
        if(matrix[0][0] < matrix[0][offset]) {
            swap(matrix[0][0], matrix[0][offset]);
            gcd(n, matrix, offset, -target);
            for(int k = 0; k < n; ++ k) {
                swap(matrix[k][0], matrix[k][offset]);
            }
            return;
        }
        if(matrix[0][offset] != 0) {
            int q = matrix[0][0] / matrix[0][offset];
            matrix[0][0] -= q * matrix[0][offset];
            gcd(n, matrix, offset, target);
            for(int k = 0; k < n; ++ k) {
                matrix[k][0] += q * matrix[k][offset];
            }
            return;
        }
    }
};

int main() {
    Solution s;
    int n;
    while(cin >> n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            cin >> matrix[0][i];
        }
        if (s.solve(n, matrix)) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (j != 0) {
                        cout << ' ';
                    }
                    cout << matrix[i][j];
                }
                cout << endl;
            }
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
