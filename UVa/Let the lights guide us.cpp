/**
 * UVa1490/LA5106
 * 修建魔法灯塔
 * Fuzhou 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define INF 20000000
#define M 5020
#define N 102
int t[N][M], f[N][M], d[2][M], c[M], v[M], m, n;

void solve() {
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> t[i][j];
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> f[i][j];
    for (int i=0; i<m; ++i) d[0][i] = t[0][i];
    for (int i=1; i<n; ++i) {
        for (int j=i-1, k=0; k<m; ++k) v[k] = f[j][k] + k, d[i&1][k] = INF;
        sort(v, v+m);
        int k = unique(v, v+m) - v;
        for (int j=1; j<=k; ++j) c[j] = INF;
        for (int j=0; j<m; ++j) {
            for (int x = upper_bound(v, v+k, f[i-1][j]+j) - v; x > 0; x -= x&-x) c[x] = min(c[x], d[~i&1][j]);
            for (int x = lower_bound(v, v+k, j-f[i][j]) - v + 1; x <= k; x += x&-x)
                d[i&1][j] = min(d[i&1][j], c[x] + t[i][j]);
        }
        for (int j=i-1, k=0; k<m; ++k) v[k] = f[j][k] - k;
        sort(v, v+m);
        k = unique(v, v+m) - v;
        for (int j=1; j<=k; ++j) c[j] = INF;
        for (int j=m-1; j>=0; --j) {
            for (int x = lower_bound(v, v+k, -j-f[i][j]) - v + 1; x <= k; x += x&-x)
                d[i&1][j] = min(d[i&1][j], c[x] + t[i][j]);
            for (int x = upper_bound(v, v+k, f[i-1][j]-j) - v; x > 0; x -= x&-x) c[x] = min(c[x], d[~i&1][j]);
        }
    }
    int ans = d[~n&1][0];
    for (int i=1; i<m; ++i) ans = min(ans, d[~n&1][i]);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) solve();
    return 0;
}