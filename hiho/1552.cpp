#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct Rect {
    LL x1, y1, x2, y2;
    Rect() {
        x1 = y1 = x2 = y2 = -1;
    }
    Rect(LL p1, LL q1, LL p2, LL q2) {
        x1 = p1;
        y1 = q1;
        x2 = p2;
        y2 = q2;
    }
    bool valid() {
        return x1 >= 0;
    }
};

class Solution {
public:
    LL area(vector<Rect> &rects) {
        LL a = 0;
        for(auto &r : rects) {
            a += area(r);
        }
        return a;
    }
    inline LL area(const Rect &r) {
        return (r.x2 - r.x1) * (r.y2 - r.y1);
    }
    Rect solve(const Rect &outline, vector<Rect> &rects) {
        if(rects.empty()) {
            return outline;
        }
        if(area(outline) == area(rects)) {
            return Rect{};
        }
        if(rects.size() == 1) {
            return solveOne(outline, rects[0]);
        }
        Rect r = mergeSolve(outline, rects);
        if(r.valid()) {
            return r;
        }
        LL x = outline.x2 - outline.x1;
        LL y = outline.y2 - outline.y1;
        return x >= y ? splitLeftRight(outline, rects) : splitTopBottom(outline, rects);
    }
    Rect mergeSolve(const Rect outline, vector<Rect> &rects) {
        {
            bool mergable = true;
            for (int i = 1; i < rects.size(); ++i) {
                if (rects[i].y1 != rects[0].y1 || rects[i].y2 != rects[0].y2) {
                    mergable = false;
                    break;
                }
            }
            if (mergable) {
                sort(begin(rects), end(rects), [&](const Rect &r1, const Rect &r2) {
                    return r1.x1 < r2.x1;
                });
                if(rects[0].x1 > outline.x1) {
                    return Rect{outline.x1, outline.y1, rects[0].x1, outline.y2};
                }
                else if(rects.back().x2 < outline.x2) {
                    return Rect{rects.back().x2, outline.y1, outline.x2, outline.y2};
                }
                else {
                    for(int i = 0; i < rects.size() - 1; ++ i) {
                        if(rects[i].x2 != rects[i+1].x1) {
                            return Rect{rects[i].x2, outline.y1, rects[i+1].x1, outline.y2};
                        }
                    }
                }
            }
        }
        {
            bool mergable = true;
            for (int i = 1; i < rects.size(); ++i) {
                if (rects[i].x1 != rects[0].x1 || rects[i].x2 != rects[0].x2) {
                    mergable = false;
                    break;
                }
            }
            if (mergable) {
                sort(begin(rects), end(rects), [&](const Rect &r1, const Rect &r2) {
                    return r1.y1 < r2.y2;
                });
                if(rects[0].y1 > outline.y1) {
                    return Rect{outline.x1, outline.y1, outline.x2, rects[0].y1};
                }
                else if(rects.back().y2 < outline.y2) {
                    return Rect{outline.x1, rects.back().y2, outline.x2, outline.y2};
                }
                else {
                    for(int i = 0; i < rects.size() - 1; ++ i) {
                        if(rects[i].y2 != rects[i+1].y1) {
                            return Rect{outline.x1, rects[i].y2, outline.x2, rects[i+1].y1};
                        }
                    }
                }
            }
        }
        return Rect{};
    }
    Rect splitLeftRight(const Rect &outline, vector<Rect> &rects) {
        LL mid = (outline.x1 + outline.x2) / 2;
        vector<Rect> left, right;
        for(auto r : rects) {
            if(r.x2 <= mid) {
                left.push_back(r);
            }
            else if(r.x1 >= mid) {
                right.push_back(r);
            }
            else {
                left.push_back(Rect{r.x1, r.y1, mid, r.y2});
                right.push_back(Rect{mid, r.y1, r.x2, r.y2});
            }
        }
        Rect lr = solve(Rect{outline.x1, outline.y1, mid, outline.y2}, left);
        Rect rr = solve(Rect{mid, outline.y1, outline.x2, outline.y2}, right);
        if(!lr.valid()) {
            return rr;
        }
        if(!rr.valid()) {
            return lr;
        }
        else {
            return Rect{lr.x1, lr.y1, rr.x2, rr.y2};
        }
    }
    Rect splitTopBottom(const Rect &outline, vector<Rect> &rects) {
        LL mid = (outline.y1 + outline.y2) / 2;
        vector<Rect> bottom, top;
        for(auto r : rects) {
            if(r.y2 <= mid) {
                bottom.push_back(r);
            }
            else if(r.y1 >= mid) {
                top.push_back(r);
            }
            else {
                bottom.push_back(Rect{r.x1, r.y1, r.x2, mid});
                top.push_back(Rect{r.x1, mid, r.x2, r.y2});
            }
        }
        Rect br = solve(Rect{outline.x1, outline.y1, outline.x2, mid}, bottom);
        Rect tr = solve(Rect{outline.x1, mid, outline.x2, outline.y2}, top);
        if(!br.valid()) {
            return tr;
        }
        if(!tr.valid()) {
            return br;
        }
        else {
            return Rect{br.x1, br.y1, tr.x2, tr.y2};
        }
    }
    Rect solveOne(const Rect &out, const Rect &in) {
        if(out.x1 == in.x1 && out.y1 == in.y1) {
            if(out.y2 == in.y2) {
                return Rect{in.x2, out.y1, out.x2, out.y2};
            }
            else {
                return Rect{out.x1, in.y2, out.x2, out.y2};
            }
        }
        else if(out.x2 == in.x2 && out.y2 == in.y2) {
            if(out.y1 == in.y1) {
                return Rect{out.x1, out.y1, in.x1, out.y2};
            }
            else {
                return Rect{out.x1, out.y1, out.x2, in.y1};
            }
        }
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    Rect outline;
    cin >> outline.x1 >> outline.y1 >> outline.x2 >> outline.y2;
    vector<Rect> rects(N-1);
    for(auto &rect : rects) {
        cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
    }
    Rect r = s.solve(outline, rects);
    cout << r.x1 << ' ' << r.y1 << ' ' << r.x2 << ' ' << r.y2 << endl;
    return 0;
}
