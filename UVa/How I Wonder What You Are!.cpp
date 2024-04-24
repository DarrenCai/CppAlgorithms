/**
 * UVa1373/LA3616
 * Yokohama 2006
 */

#include <iostream>
#include <cmath>
using namespace std;

#define M 505
double x[M], y[M], z[M], l[M]; int m, n; bool vis[M];

int solve() {
    for (int i=0; i<m; ++i) cin >> x[i] >> y[i] >> z[i], l[i] = sqrt(x[i]*x[i]+y[i]*y[i]+z[i]*z[i]), vis[i] = false;
    cin >> n;
    for (int i=0; i<n; ++i) {
        double tx, ty, tz, t; cin >> tx >> ty >> tz >> t; t = sqrt(tx*tx+ty*ty+tz*tz)*cos(t);
        for (int j=0; j<m; ++j) if (!vis[j] && x[j]*tx+y[j]*ty+z[j]*tz > l[j]*t) vis[j] = true;
    }
    int ans = 0;
    for (int i=0; i<m; ++i) if (vis[i]) ++ans;
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m && m) cout << solve() << endl;
    return 0;
}