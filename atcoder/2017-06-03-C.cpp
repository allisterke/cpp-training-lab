#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

int main() {
    Solution s;

    int N;
    cin >> N;
    int total_grade = 0;
    int min_grade_not_ten = 100;
    for(int i = 0; i < N; ++ i) {
        int grade;
        cin >> grade;
        total_grade += grade;
        if(grade % 10 != 0) {
            min_grade_not_ten = min(min_grade_not_ten, grade);
        }
    }
    cout << (total_grade % 10
             ? total_grade
             : min_grade_not_ten != 100 ? total_grade - min_grade_not_ten : 0) << endl;
    return 0;
}
