/**
 * UVa1299/LA2221
 * 边境
 * NEERC 2000
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define M 1010
#define N 55
short a[M], b[M], x[N], y[N], m, n; double dis[N][N], d[N]; bool c[N][N];

int s(int xa, int ya, int xb, int yb, int xc, int yc) {
    return ya*(xc-xb) + yb*(xa-xc) + yc*(xb-xa);
}

bool check(int xa, int ya, int xb, int yb) {
    for (short i=0; i<m; ++i) if (s(xa, ya, xb, yb, a[i], b[i]) >= 0) return false;
    return true;
}

double solve() {
    for (short i=0; i<n; ++i) cin >> x[i] >> y[i];
    for (short i=0; i<m; ++i) cin >> a[i] >> b[i];
    for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j)
        dis[i][j] = dis[j][i] = sqrt(1.*(x[i]-x[j])*(x[i]-x[j]) + 1.*(y[i]-y[j])*(y[i]-y[j]));
    double ans = __DBL_MAX__;
    if (m > 0) {
        for (short i=0; i<n; ++i) {
            c[i][1] = true;
            for (short j=n-2; j>0; --j) if (!(c[i][n-j] = check(x[(i+j)%n], y[(i+j)%n], x[i], y[i]))) break;
        }
        for (short i=0; i<n; ++i) {
            d[0] = 0.;
            for (short j=1; j<=n; ++j) {
                d[j] = __DBL_MAX__;
                short jj = (i+j)%n;
                for (short k=1; k<=j; ++k) {
                    if (!c[jj][k]) break;
                    d[j] = min(d[j], d[j-k]+dis[jj][(jj+n-k)%n]);
                }
            }
            ans = min(ans, d[n]);
        }
    } else {
        for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j) for (short k=j+1; k<n; ++k)
            if (s(x[k], y[k], x[j], y[j], x[i], y[i])) ans = min(ans, dis[i][j] + dis[j][k] + dis[k][i]);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}