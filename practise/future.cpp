//
// Created by ally on 9/1/17.
//
// g++ future.cpp -lpthread -O3
#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

LL f(LL begin, LL end) {
    LL sum = 0;
    while(begin <= end) {
        sum += begin * begin;
        ++ begin;
    }
    return sum;
}

int main() {
    vector<future<LL>> futures;
    LL begin = 1, end = 1000LL * 1000 * 1000 * 100;
    int N = 20;
    for(int i = 0; i < N; ++ i) {
        futures.push_back(
            async(launch::async,
                  f, begin + (end - begin + 1) / N * i, begin + (end - begin + 1) / N * (i + 1) - 1));
    }
    LL sum = 0;
    for(auto & fu : futures) {
        sum += fu.get();
    }
    cout << sum << endl;
}