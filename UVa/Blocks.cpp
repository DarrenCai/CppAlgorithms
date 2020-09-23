/**
 * UVa10559
 * 方块消除
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 250
struct section {
    int s, len;
} s[N][N>>1];
short n, m, pc, a[N], c[N], x[N], p[N], mp[N]; int d[N][N], df[N][N][N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t, kase = 0; cin >> t;
    while (kase ++ < t) {
        memset(c, 0, sizeof(c)); memset(d, 0, sizeof(d)); memset(df, 0, sizeof(df));
        pc = m = 0; cin >> n;
        for (short i=0, j=0; i<n; ++i) {
            cin >> a[i]; m = max(m, a[i]);
            if (a[i] != a[j]) {
                x[j] = c[a[j]]; mp[i-1] = mp[j] = pc; p[pc++] = j;
                s[a[j]][c[a[j]]].s = j; s[a[j]][c[a[j]]++].len = i-j; j = i;
            }
            if (i == n-1) {
                x[j] = c[a[j]]; mp[i] = mp[j] = pc; p[pc++] = j;
                s[a[j]][c[a[j]]].s = j; s[a[j]][c[a[j]]++].len = i-j+1;
            }
        }
        for (int i=1; i<=m; ++i) for (int j=0; j<c[i]; ++j)
            d[mp[s[i][j].s]][mp[s[i][j].s]] = s[i][j].len * s[i][j].len;
        for (short l=1; l<pc; ++l) for (short i=0, ii=l; ii<pc; ++i, ++ii) {
            for (short j=i; j<ii; ++j) d[i][ii] = max(d[i][ii], d[i][j]+d[j+1][ii]);
            if (a[p[i]] == a[p[ii]]) {
                short len1 = s[a[p[i]]][x[p[i]]].len, len2 = s[a[p[i]]][x[p[ii]]].len, size = n - len1 - len2;
                short i1 = s[a[p[i]]][x[p[i]]].s + len1, i2 = s[a[p[i]]][x[p[ii]]].s-1;
                for (short k=x[p[i]]+1; k<x[p[ii]]; ++k) {
                    short size1 = size-s[a[p[i]]][k].len, i3 = s[a[p[i]]][k].s, i4 = s[a[p[i]]][k].s-1;
                    for (short r=0; r<=size1; ++r)
                        df[r][i][ii] = max(df[r][i][ii], df[r+len1][mp[i3]][ii] + d[mp[i1]][mp[i4]]);
                }
                for (short r=0; r<=size; ++r)
                    df[r][i][ii] = max(df[r][i][ii], (r+len1+len2)*(r+len1+len2) + d[mp[i1]][mp[i2]]);
                d[i][ii] = max(d[i][ii], df[0][i][ii]);
            }
        }
        cout << "Case " << kase << ": " << d[0][pc-1] << endl;
    }
    return 0;
}