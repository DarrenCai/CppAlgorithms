/**
 * UVa1635
 * 无关的元素
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 100100
unsigned short prim[7000], p=0, cc; int g[7000], c[7000], a[N], t;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    bool f[65536] = {0};
    for (unsigned short i=2; i<256; ++i) if (!f[i]) for (int j=i*i; j<65535; j+=i) f[j] = true;
    for (unsigned short i=2; i<65535; ++i) if (!f[i]) prim[p++] = i;
    int n, m;
    while (cin >> n >> m) {
        memset(c, cc=0, sizeof(c));
        for (short i=0; i<p && prim[i]*prim[i] <= m; ++i) if (m % prim[i] == 0) {
            g[cc] = prim[i];
            while (m % prim[i] == 0) ++c[cc], m /= g[cc];
            ++ cc;
        }
        if (m > 1) ++c[cc], g[cc++] = m;
        --n; t = 0; short cnt = cc;
        for (int i=1, nn=n>>1, ii, j; i<=nn; ++i) {
            for (j=0, ii=i; j<cc && g[j]*g[j] <= i; ++j) if (ii % g[j] == 0)
                while (ii % g[j] == 0) {
                    ii /= g[j]; if (++c[j] == 1) ++cnt;
                }
            while (ii > 1 && j < cc) if (ii % g[j++] == 0) {
                if (++c[j-1] == 1) ++cnt;
                break;
            }
            for (j=0, ii=n-i+1; j<cc && g[j]*g[j] <= ii; ++j) if (ii % g[j] == 0)
                while (ii % g[j] == 0) {
                    ii /= g[j]; if (--c[j] == 0) --cnt;
                }
            while (ii > 1 && j < cc) if (ii % g[j++] == 0) {
                if (--c[j-1] == 0) --cnt;
                break;
            }
            if (cnt == 0) {
                a[t++] = i+1;
                if (i<<1 < n) a[t++] = n-i+1;
            }
        }
        cout << t << endl;
        if (t > 0) {
            sort(a, a+t); cout << a[0];
        }
        for (int i=1; i<t; ++i) cout << ' ' << a[i];
        cout << endl;
    }
    return 0;
}