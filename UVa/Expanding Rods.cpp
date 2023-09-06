/**
 * UVa10668
 * 变长的木棍
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double l, n, c;

double solve() {
    if (l==0. || n==0. || c==0.) return 0.;
    double f = 1. + n*c, x = M_PI_2, y = f*sin(x);
    while (x != y) x = y, y = f*sin(x);
    return .5*l*tan(.5*x);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin>>l>>n>>c && l>=0.) cout << solve() << endl;
    return 0;
}