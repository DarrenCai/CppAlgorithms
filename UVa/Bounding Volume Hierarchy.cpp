/**
 * UVa12312
 * 层次包围盒
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 40040
#define T 80080
int ls[T<<1], rs[T<<1], a[T], b[T], c[T], d[T], p, t, q, s;
double xa[T<<1], ya[T<<1], za[T<<1], xb[T<<1], yb[T<<1], zb[T<<1], x[N], y[N], z[N], *ptr, sx, sy, sz, tx, ty, tz;
struct ret {int i; double d;};

bool cmp(int i, int j) {
    return min(min(ptr[a[i]], ptr[b[i]]), ptr[c[i]]) < min(min(ptr[a[j]], ptr[b[j]]), ptr[c[j]]);
}

void build(int& o, int l, int r) {
    if (!o) o = ++s, ls[o] = rs[o] = 0;
    xa[o] = xb[o] = x[a[d[l]]]; ya[o] = yb[o] = y[a[d[l]]]; za[o] = zb[o] = z[a[d[l]]];
    for (int i=l; i<r; ++i) {
        xa[o] = min(min(x[a[d[i]]], x[b[d[i]]]), min(x[c[d[i]]], xa[o]));
        ya[o] = min(min(y[a[d[i]]], y[b[d[i]]]), min(y[c[d[i]]], ya[o]));
        za[o] = min(min(z[a[d[i]]], z[b[d[i]]]), min(z[c[d[i]]], za[o]));
        xb[o] = max(max(x[a[d[i]]], x[b[d[i]]]), max(x[c[d[i]]], xb[o]));
        yb[o] = max(max(y[a[d[i]]], y[b[d[i]]]), max(y[c[d[i]]], yb[o]));
        zb[o] = max(max(z[a[d[i]]], z[b[d[i]]]), max(z[c[d[i]]], zb[o]));
    }
    if (l+1 == r) return;
    ptr = xb[o]-xa[o] > yb[o]-ya[o] ? (xb[o]-xa[o] > zb[o]-za[o] ? x : z) : (yb[o]-ya[o] > zb[o]-za[o] ? y : z);
    int m = (l+r)>>1; sort(d+l, d+r, cmp); build(ls[o], l, m); build(rs[o], m, r);
}

bool checkx(int o, double x) {
    double d1 = x - sx, d2 = tx;
    if (d1 * d2 <= 0.) return false;
    if (d1 < 0.) d1 = -d1, d2 = -d2;
    double y = d1 * ty, z = d1 * tz;
    return d2 * (ya[o] - sy) <= y && y <= d2 * (yb[o] - sy) && d2 * (za[o] - sz) <= z && z <= d2 * (zb[o] - sz);
}

bool checky(int o, double y) {
    double d1 = y - sy, d2 = ty;
    if (d1 * d2 <= 0.) return false;
    if (d1 < 0.) d1 = -d1, d2 = -d2;
    double x = d1 * tx, z = d1 * tz;
    return d2 * (xa[o] - sx) <= x && x <= d2 * (xb[o] - sx) && d2 * (za[o] - sz) <= z && z <= d2 * (zb[o] - sz);
}

bool checkz(int o, double z) {
    double d1 = z - sz, d2 = tz;
    if (d1 * d2 <= 0.) return false;
    if (d1 < 0.) d1 = -d1, d2 = -d2;
    double x = d1 * tx, y = d1 * ty;
    return d2 * (xa[o] - sx) <= x && x <= d2 * (xb[o] - sx) && d2 * (ya[o] - sy) <= y && y <= d2 * (yb[o] - sy);
}

bool check(int o) {
    if (sx >= xa[o] && sx <= xb[o] && sy >= ya[o] && sy <= yb[o] && sz >= za[o] && sz <= zb[o]) return true;
    return (sx < xa[o] && checkx(o, xa[o])) || (sx > xb[o] && checkx(o, xb[o]))
        || (sy < ya[o] && checky(o, ya[o])) || (sy > yb[o] && checky(o, yb[o]))
        || (sz < za[o] && checkz(o, za[o])) || (sz > zb[o] && checkz(o, zb[o]));
}

int sign(double x) {
    return x > 0. ? 1 : (x < 0. ? -1 : 0);
}

double intersect(int a, int b, int c) {
    double x1 = x[b] - x[a], y1 = y[b] - y[a], z1 = z[b] - z[a], x2 = x[c] - x[a], y2 = y[c] - y[a], z2 = z[c] - z[a],
        nx = y1*z2 - z1*y2, ny = z1*x2 - x1*z2, nz = x1*y2 - y1*x2, vx = x[a] - sx, vy = y[a] - sy, vz = z[a] - sz;
    double d1 = nx*tx + ny*ty + nz*tz, d2 = nx*vx + ny*vy + nz*vz;
    if (abs(d1) < 1e-12 || (d1 > 0. && d2 < 0.) || (d1 < 0. && d2 > 0.)) return -1.0;
    double y3 = d2*ty - d1*vy, z3 = d2*tz - d1*vz;
    int as = sign(y1*z3 - z1*y3), bs, cs;
    y3 = d2*ty + d1*(sy-y[b]); z3 = d2*tz + d1*(sz-z[b]); bs = sign((y[c]-y[b])*z3 - (z[c]-z[b])*y3);
    y3 = d2*ty + d1*(sy-y[c]); z3 = d2*tz + d1*(sz-z[c]); cs = sign(-y2*z3 + z2*y3);
    return as*bs >= 0 && as*cs >= 0 && bs*cs >= 0 ? d2 / d1 : -1.;
}

ret query(int o, int l, int r) {
    if (!check(o)) return {-1, -1.};
    if (l+1 == r) {
        int i = d[l]; double s = intersect(a[i], b[i], c[i]);
        return {s < 0. ? -1 : i, s};
    }
    int m = (l+r)>> 1;
    ret s = query(ls[o], l, m), t = query(rs[o], m, r);
    return s.i < 0 || (t.i >= 0 && t.d < s.d) ? t : s;
}

void query() {
    cin >> sx >> sy >> sz >> tx >> ty >> tz; tx -= sx; ty -= sy; tz -= sz;
    ret r = query(1, 0, t);
    cout << r.i;
    if (r.i >= 0) cout << ' ' << r.d*tx + sx << ' ' << r.d*ty + sy << ' ' << r.d*tz + sz;
    cout << endl;
}

void solve() {
    for (int i=0; i<p; ++i) cin >> x[i] >> y[i] >> z[i];
    cin >> t;
    for (int i=0; i<t; ++i) cin >> a[i] >> b[i] >> c[i], d[i] = i;
    int k = s = 0; build(k, 0, t);
    cin >> q;
    while (q--) query();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    while (cin >> p && p) solve();
    return 0;
}