/**
 * UVa1347/LA3305
 * 旅行
 * SEERC 2005
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 2010
double d[N][N], s[N][N], x[N], y[N]; int n;

double solve() {
    for (int i=0; i<n; ++i) {
        cin >> x[i] >> y[i];
        for (int j=0; j<=i; ++j) {
            s[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            d[i][j] = d[j][i] =__DBL_MAX__;
        }
    }
    d[0][0] = 0;
    for (int i=0; i<n; ++i) for (int j=i; j<n; ++j) {
        d[j][j] = min(d[j][j], min(d[i][j] + s[i][j], d[j][i] + s[i][j]));
        int k = j+1;
        if (k==n || (i==j && i)) continue;
        d[i][k] = min(d[i][k], d[i][j] + s[j][k]);
        d[k][j] = min(d[k][j], d[i][j] + s[i][k]);
        d[j][k] = min(d[j][k], d[j][i] + s[i][k]);
        d[k][i] = min(d[k][i], d[j][i] + s[j][k]);
    }
    return d[n-1][n-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);
    while (cin >> n) cout << solve() << endl;
    return 0;
}