/**
 * UVa1629
 * 切蛋糕
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 22
short n, m, k, d[N][N][N][N], dp[N][N][N][N], inf = 16360;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin >> n >> m >> k) {
        for (short r=1; r <= n; ++r) for (short c=1; c <= m; ++c) d[r][c][1][1] = 0;
        for (short i=0, r, c; i<k; ++i) cin >> r >> c, d[r][c][1][1] = 1;
        for (short w=1; w<=m; ++w) for (short h=1; h<=n; ++h)
            for (short r=1; r+h <= n+1; ++r) for (short c=1; c+w <= m+1; ++c) {
                if (w>1) d[r][c][w][h] = d[r][c][w-1][h] + d[r][c+w-1][1][h];
                else if (h>1) d[r][c][w][h] = d[r][c][w][h-1] + d[r+h-1][c][w][1];
            }
        for (short w=1; w<=m; ++w) for (short h=1; h<=n; ++h)
            for (short r=1; r+h <= n+1; ++r) for (short c=1; c+w <= m+1; ++c) {
                short &ref = dp[r][c][w][h];
                if (d[r][c][w][h] == 0) ref = inf;
                else if (d[r][c][w][h] == 1) ref = 0;
                else {
                    short v; ref = inf;
                    for (short ww=1; ww<w; ++ww)
                        ref = min(ref, min(v = dp[r][c][ww][h] + dp[r][c+ww][w-ww][h] + h, inf));
                    for (short hh=1; hh<h; ++hh)
                        ref = min(ref, min(v = dp[r][c][w][hh] + dp[r+hh][c][w][h-hh] + w, inf));
                }
            }
        cout << "Case " << ++kase << ": " << dp[1][1][m][n] << endl;
    }
    return 0;
}