/**
 * UVa11464
 * 偶数矩阵
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20
#define INF 1000
short a[N][N], c[N][N], c0[N], c1[N], n;

short calc() {
    short t = 0;
    for (short i=1; i<n; ++i) for (short j=0; j<n; ++j) {
        if (a[i][j]) {
            if ((~c[i-1][j]) & 1) return INF;
            if (j > 0) ++c[i][j-1];
            if (j+1 < n) ++c[i][j+1];
            if (i+1 < n) ++c[i+1][j];
        } else if (c[i-1][j] & 1) {
            if (j > 0) ++c[i][j-1];
            if (j+1 < n) ++c[i][j+1];
            if (i+1 < n) ++c[i+1][j];
            ++t;
        }
    }
    for (short (&r)[N] = c[n-1], j=0; j<n; ++j) if (r[j] & 1) return INF;
    return t;
}

short dfs(short i=0, short t=0) {
    if (n == 1) return 0;
    if (i >= n) {
        memset(c, 0, sizeof(c)); memcpy(c[0], c0, sizeof(c0)); memcpy(c[1], c1, sizeof(c1));
        return t + calc();
    }
    if (a[0][i]) return dfs(i+1, t);
    if (i > 0) ++c0[i-1];
    if (i+1 < n) ++c0[i+1];
    ++c1[i];
    short v = dfs(i+1, t+1);
    if (i > 0) --c0[i-1];
    if (i+1 < n) --c0[i+1];
    --c1[i];
    return min(v, dfs(i+1, t));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> n;
        for (short i=0; i<n; ++i) {
            c0[i] = c1[i] = 0;
            for (short j=0; j<n; ++j) cin >> a[i][j];
        }
        for (short i=0; i<n; ++i) if (a[0][i]) {
            if (i > 0) ++c0[i-1];
            if (i+1 < n) ++c0[i+1];
            ++c1[i];
        }
        short ans = dfs(); if (ans >= INF) ans = -1;
        cout << "Case " << kase << ": " << ans << endl;
    }
    return 0;
}