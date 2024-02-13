/**
 * UVa1473/LA4986
 * 马戏团的屋顶
 * NEERC 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-5
#define N 10010
double r[N], z[N]; int n;

double calc_r(double h) {
    double a = 0;
    for (int i=0; i<n; ++i) a = max(a, h/(h-z[i])*r[i]);
    return a;
}

void solve() {
    double zm = 0;
    for (int i=0; i<n; ++i) {
        double x, y; cin >> x >> y >> z[i];
        r[i] = sqrt(x*x + y*y);
        zm = max(zm, z[i]);
    }
    double l = zm + eps, r = 1e5;
    while (l+eps < r) {
        double x = (2*l + r) / 3, y = (l + 2*r) / 3;
        double u = calc_r(x), v = calc_r(y);
        u*u*x > v*v*y ? l = x + eps : r = y-eps;
    }
    cout << r << ' ' << calc_r(r) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(3);
    while (cin >> n) solve();
    return 0;
}