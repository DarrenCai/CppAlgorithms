/**
 * UVa1429/LA4330
 * Beijing 2008
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void solve() {
    double h, d, v; cin >> h >> d >> v;
    double k = 12*v/h/d/d, x = M_PI / 2;
    if (abs(k/x - 1) > 1e-6) {
        double l = 0., r = x, y0 = -1., y = 0., c;
        while (y != y0) {
            y0 = y;
            x = (l+r) / 2;
            c = cos(x);
            y = x - sin(2*x) + c*c*c*log(c/(1-sin(x)));
            y > k ? r = x : l = x;
        }
    }
    cout << d*(1+cos(x))/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}