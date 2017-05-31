#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * @param A: An integer array.
     * @param B: An integer array.
     * @return: a double whose format is *.5 or *.0
     */
    double findMedianSortedArrays(const vector<int> &A, const vector<int> &B) {
        // write your code here
        int oa = 0, ob = 0;
        int sa = A.size(), sb = B.size();
        int total = sa + sb;
        int del = (total & 1) ? total / 2 : total / 2 - 1;
        while(del > 0) {
            int k = del / 2;
            k += (del & 1);
            if(ob + k > sb || oa + k <= sa && A[oa + k - 1] < B[ob + k - 1]) {
                oa += k;
            }
            else {
                ob += k;
            }
            del -= k;
        }
        vector<int> cs;
        for(int i = oa; i < min(oa+2, sa); ++ i) {
            cs.push_back(A[i]);
        }
        for(int i = ob; i < min(ob+2, sb); ++ i) {
            cs.push_back(B[i]);
        }
        sort(cs.begin(), cs.end());
        if(total & 1) {
            return cs[0];
        }
        else {
            return (cs[0] + cs[1]) / 2.0;
        }
    }
};

int main() {
	cout << Solution().findMedianSortedArrays({}, {1}) << endl;
	return 0;
}
