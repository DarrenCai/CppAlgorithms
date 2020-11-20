/**
 * UVa10163
 * 仓库守卫
 */

#include <iostream>
using namespace std;

#define M 32
#define N 105
#define INF 32000
short m, n, d[M][N], p[M];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n && m) {
        for (short i=0; i<m; ++i) cin >> p[i];
        for (short i=0; i<=n; ++i) d[0][i] = i==0 ? INF : p[0]/i;
        for (short i=1; i<m; ++i) {
            for (short j=0; j<=n; ++j) d[i][j] = d[i-1][j];
            for (short j=0; j<n; ++j) for (short k=1; j+k <= n; ++k)
                d[i][j+k] = max(d[i][j+k], min(d[i-1][j], short(p[i]/k)));
        }
        short l = d[m-1][n];
        if (l == 0) cout << "0 0" << endl;
        else {
            for (short i=0; i<m; ++i) d[i][0] = 0;
            for (short i=0; i<m; ++i) for (short v=n; v>0; --v) {
                if (i==0) {
                    d[i][v] = p[i]/l == v ? p[i] : INF;
                } else if (p[i] < l || p[i]/l > v) d[i][v] = d[i-1][v];
                else d[i][v] = min(int(d[i-1][v]), p[i] + d[i-1][v-p[i]/l]);
            }
            cout << l << ' ' << d[m-1][n] << endl;
        }
    }
    return 0;
}