/**
 * UVa1609
 * 不公平竞赛
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1024
char s[N+1][N+2]; short f, n, t[2][N], p[N+1], a[N], b[N], c[N], d[N];

void solve() {
    short an=0, bn=0, cn=0, dn=0, ff=f^1; memset(p, 0, sizeof(p));
    for (short i=0; i<n; ++i) s[1][t[f][i]]=='1' ? a[an++]=t[f][i] : b[bn++] = t[f][i];
    for (short i=0; i<bn; ++i) for (short j=0, br=0; !br && j<an; ++j) if (!p[a[j]] && s[a[j]][b[i]]=='1')
        br = 1, p[a[j]] = b[i], p[b[i]] = a[j], cout << a[j] << ' ' << b[i] << endl;
    for (short i=0; i<an; ++i) if (!p[a[i]]) c[cn++] = a[i];
    for (short i=0; i<bn; ++i) if (!p[b[i]]) d[dn++] = b[i];
    p[1] = c[0], p[c[0]] = 1, cout << "1 " << c[0] << endl;
    for (short i=1; i<dn; i+=2) p[d[i-1]] = d[i], p[d[i]] = d[i-1], cout << d[i-1] << ' ' << d[i] << endl;
    for (short i=2; i<cn; i+=2) p[c[i-1]] = c[i], p[c[i]] = c[i-1], cout << c[i-1] << ' ' << c[i] << endl;
    if (dn & 1) p[c[cn-1]] = d[dn-1], p[d[dn-1]] = c[cn-1], cout << c[cn-1] << ' ' << d[dn-1] << endl;
    for (short i=0, j=0; i<n; ++i) if (s[t[f][i]][p[t[f][i]]]=='1') t[ff][j++] = t[f][i];
    if (f=ff, n>>=1) solve();
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        for (short i=1; i<=n; ++i) t[0][i-1] = i+1, cin >> (s[i]+1);
        --n; f=0; solve();
    }
    return 0;
}