/**
 * UVa1520/LA5915
 * NEERC 2011
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 50020
double p[N], x[N], y[N]; int m, n;

void solve() {
    for (int i=1; i<=n; ++i) cin >> p[i] >> x[i] >> y[i];
    cin >> m;
    while (m--) {
        int t1, t2, x1, x2; double ans = 0.; cin >> t1 >> t2 >> x1 >> x2;
        for (int i=t1; i<=t2; ++i) {
            if (x1 <= x[i] && x[i] <= x2) ans = max(ans, y[i]);
            else if (x1 > x[i]) ans = max(ans, max(y[i]*(1-(x1-x[i])*(x1-x[i])/(p[i]-x[i])/(p[i]-x[i])), 0.));
            else ans = max(ans, max(y[i]*(1-(x2-x[i])*(x2-x[i])/(p[i]-x[i])/(p[i]-x[i])), 0.));
        }
        cout << ans << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); cout << fixed << setprecision(4);
    while (cin >> n) solve();
    return 0;
}