/**
 * UVa1025
 * 城市里的间谍
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 52
int n, m1, m2, T, t[N], d[N][N], e[N][N], f[N][N];

int calc(int i, int j) {
    if (f[i][j] > -1) return f[i][j];
    if (i > 1) f[i][j] = calc(i-1, j) + t[i-1];
    for (int ii=n; ii>i; --ii) for (int jj=1; jj<j; ++jj) {
        int k = lower_bound(e[ii]+1, e[ii]+1+m2, d[ii][jj]) - e[ii];
        if (k <= m2 && e[i][k] <= d[i][j]) {
            f[i][j] = max(f[i][j], calc(ii, jj) + e[i][k] - e[ii][k]);
        }
    }
    return f[i][j] = max(f[i][j], 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k = 0;
    while (cin >> n && n) {
        cin >> T;
        for (int i=1; i<n; ++i) cin >> t[i];
        cin >> m1;
        for (int i=1; i<=m1; ++i) cin >> d[1][i];
        cin >> m2;
        for (int i=1; i<=m2; ++i) cin >> e[n][i];
        for (int i=1; i<n; ++i) for (int j=1; j<=m1; ++j) d[i+1][j] = d[i][j] + t[i];
        for (int i=n-1; i>=1; --i) for (int j=1; j<=m2; ++j) e[i][j] = e[i+1][j] + t[i];
        cout << "Case Number " << ++k << ": ";
        while (d[n][m1] > T) --m1;
        if (m1 == 0) {
            cout << "impossible" << endl;
        } else {
            memset(f, -1, sizeof(f));
            for (int i=1; i<=n; ++i) f[i][1] = d[i][1] - d[1][1];
            cout << T - calc(n, m1) << endl;
        }
    }
    return 0;
}