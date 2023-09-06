/**
 * UVa10385
 * 铁人两项
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 25
double a[N], b[N], c[N], r[N], t, x, y, z; int n;

bool judge() {
    x=0.; y=t;
    for (int i=1; i<n; ++i) {
        b[i] = 1./c[i] - 1./c[0]; a[i] = 1./r[i] - 1./r[0] - b[i]; b[i] *= t;
        if (a[i] == 0.) {
            if (b[i] < 0) return false;
        } else if (a[i] > 0.) {
            if ((z = -b[i]/a[i]) > y) return false;
            x = max(x, z);
        } else {
            if ((z = -b[i]/a[i]) < x) return false;
            y = min(y, z);
        }
    }
    return true;
}

double eval(double x) {
    double v = __DBL_MAX__;
    for (int i=1; i<n; ++i) v = min(v, a[i]*x+b[i]);
    return v;
}

void solve() {
    cin >> n;
    for (int i=n-1; i>=0; --i) cin >> c[i] >> r[i];
    if (judge()) {
        for (int i=0; i<70; ++i) {
            double l = (2.*x + y)/3., r = (x + 2.*y)/3., a = eval(l), b = eval(r);
            a > b ? y = r : x = l;
            z = max(a, b);
        }
        cout << "The cheater can win by " << (long long)(3600*z + .5) 
            << " seconds with r = " << t-y << "km and k = " << y << "km." << endl;
    } else cout << "The cheater cannot win." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> t) solve();
    return 0;
}