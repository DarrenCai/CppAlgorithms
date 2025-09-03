/**
 * UVa12074/LA3294
 * Regionals 2005 >> Asia - Dhaka
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
#define T 324*N
struct {int x, y, w, l;} land[N]; int ls[T], rs[T], lc[T], rc[T], v[T], x[N], y[N], z[N], a, b, t, n;

bool cmp(int i, int j) {
    return land[i].w < land[j].w;
}

int query(int o, int l, int r, int y1, int y2) {
    if (l >= y1 && r <= y2) return v[o];
    int s = 0, m = (l+r) >> 1;
    if (y1 <= m && lc[o]) s = max(s, query(lc[o], l, m, y1, y2));
    if (y2 > m && rc[o]) s = max(s, query(rc[o], m+1, r, y1, y2));
    return s;
}

void set(int &o, int l, int r, int y, int w) {
    if (!o) o = t++, lc[o] = rc[o] = v[o] = 0;
    if (l < r) {
        int m = (l+r)>>1;
        if (y <= m) set(lc[o], l, m, y, w), v[o] = max(v[o], v[lc[o]]);
        else set(rc[o], m+1, r, y, w), v[o] = max(v[o], v[rc[o]]);
    } else v[o] = w;
}

void upd(int ch, int &o, int l, int r, int y) {
    if (!o) o = t++, lc[o] = rc[o] = v[o] = 0;
    if (l < r) {
        int m = (l+r)>>1;
        if (y <= m) upd(lc[ch], lc[o], l, m, y), v[o] = max(v[o], v[lc[o]]);
        else upd(rc[ch], rc[o], m+1, r, y), v[o] = max(v[o], v[rc[o]]);
    } else v[o] = max(v[o], v[ch]);
}

int query(int o, int l, int r, int x1, int x2, int y1, int y2) {
    if (l >= x1 && r <= x2) return query(o, 0, b-1, y1, y2);
    int s = 0, m = (l+r)>>1;
    if (x1 <= m && ls[o]) s = max(s, query(ls[o], l, m, x1, x2, y1, y2));
    if (x2 > m && rs[o]) s = max(s, query(rs[o], m+1, r, x1, x2, y1, y2));
    return s;
}

void set(int &o, int l, int r, int x, int y, int w) {
    if (!o) o = t++, ls[o] = rs[o] = lc[o] = rc[o] = v[o] = 0;
    if (l == r) return set(o, 0, b-1, y, w);
    int m = (l+r)>>1;
    if (x <= m) set(ls[o], l, m, x, y, w), upd(ls[o], o, 0, b-1, y);
    else set(rs[o], m+1, r, x, y, w), upd(rs[o], o, 0, b-1, y);
}

int solve() {
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> x[i] >> y[i] >> land[i].w >> land[i].l; z[i] = i;
        land[i].x = x[i] - y[i]; land[i].y = x[i] + y[i]; x[i] = land[i].x; y[i] = land[i].y;
    }
    sort(x, x+n); sort(y, y+n); sort(z, z+n, cmp); a = unique(x, x+n) - x; b = unique(y, y+n) - y;
    int ans = 0; ls[1] = rs[1] = lc[1] = rc[1] = v[1] = 0; t = 2;
    for (int i=0; i<n; ++i) {
        int xi = land[z[i]].x, yi = land[z[i]].y, li = land[z[i]].l,
            x1 = lower_bound(x, x+a, xi-li) - x, x2 = upper_bound(x, x+a, xi+li) - x - 1,
            y1 = lower_bound(y, y+b, yi-li) - y, y2 = upper_bound(y, y+b, yi+li) - y - 1,
            v = query(1, 0, a-1, x1, x2, y1, y2) + 1, s = 1;
        if (i+1 < n) set(s, 0, a-1, lower_bound(x, x+a, xi) - x, lower_bound(y, y+b, yi) - y, v);
        ans = max(ans, v);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case " << k << ": " << solve() << endl;
    return 0;
}