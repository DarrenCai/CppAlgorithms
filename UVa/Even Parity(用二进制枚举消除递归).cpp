/**
 * UVa11464
 * 偶数矩阵
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20
#define INF 1000
short a[N][N], c[N][N], n;

short check(int s) {
    short t = 0; memset(c, 0, sizeof(c));
    for (short i=0; i<n; ++i, s>>=1) {
        if (s&1) {
            if (!a[0][i]) ++t;
            if (i > 0) ++c[0][i-1];
            if (i+1 < n) ++c[0][i+1];
            ++c[1][i];
        } else if (a[0][i]) return INF;
    }
    for (short i=1; i<n; ++i) for (short j=0; j<n; ++j) if (a[i][j] || c[i-1][j]&1) {
        if ((~c[i-1][j]) & 1) return INF;
        if (!a[i][j]) ++t;
        if (j > 0) ++c[i][j-1];
        if (j+1 < n) ++c[i][j+1];
        if (i+1 < n) ++c[i+1][j];
    }
    for (short (&r)[N] = c[n-1], j=0; j<n; ++j) if (r[j] & 1) return INF;
    return t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> n;
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) cin >> a[i][j];
        short ans = INF;
        for (int s = (1<<n)-1; s>=0; --s) ans = min(ans, check(s));
        cout << "Case " << kase << ": " << (ans >= INF ? -1 : ans) << endl;
    }
    return 0;
}