/**
 * UVa1472/LA4980
 * 魔法师的帽子
 * CERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
#define T 32403240
#define M -1ll<<31
long long x[N], y[N], x1[N], x2[N], y1[N], y2[N], c1[N], c2[N]; int s[N], n; bool w[N], f[N];

struct {
    int ls[T], rs[T], lc[T], rc[T], v[T], m, n, t;
    void set(int& o, int l, int r, int y, int w) {
        if (!o) o = ++t, lc[o] = rc[o] = 0;
        v[o] = w;
        if (l == r) return;
        int m = (l+r)>>1;
        m >= y ? set(lc[o], l, m, y, w) : set(rc[o], m+1, r, y, w);
    }
    void upd(int ch, int& o, int l, int r, int y) {
        if (!o) o = ++t, lc[o] = rc[o] = 0;
        v[o] = v[ch];
        if (l == r) return;
        int m = (l+r)>>1;
        m >= y ? upd(lc[ch], lc[o], l, m, y) : upd(rc[ch], rc[o], m+1, r, y);
    }
    void set(int& o, int l, int r, int x, int y, int w) {
        if (!o) o = ++t, ls[o] = rs[o] = lc[o] = rc[o] = 0;
        if (l == r) return set(o, 0, n-1, y, w);
        int m = (l+r)>>1;
        m >= x ? set(ls[o], l, m, x, y, w) : set(rs[o], m+1, r, x, y, w);
        upd(m >= x ? ls[o] : rs[o], o, 0, n-1, y);
    }
    int query(int o, int l, int r, int y) {
        if (l >= y) return v[o];
        int m = (l+r)>>1, s = ::n;
        if (rc[o]) s = query(rc[o], m+1, r, y);
        if (m >= y && lc[o]) s = min(s, query(lc[o], l, m, y));
        return s;
    }
    int query(int o, int l, int r, int x, int y) {
        if (l >= x) return query(o, 0, n-1, y);
        int m = (l+r)>>1, s = ::n;
        if (rs[o]) s = query(rs[o], m+1, r, x, y);
        if (m >= x && ls[o]) s = min(s, query(ls[o], l, m, x, y));
        return s;
    }
} t1, t2;

void solve() {
    cin >> n; t1.t = t2.t = 0; t1.v[0] = t2.v[0] = n;
    for (int i=0; i<n; ++i) {
        char c; cin >> x[i] >> y[i] >> c; w[i] = c == 'W'; f[i] = s[i] = 0;
        x1[i] = y[i]-x[i]; y1[i] = y[i]+x[i]; x2[i] = y[i]-2*x[i]; y2[i] = y[i]+2*x[i];
    }
    sort(x1, x1+n); sort(y1, y1+n); sort(x2, x2+n); sort(y2, y2+n);
    t1.m = unique(x1, x1+n) - x1; t1.n = unique(y1, y1+n) - y1;
    t2.m = unique(x2, x2+n) - x2; t2.n = unique(y2, y2+n) - y2;
    for (int i=1; i<=t1.m; ++i) c1[i] = M;
    for (int i=1; i<=t2.m; ++i) c2[i] = M;
    for (int i=0; i<n; ++i) {
        int k1 = upper_bound(x1, x1+t1.m, y[i]-x[i]) - x1; long long y1 = y[i]+x[i];
        for (int x=k1; x<=t1.m; x += x&-x) if (c1[x] >= y1) {
            f[i] = true; break;
        }
        if (f[i]) continue;
        int k2 = upper_bound(x2, x2+t2.m, y[i]-2*x[i]) - x2; long long y2 = y[i]+2*x[i];
        for (int x=k2; x<=t2.m; x += x&-x) if (c2[x] >= y2) {
            f[i] = true; break;
        }
        if (!f[i]) {
            if (w[i]) while (k1 > 0) c1[k1] = max(c1[k1], y1), k1 -= k1&-k1;
            else while (k2 > 0) c2[k2] = max(c2[k2], y2), k2 -= k2&-k2;
        }
    }
    for (int i=n-1; i>=0; --i) {
        if (f[i]) continue;
        int u = lower_bound(x1, x1+t1.m, y[i]-x[i]) - x1, v = lower_bound(y1, y1+t1.n, y[i]+x[i]) - y1;
        int o = min(t1.t, 1), k = t1.query(o, 0, t1.m-1, u, v);
        if (w[i]) t1.set(o, 0, t1.m-1, u, v, i);
        u = lower_bound(x2, x2+t2.m, y[i]-2*x[i]) - x2; v = lower_bound(y2, y2+t2.n, y[i]+2*x[i]) - y2;
        o = min(t2.t, 1); ++s[min(k, t2.query(o, 0, t2.m-1, u, v))];
        if (!w[i]) t2.set(o, 0, t2.m-1, u, v, i);
    }
    for (int i=0, ans=0; i<n; ++i) f[i] ? cout << "FAIL" << endl : cout << (ans = ans - s[i] + 1) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}