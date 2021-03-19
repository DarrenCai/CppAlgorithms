/**
 * UVa11181
 * 条件概率
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 21
double d[N], p[N], t; short n, r;

void calc(short i, int x, short rr) {
    if (i==n && rr==r) {
        double v = 1.;
        for (short j=0; j<n; ++j) v *= x & 1<<j ? p[j] : 1-p[j];
        for (short j=0; j<n; ++j) if (x & 1<<j) d[j] += v;
        t += v;
    } else if (i<n) {
        if (rr == r) {
            calc(i+1, x, r);
        } else if (rr < r) {
            calc(i+1, x ^ 1<<i, rr+1);
            calc(i+1, x, rr);
        }
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    short k = 0;
    while (cin>>n>>r && n) {
        for (short i=0; i<n; ++i) cin >> p[i];
        cout << "Case " << ++k << ':' << endl;
        if (r > 0) {
            fill_n(d, n, t = .0);
            calc(0, 0, 0);
            for (short i=0; i<n; ++i) cout << d[i] / t << endl;
        } else for (short i=0; i<n; ++i) cout << .0 << endl;
    }
    return 0;
}