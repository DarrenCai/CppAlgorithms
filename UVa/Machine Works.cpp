/**
 * UVa1106/LA5133
 * 机械工厂
 * World Finals 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
#define T 1<<18
long long p[N], r[N], g[N], f[N], c; int a[N], d[N], x[N], v[T], m, n, t, kase = 0;

bool cmp(int i, int j) {
    return d[i] < d[j];
}

int query(int o, int l, int r, int x) {
    if (v[o] >= 0) return v[o];
    int lc = o<<1, rc = lc|1, m = (l+r)>>1;
    return x <= m ? query(lc, l, m, x) : query(rc, m+1, r, x);
}

void set(int o, int l, int r, int x1, int x2, int i) {
    if (l >= x1 && r <= x2) {
        v[o] = i;
        return;
    }
    int lc = o<<1, rc = lc|1, m = (l+r)>>1;
    if (v[o] >= 0) v[lc] = v[rc] = v[o], v[o] = -1;
    if (x1 <= m) set(lc, l, m, x1, x2, i);
    if (x2 > m) set(rc, m+1, r, x1, x2, i);
}

int search1(int l, int r, int i) {
    while (l < r) {
        int m = (l+1+r)>>1, j = query(1, 0, t, m); long long d = f[i] + g[i]*x[m] - f[j] - g[j]*x[m];
        if (d == 0) return m-1;
        d > 0 ? l = m : r = m-1;
    }
    return l;
}

int search2(int l, int r, int i) {
    while (l < r) {
        int m = (l+r)>>1, j = query(1, 0, t, m); long long d = f[i] + g[i]*x[m] - f[j] - g[j]*x[m];
        if (d == 0) return m+1;
        d > 0 ? r = m : l = m+1;
    }
    return r;
}

void update(int l, int r, int i) {
    if (l > r) return;
    int m = (l+r)>>1, j = query(1, 0, t, m);
    if (f[i] + g[i]*x[m] - f[j] - g[j]*x[m] > 0)
        return set(1, 0, t, search2(l, m, i), search1(m, r, i), i);
    if (g[i] == g[j]) return;
    return g[i] < g[j] ? update(l, m-1, i) : update(m+1, r, i);
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> d[i] >> p[i] >> r[i] >> g[i], x[i-1] = d[i], a[i] = i;
    ++m; v[1] = 0; sort(a, a+n+1, cmp); sort(x, x+n);
    long long ans = f[0] = c; t = unique(x, x+n) - x - 1;
    for (int i=1; i<=n; ++i) {
        int j = a[i], y = lower_bound(x, x+t+1, d[j]) - x, k = query(1, 0, t, y); long long w = f[k] + g[k]*d[j];
        if (w >= p[j]) {
            f[j] = w - p[j] - g[j]*(d[j]+1) + r[j];
            ans = max(ans, f[j] + g[j]*m);
            update(y+1, t, j);
        }
    }
    cout << "Case " << ++kase << ": "  << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    r[0] = g[0] = a[0] = d[0] = 0;
    while (cin >> n >> c >> m && (n || c || m)) solve();
    return 0;
}