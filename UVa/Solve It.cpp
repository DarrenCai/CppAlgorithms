/**
 * UVa10341
 * 解方程
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int p, q, r, s, t, u;

double eval(double x) {
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

void solve() {
    double low = 0., high = 1.;
    if (eval(0.) < 0 || eval(1.) > 0) {
        cout << "No solution" << endl;
        return;
    }
    while (int(10000*low+.5) < int(10000*high+.5)) {
        double mid = (low + high) / 2;
        eval(mid) > 0 ? low = mid : high = mid;
    }
    cout << high << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> p >> q >> r >> s >> t >> u) solve();
    return 0;
}