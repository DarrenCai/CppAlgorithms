/**
 * UVa1366/LA3530
 * 火星采矿
 * CERC 2005
 */

#include <iostream>
using namespace std;

#define N 510
int a[N][N], b[N][N], d[N][N], m, n;

int solve() {
    for (int i=1; i<=n; ++i) {
        a[i][0] = 0;
        for (int j=1; j<=m; ++j) cin >> a[i][j], a[i][j] += a[i][j-1];
    }
    for (int i=1; i<=n; ++i) {
        d[0][i] = 0;
        for (int j=1; j<=m; ++j) cin >> b[i][j];
    }
    for (int i=1; i<=m; ++i) {
        int s = d[i][0] = 0;
        for (int j=1; j<=n; ++j) {
            s += b[j][i];
            d[i][j] = max(s + d[i-1][j], d[i][j-1] + a[j][i]);
        }
    }
    return d[m][n];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>m && n) cout << solve() << endl;
    return 0;
}