/**
 * UVa1474/LA4987
 * 疏散计划
 * NEERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 4020
long long d[N][N]; int x[N], y[N], a[N], b[N], f[N], n, m;

bool cmpx(int i, int j) {
    return x[i] < x[j];
}

bool cmpy(int i, int j) {
    return y[i] < y[j];
}

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i], a[i] = i;
    cin >> m;
    for (int i=0; i<m; ++i) cin >> y[i], b[i] = i;
    sort(a, a+n, cmpx);
    sort(b, b+m, cmpy);
    d[n-1][m-1] = abs(x[a[n-1]] - y[b[m-1]]);
    for (int i=n-2; i>=0; --i) for (int j=min(i, m-1), k=max(m+i-n, 0); j>=k; --j) {
        if (j+1 == m) {
            d[i][j] = abs(x[a[i]] - y[b[j]]) + d[i+1][j];
            continue;
        }
        d[i][j] = abs(x[a[i]] - y[b[j]]) + d[i+1][j+1];
        if (n-i > m-j) d[i][j] = min(d[i][j], abs(x[a[i]] - y[b[j]]) + d[i+1][j]);
    }
    for (int i=0, j=0; i<n; ++i) {
        f[a[i]] = b[j] + 1;
        // d[i+1][j]<d[i+1][j+1] 可以换成 d[i+1][j]<=d[i+1][j+1]
        if (j+1==m || (i+1<n && j+1<m && n-i>m-j && d[i+1][j]<d[i+1][j+1])) continue;
        ++j;
    }
    cout << d[0][0] << endl << f[0];
    for (int i=1; i<n; ++i) cout << ' ' << f[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) solve();
    return 0;
}