/**
 * UVa1579
 * 俄罗斯套娃
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 10000000
#define N 600

short s[N], c[N], a[N][N][N], n, m; int dd[N][N], d[N][N];

int calc(short i, short j) {
    int &ref = dd[i][j];
    if (ref < INF) return ref;
    if (i==j) {
        a[i][j][0] = s[i];
        return ref = 0;
    }
    for (short k=i; k<j; ++k) {
        calc(i, k); calc(k+1, j);
        int v = dd[i][k] + dd[k+1][j];
        short k1 = k-i, k2 = j-k-1;
        while (v < ref && k1 >=0 && k2 >= 0) {
            ++v;
            a[i][k][k1] > a[k+1][j][k2] ? --k1 : --k2;
        }
        ref = min(v, ref);
    }
    short k=0, t=0;
    while (k<j-i && a[i+1][j][k] < s[i]) a[i][j][t++] = a[i+1][j][k++];
    a[i][j][t++] = s[i];
    while (k<j-i) a[i][j][t++] = a[i+1][j][k++];
    return ref;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    while (cin >> n) {
        m = 0;
        for (short i=1; i<=n; ++i) {
            cin >> s[i];
            m = max(m, s[i]);
        }
        memset(d, 1, sizeof(d));
        memset(dd, 1, sizeof(dd));
        for (short i=1; i<=n; ++i) {
            memset(c, 0, (m+1)*sizeof(short));
            short x = 0;
            for (short j=i; j<=n; ++j) {
                if (++c[s[j]] > 1) break;
                x = max(x, s[j]);
                if (x == j-i+1) d[i][j] = calc(i, j);
            }
        }
        for (short l=1; l<=n; ++l) for (short i=1, ii; (ii=i+l-1) <= n; ++i) if (d[i][ii] >= INF)
            for (short k=i; k<ii; ++k) d[i][ii] = min(d[i][ii], d[i][k] + d[k+1][ii]);
        d[1][n] >= INF ? cout << "impossible" << endl : cout << d[1][n] << endl;
    }
    return 0;
}