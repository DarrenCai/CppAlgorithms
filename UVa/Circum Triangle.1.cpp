/**
 * UVa11186
 * 圆周上的三角形
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 505
double t[N], r, dtr = 0.017453292519943295; int n;

void solve() {
    for (int i=0; i<n; ++i) cin >> t[i], t[i] *= dtr;
    sort(t, t+n);
    double s = 0.;
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) s += sin(t[j]-t[i])*(n-(j-i<<1));
    cout << (long long)(.5*(r*r*s + 1)) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> r && (n || r)) solve();
    return 0;
}
