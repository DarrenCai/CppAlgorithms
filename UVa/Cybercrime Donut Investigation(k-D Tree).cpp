/**
 * UVa12389/LA5821
 * SWERC 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
#define T 150100
int a[N], x[T], y[T], lc[N], rc[N], p[N], x1[N], x2[N], y1[N], y2[N], n, q, t, kase = 0;

bool cmpx(int i, int j) {
    return x[i] < x[j] || (x[i] == x[j] && y[i] < y[j]);
}

bool cmpy(int i, int j) {
    return y[i] < y[j] || (y[i] == y[j] && x[i] < x[j]);
}

void update(int o, int ch) {
    x1[o] = min(x1[o], x1[ch]); x2[o] = max(x2[o], x2[ch]); y1[o] = min(y1[o], y1[ch]); y2[o] = max(y2[o], y2[ch]);
}

void build(int& o, int l, int r, int d = 0) {
    o = ++t; lc[o] = rc[o] = 0;
    if (l+1 < r) {
        int m = (l+r)>>1; nth_element(a+l, a+m, a+r, d&1 ? cmpy : cmpx);
        p[o] = a[m]; x1[o] = x2[o] = x[a[m]]; y1[o] = y2[o] = y[a[m]];
        build(lc[o], l, m, d^1); update(o, lc[o]);
        if (m+1 < r) build(rc[o], m+1, r, d^1), update(o, rc[o]);
    } else p[o] = a[l], x1[o] = x2[o] = x[a[l]], y1[o] = y2[o] = y[a[l]];
}

int check(int x1, int x2, int y1, int y2, int xi, int yi) {
    if (xi < x1) return yi < y1 ? max(x1-xi, y1-yi) : (yi > y2 ? max(x1-xi, yi-y2) : x1-xi);
    if (xi > x2) return yi < y1 ? max(xi-x2, y1-yi) : (yi > y2 ? max(xi-x2, yi-y2) : xi-x2);
    return yi < y1 ? y1-yi : (yi > y2 ? yi-y2 : 0);
}

int query(int o, int i, int d = 0) {
    int ans = max(abs(x[p[o]]-x[i]), abs(y[p[o]]-y[i]));
    if (ans == 0) return ans;
    bool f = d&1 ? cmpy(i, p[o]) : cmpx(i, p[o]); int c1 = f ? lc[o] : rc[o], c2 = f ? rc[o] : lc[o];
    if (c1 && check(x1[c1], x2[c1], y1[c1], y2[c1], x[i], y[i]) < ans) ans = min(ans, query(c1, i, d^1));
    if (c2 && check(x1[c2], x2[c2], y1[c2], y2[c2], x[i], y[i]) < ans) ans = min(ans, query(c2, i, d^1));
    return ans;
}

void query(int i) {
    cin >> x[i] >> y[i]; t = x[i]+y[i]; x[i] -= y[i]; y[i] = t;
    cout << query(1, i) << endl;
}

void solve() {
    if (kase++) cout << endl;
    for (int i=1; i<=n; ++i) cin >> x[i] >> y[i], t = x[i]+y[i], x[i] -= y[i], y[i] = t, a[i] = i;
    int s = t = 0; build(s, 1, n+1);
    cin >> q;
    for (int i=1; i<=q; ++i) query(n+i);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n != -1) solve();
    return 0;
}