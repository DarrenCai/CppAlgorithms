/**
 * UVa12300
 * 最小正多边形
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int xa, ya, xb, yb, n;

double solve() {
    int d = (xa-xb)*(xa-xb) + (ya-yb)*(ya-yb);
    if (n==3) return .4330127018922192982941510309*d;
    if (~n&1) return n*sin(6.28318530717958647692/n)*d/8;
    double t = sin(M_PI*(n>>1)/n);
    return n*sin(6.28318530717958647692/n)*d/8/t/t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    while (cin >> xa >> ya >> xb >> yb >> n && n) cout << solve() << endl;
    return 0;
}