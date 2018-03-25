/**
 * UVa149
 * 森林
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct range {
    float min, max;
    range(float min, float max) {
        this->min = min;
        this->max = max;
    }

    bool operator < (const range& rhs) const {
        return min < rhs.min || (min==rhs.min && max<rhs.max);
    }
    bool notIntersects(const range& rhs) const {
        return rhs.max<min-0.01 || max<rhs.min-0.01;
    }
};

float d, x, y, deg=57.295779513082321; vector<range> v; int total; bool f[8];

bool calc(int i, int j) {
    float dx = i-x, dy = j-y, s = asin(d/sqrt(dx*dx + dy*dy)/2)*deg;
    if (s <= 0.005) return true;
    float a = atan2(dy, dx)*deg; range r(a-s, a+s);
    if (v.empty()) {
        v.push_back(r); ++total;
    } else {
        vector<range>::iterator it = lower_bound(v.begin(), v.end(), r);
        if ((it==v.begin() && it->notIntersects(r))) {
            v.insert(it, r); ++total;
        } else if (it==v.end()) {
            vector<range>::reverse_iterator it1 = v.rbegin();
            if (it1->notIntersects(r)) {
                v.insert(it, r); ++total;
            } else it1->max = max(it1->max, r.max);
        } else if (!it->notIntersects(r)) {
            it->min = r.min;
            if (it!=v.begin()) {
                vector<range>::iterator it1 = it-1;
                if (!it1->notIntersects(*it)) {
                    it->min = it1->min;
                    it = v.erase(it1);
                }
            }
            if (r.max > it->max) {
                it->max = r.max;
                vector<range>::iterator it1 = it+1;
                while (it1 != v.end()) {
                    if (!it->notIntersects(*it1)) {
                        it->max = it1->max;
                        it1 = v.erase(it1);
                    } else break;
                }
            }
        } else {
            vector<range>::iterator it1 = it-1;
            if (it1->notIntersects(r)) {
                v.insert(it, r); ++total;
            } else if (r.max > it1->max) {
                it1->max = r.max;
                if (!it1->notIntersects(*it)) {
                    it1->max = it->max;
                    v.erase(it);
                }
            }
        }
    }
    return false;
}

void calc(int l, int r, int t, int b) {
    float dx = l-x, dy = 1-y;
    if (f[0]) f[0] = asin(d/sqrt(dx*dx + y*y)/2)*deg > 0.005;
    if (f[7]) f[7] = asin(d/sqrt(dx*dx + dy*dy)/2)*deg > 0.005;
    dx = r-x;
    if (f[3]) f[3] = asin(d/sqrt(dx*dx + y*y)/2)*deg > 0.005;
    if (f[4]) f[4] = asin(d/sqrt(dx*dx + dy*dy)/2)*deg > 0.005;
    dx = 1-x; dy = b-y;
    if (f[1]) f[1] = asin(d/sqrt(x*x + dy*dy)/2)*deg > 0.005;
    if (f[2]) f[2] = asin(d/sqrt(dx*dx + dy*dy)/2)*deg > 0.005;
    dy = t-y;
    if (f[5]) f[5] = asin(d/sqrt(dx*dx + dy*dy)/2)*deg > 0.005;
    if (f[6]) f[6] = asin(d/sqrt(x*x + dy*dy)/2)*deg > 0.005;
    for (int j=0; f[0] && j>b; --j)
        if (calc(l, j)) break;
    for (int j=0; f[1] && j>=l; --j)
        if (calc(j, b)) break;
    for (int j=1; f[2] && j<r; ++j)
        if (calc(j, b)) break;
    for (int j=0; f[3] && j>=b; --j)
        if (calc(r, j)) break;
    for (int j=1; f[4] && j<t; ++j)
        if (calc(r, j)) break;
    for (int j=1; f[5] && j<=r; ++j)
        if (calc(j, t)) break;
    for (int j=0; f[6] && j>l; --j)
        if (calc(j, t)) break;
    for (int j=1; f[7] && j<=t; ++j)
        if (calc(l, j)) break;
    if (f[0] || f[1] || f[2] || f[3] || f[4] || f[5] || f[6] || f[7])
        calc(l-1, r+1, t+1, b-1);
}

int main()
{
    while (cin>>d>>x>>y && d) {
        total = 0;
        for (char i=0; i<8; ++i) f[i] = true;
        calc(0, 1, 1, 0);
        cout << total << endl;
        v.clear();
    }
    return 0;
}