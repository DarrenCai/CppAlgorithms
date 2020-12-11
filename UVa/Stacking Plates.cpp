/**
 * UVa1289
 * 叠盘子
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 60
#define D 10100
struct {short c, p;} f[D+1], f1[D+1];
short s[N][N], h[N], h1[N], ss[N], d[N*N], n;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin >> n) {
        for (short i=0; i<n; ++i) {
            cin >> h[i];
            for (short j=0; j<h[i]; ++j) cin >> s[i][j];
            h1[i] = h[i] = unique(s[i], s[i]+h[i]) - s[i];
        }
        short t = 0;
        for (short i=0; i<n; ++i) for (short j=0; j<h[i]; ++j) d[t++] = s[i][j];
        sort(d, d+t);
        short cur = D;
        for (short i=t-1; i>=0; --i) {
            if (d[i] < cur) {
                f1[cur].p = f[cur].p = d[i]; f[cur = d[i]].c = 1; f1[cur].c = 1;
            } else ++f[cur].c, ++f1[cur].c;
        }
        f[cur].p = 0; f[0].c = 0; cur = d[t-1];
        short m = 0;
        while (f[cur].p > 0 || f[cur].c > 0) {
            short c = 0;
            for (short i=0; i<n; ++i) if (h[i]>0 && s[i][h[i]-1] == cur) {
                if (h[i]-- > 1) {
                    if (s[i][h[i]-1] < f[cur].p || (h[i]+1 < h1[i] && f1[cur].c > 1)) {
                        ++m; h1[i] = h[i];
                    } else {
                        ss[c++] = i;
                    }
                }
                if (--f[cur].c == 0) {
                    cur = f[cur].p;
                    for (short j=0; j<c-1; ++j) ++m, h1[ss[j]] = h[ss[j]];
                    break;
                }
            }
        }
        cout << "Case " << ++kase << ": " << (m<<1) + n - 1 << endl;
    }
    return 0;
}