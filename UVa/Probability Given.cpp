/**
 * UVa11181
 * 条件概率
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 21
double d[N][1<<N], p[N]; short n, r;

double dp(int x, short nn, short rr) {
    double& ref = d[rr][x];
    if (ref >= .0) return ref;
    if (rr > nn) return ref = .0;
    if (rr == 0) {
        ref = 1.;
        for (int i=0; i<n; ++i) if (x & 1<<i) ref *= 1-p[i];
    } else {
        ref = .0;
        for (int i=0; i<n; ++i) if (x & 1<<i) ref += p[i] * dp(x ^ 1<<i, nn-1, rr-1) / rr;
    }
    return ref;
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
            for (short i=0; i<=r; ++i) fill_n(d[i], 1<<n, -1.);
            int x = (1<<n)-1;
            dp(x, n, r);
            for (short i=0; i<n; ++i) cout << p[i]*d[r-1][x ^ 1<<i]/d[r][x] << endl;
        } else for (short i=0; i<n; ++i) cout << .0 << endl;
    }
    return 0;
}