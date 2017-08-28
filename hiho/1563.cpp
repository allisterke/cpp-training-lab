#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(int N, int M, const vector<int> &seats) {
        if(count(seats.begin(), seats.end(), 0) < M) {
            return -1;
        }
        if(M == 1) {
            return 0;
        }
        int left = 0, right = 0;
        int i = N-1, j = 0;
        int dist = 0;
        while(left + right < M) {
            if(j <= N - i) {
                if(!seats[j]) {
                    ++ right;
                    dist += j;
                }
                ++ j;
            }
            else {
                if(!seats[i]) {
                    ++ left;
                    dist += (N - i);
                }
                -- i;
            }
        }
        int best = dist;
        for(i = (i+1) % N; seats[i]; i = (i+1) % N) ; // adjust i to left most available seat
        for(j = j%N; seats[j]; j = (j+1) % N) ; // find next seat
        for(int center = 1; center < seats.size(); ++ center) {
            if(left == 0) {
                if(seats[center-1]) {
                    dist -= right;
                }
                else {
                    if((j - center + N) % N == 1) { // replace last center
                        for(; seats[j]; j = (j+1) % N) ;
                    }
                    else { // last center becomes the first left node
                        dist = dist - (right - 1) + 1;
                        ++ left;
                        -- right;
                        i = center - 1;
                    }
                }
            }
            else {
                if((j - center + N) % N <= (center - i + N) % N) { // replace left most with right most
                    dist -= right;
                    ++right;
                    dist += (j - center + N) % N;
                    --left;
                    dist += left;
                    dist -= (center - 1 - i + N) % N;
                    for(i = (i+1)%N; seats[i]; i = (i+1) % N) ; // find next empty seat
                    for(j = (j+1)%N; seats[j]; j = (j+1) % N) ;
                }
                else { // no replace
                    dist -= right;
                    dist += left;
                }
                if(!seats[center - 1]) {
                    ++ left;
                    -- right;
                    dist += 2;
                }
            }
            best = min(best, dist);
        }
        return best;
    }

    int naive_solve(int N, int M, const vector<int> &seats) {
        if(count(seats.begin(), seats.end(), 0) < M) {
            return -1;
        }
        if(M == 1) {
            return 0;
        }
        int best = numeric_limits<int>::max();
        for(int center = 0; center < seats.size(); ++ center) {
            int dist = 0;
            int left = 0, right = 0;
            for(int i = 1, j = 0; left + right < M; ) {
                if(i >= j) {
                    if(!seats[(center+j)%N]) {
                        ++ right;
                        dist += j;
                    }
                    ++ j;
                }
                else {
                    if(!seats[(N+center-i) % N]) {
                        ++ left;
                        dist += i;
                    }
                    ++ i;
                }
            }
            best = min(best, dist);
        }
        return best;
    }
};

void test() {
    Solution s;
    default_random_engine g(random_device{}());
    for(int t = 0; t < 100; ++ t) {
        int N = 80;
        int M = N / 2;
        vector<int> v;
        for (int i = 0; i < N; ++i) {
            v.push_back(g() & 1);
        }
        if(s.solve(N, M, v) == s.naive_solve(N, M, v)) {
            continue;
        }
        cout << N << ' ' << M << endl;
        for (auto n : v) {
            cout << n << ' ';
        }
        cout << endl;
        cout << "solve: " << s.solve(N, M, v) << endl;
        cout << "naive solve: " << s.naive_solve(N, M, v) << endl;
        break;
    }
}

void run() {
    Solution s;
    int N, M;
    while(cin >> N >> M) {
        vector<int> seats(N);
        for(auto &seat : seats) {
            cin >> seat;
        }
        cout << s.solve(N, M, seats) << endl;
//        cout << s.naive_solve(N, M, seats) << endl;
    }
}

int main() {
//    test();
    run();
    return 0;
}
