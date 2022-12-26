/**
 * UVa1476/LA5009
 * 误差曲线
 * ChengDu 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 10010
int a[N], b[N], c[N], n;

bool check(double y) {
    double x0 = 0., x1 = 1000.;
    for (int i=0; i<n; ++i) {
        if (a[i] > 0) {
            double d = 1.*b[i]*b[i]-4*(c[i]-y)*a[i];
            if (d < 0) return false;
            d = sqrt(d);
            x0 = max(x0, -.5*(b[i]+d)/a[i]);
            x1 = min(x1, .5*(d-b[i])/a[i]);
        } else if (b[i] == 0) {
            if (c[i] > y) return false;
        } else b[i] > 0 ? x1 = min(x1, (y-c[i])/b[i]) : x0 = max(x0, (y-c[i])/b[i]);
        if (x0 > x1) return false;
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i] >> b[i] >> c[i];
    double low = -6e6, high = 5000;
    while ((long long)(10000*low+.5) < (long long)(10000*high+.5)) {
        double mid = (low + high) / 2;
        check(mid) ? high = mid : low = mid;
    }
    cout << high << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}