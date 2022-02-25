/**
 * UVa10382
 * 喷⽔装置
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 10050
struct node {
    double l, r;
    bool operator< (const node& rhs) const {
        return l < rhs.l;
    }
} s[N];
int n, l, w;

int solve() {
    double w2 = w/2.; w2 *= w2;
    for (int i=0; i<n; ++i) {
        int p, r; cin >> p >> r; double x = 1.*r*r - w2;
        x <= 0 ? s[i].l = l = s[i].r = l : (x = sqrt(x), s[i].l = p-x,  s[i].r = p+x);
    }
    sort(s, s+n);
    int c = 0, k = 0; double x = 0;
    while (x < l) {
        if (k >= n || s[k].l > x) return -1;
        ++ c;
        double y = s[k].r;
        while (++k < n && s[k].l <= x) if (s[k].r > y) y = s[k].r;
        x = y;
    }
    return c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> l >> w) cout << solve() << endl;
    return 0;
}