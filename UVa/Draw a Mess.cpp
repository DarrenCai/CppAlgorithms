/**
 * UVa1493/LA5698
 * Dalian 2011
 * 利用线段树求解
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 50050
int e[1<<17], g[N], x[N], y[N], r[N], w[N], c[N], l[N], a[10], m, n, q, b, t, cc; char s[10];

void set(int o, int l, int r) {
    if (l >= b && r <= t) {
        e[o] = cc; return;
    }
    int m = (l+r) >> 1, lc = o << 1, rc = lc + 1;
    if (e[o] >= 0) e[lc] = e[rc] = e[o], e[o] = -1;
    if (b <= m) set(lc, l, m);
    if (t > m) set(rc, m+1, r);
}

void query(int o, int l, int r) {
    if (e[o] >= 0) {
        a[e[o]] += min(r, t) - max(l ,b) + 1;
        return;
    }
    int m = (l+r) >> 1, lc = o << 1, rc = lc + 1;
    if (b <= m) query(lc, l, m);
    if (t > m) query(rc, m+1, r);
}

void solve() {
    for (int i=1; i<10; ++i) a[i] = 0;
    for (int i=0; i<q; ++i) {
        cin >> s >> x[i] >> y[i]; g[i] = s[0];
        s[0] == 'R' ? cin >> l[i] >> w[i] >> c[i] : (s[0] == 'T' ? cin >> w[i] >> c[i] : cin >> r[i] >> c[i]);
    }
    for (int i=0; i<n; ++i) {
        e[1] = 0;
        for (int j=0; j<q; ++j) {
            if (g[j] == 'C') {
                if (i < x[j]-r[j] || i > x[j]+r[j]) continue;
                int h = sqrt(r[j]*r[j] - (i-x[j])*(i-x[j]) + .5);
                b = max(y[j]-h, 0); t = min(y[j]+h, m-1);
            } else if (g[j] == 'D') {
                if (i < x[j]-r[j] || i > x[j]+r[j]) continue;
                b = max(y[j]-r[j]+abs(i-x[j]), 0); t = min(y[j]+r[j]-abs(i-x[j]), m-1);
            } else if (g[j] == 'R') {
                if (i < x[j] || i >= x[j]+l[j]) continue;
                b =  y[j]; t = min(y[j]+w[j], m)-1;
            } else {
                int h = (w[j]-1) >> 1;
                if (i < x[j] || i > x[j]+h) continue;
                b = max(y[j]-h+i-x[j], 0); t = min(y[j]+h-i+x[j], m-1);
            }
            cc = c[j]; set(1, 0, m-1);
        }
        b = 0; t = m-1; query(1, 0, m-1);
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