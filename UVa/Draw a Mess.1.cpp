/**
 * UVa1493/LA5698
 * Dalian 2011
 * 用并查集做更好
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 50050
int f[202][N], g[N], x[N], y[N], r[N], w[N], c[N], l[N], a[10], m, n, q; char s[10];

int find(int (&f)[N], int x) {
    return x == f[x] ? x : f[x] = find(f, f[x]);
}

void solve() {
    for (int i=1; i<10; ++i) a[i] = 0;
    for (int i=0; i<q; ++i) {
        cin >> s >> x[i] >> y[i]; g[i] = s[0];
        s[0] == 'R' ? cin >> l[i] >> w[i] >> c[i] : (s[0] == 'T' ? cin >> w[i] >> c[i] : cin >> r[i] >> c[i]);
    }
    for (int i=0; i<n; ++i) for (int j=0; j<=m; ++j) f[i][j] = j;
    while (q--) {
        if (g[q] == 'C') {
            for (int i=max(x[q]-r[q], 0), j=min(x[q]+r[q], n-1); i<=j; ++i) {
                int h = sqrt(r[q]*r[q] - (i-x[q])*(i-x[q]) + .5), b = find(f[i], max(y[q]-h, 0)), t = min(y[q]+h, m-1);
                while (b <= t) ++ a[c[q]], b = f[i][b] = find(f[i], b+1);
            }
        } else if (g[q] == 'D') {
            for (int i=max(x[q]-r[q], 0), j=min(x[q]+r[q], n-1); i<=j; ++i) {
                int b = find(f[i], max(y[q]-r[q]+abs(i-x[q]), 0)), t = min(y[q]+r[q]-abs(i-x[q]), m-1);
                while (b <= t) ++ a[c[q]], b = f[i][b] = find(f[i], b+1);
            }
        } else if (g[q] == 'R') {
            for (int i=x[q], j=min(x[q]+l[q], n); i<j; ++i) {
                int b = find(f[i], y[q]), t = min(y[q]+w[q], m)-1;
                while (b <= t) ++ a[c[q]], b = f[i][b] = find(f[i], b+1);
            }
        } else {
            for (int i=x[q], h=(w[q]-1)>>1, j=min(x[q]+h, n-1); i<=j; ++i) {
                int b = find(f[i], max(y[q]-h+i-x[q], 0)), t = min(y[q]+h-i+x[q], m-1);
                while (b <= t) ++ a[c[q]], b = f[i][b] = find(f[i], b+1);
            }
        }
    }
    cout << a[1]; for (int i=2; i<10; ++i) cout << ' ' << a[i]; cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m >> q) solve();
    return 0;
}