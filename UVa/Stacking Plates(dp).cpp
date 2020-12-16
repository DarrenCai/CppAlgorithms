/**
 * UVa1289
 * 叠盘子
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 60
#define M 6000
struct {short d, c;} f[N*N];
short s[N][N], h[N], a[N*N], d[N*N][N], n;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin >> n) {
        for (short i=0; i<n; ++i) {
            cin >> h[i];
            for (short j=0; j<h[i]; ++j) cin >> s[i][j];
            h[i] = unique(s[i], s[i]+h[i]) - s[i];
        }
        short t = 0;
        for (short i=0; i<n; ++i) for (short j=0; j<h[i]; ++j) a[t++] = s[i][j];
        sort(a, a+t);
        short c = -1, pre = -1;
        for (short i=0; i<t; ++i) {
            if (a[i] != pre) {
                f[++c].d = a[i]; f[c].c = 1; pre = a[i];
            } else ++f[c].c;
        }
        for (short i=0; i<n; ++i) d[0][i] = (f[0].c<<1) - 2*(s[i][0] == f[0].d);
        for (short i=1; i<=c; ++i) for (short j=0; j<n; ++j) {
            d[i][j] = M;
            for (short k=0; k<n; ++k) {
                short v = d[i-1][k]+2+(f[i].c<<1);
                short p = lower_bound(s[k], s[k]+h[k], f[i].d) - s[k];
                if (p < h[k] && s[k][p] == f[i].d) {
                    v -= 2;
                    if (j==k && f[i].c == 1) {
                        p = lower_bound(s[k], s[k]+h[k], f[i-1].d) - s[k];
                        if (p < h[k] && s[k][p] == f[i-1].d) v -= 2;
                    }
                }
                if (j != k) {
                    p = lower_bound(s[j], s[j]+h[j], f[i].d) - s[j];
                    if (p < h[j] && s[j][p] == f[i].d) v -= 2;
                }
                d[i][j] = min(d[i][j], v);
            }
        }
        short ans = M; for (short i=0; i<n; ++i) ans = min(ans, d[c][i]);
        cout << "Case " << ++kase << ": " << ans - n + 1 << endl;
    }
    return 0;
}