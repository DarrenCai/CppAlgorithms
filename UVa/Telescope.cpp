/**
 * UVa1543
 * 圆和多边形
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

#define N 50
#define P 6.283185307179586
short n, m; double p[N], s[N][N][N], d[N][N][N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin >> n >> m && n) {
        for (short i=0; i<n; ++i) cin >> p[i], p[i] *= P;
        for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j) for (short k=j+1; k<n; ++k) {
            double t1 = p[j] - p[i], t2 = p[k] - p[j];
            s[i][j][k] = .5*(sin(t1) + sin(t2) - sin(t1+t2));
        }
        memset(d, 0, sizeof(d));
        for (short l=3; l<=m; ++l) for (short i=0; i<n; ++i)
            for (short j=i+l-1; j<n; ++j) for (short k=i+1; k<j; ++k) {
                d[i][j][l] = max(d[i][j][l], s[i][k][j] + d[k][j][l-1]);
            }
        double ans = 0;
        for (short i=0; i<n; ++i) for (short j=i+m-1; j<n; ++j) ans = max(ans, d[i][j][m]);
        cout << ans << endl;
    }
    return 0;
}