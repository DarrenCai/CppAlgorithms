/**
 * UVa1001
 * 奶酪里的老鼠
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 110
double d[N], w[N][N]; int x[N], y[N], z[N], r[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; int kase = 0;
    while (cin>>n && n>-1) {
        for (short i=1; i<=n; ++i) cin >> x[i] >> y[i] >> z[i] >> r[i];
        cin >> x[0] >> y[0] >> z[0] >> x[n+1] >> y[n+1] >> z[n+1];
        r[0] = r[++n] = 0;
        for (short i=0; i<=n; ++i) {
            w[i][i] = 0.;
            for (short j=i+1; j<=n; ++j) {
                double a = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j])), b = r[i]+r[j];
                w[i][j] = w[j][i] = a>b ? (a-b)*10 : 0.;
            }
            d[i] = w[0][i];
        }
        bool visit[N] = {false}; visit[0] = true;
        for (short i=1; i<=n; ++i) {
            short x; double m = __DBL_MAX__;
            for (short j=1; j<=n; ++j) if (!visit[j] && d[j]<m) m = d[x=j];
            visit[x] = true;
            for (short j=0; j<=n; ++j) d[j] = min(d[j], d[x] + w[x][j]);
        }
        cout << "Cheese " << ++kase << ": Travel time = " << int(d[n]+.5) << " sec" << endl;
    }
    return 0;
}