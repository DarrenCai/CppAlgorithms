/**
 * UVa1492/LA5694
 * Dalian 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
struct node {
    int l, r, v; long long h;
    node (int l=0, int r=0, int v=0, long long h=0): l(l), r(r), h(h), v(v) {}
    bool operator< (const node& rhs) const {
        return h < rhs.h;
    }
} s[N];
int a[1<<18], c[1<<18], x[N], x1[N>>1], x2[N>>1], y1[N>>1], y2[N>>1], m, n, t; long long ans, w, h;

void build(int o, int l, int r) {
    a[o] = c[o] = 0;
    if (l == r) return;
    int m = (l+r)>>1, lc = o<<1, rc = lc|1;
    build(lc, l, m); build(rc, m+1, r);
}

void update(int o, int l, int r) {
    if (a[o]) c[o] = x[r+1] - x[l];
    else if (l == r) c[o] = 0;
    else c[o] = c[o<<1] + c[o<<1|1];
}

void add(int o, int l, int r, int y, int z, int v) {
    if (x[l] >= y && x[r+1] <= z) a[o] += v;
    else {
        int m = (l+r)>>1, lc = o<<1, rc = lc|1;
        if (y < x[m+1]) add(lc, l, m, y, z, v);
        if (z > x[m+1]) add(rc, m+1, r, y, z, v);
    }
    update(o, l, r);
}

void calc() {
    sort(s, s+t); sort(x, x+t);
    int k = unique(x, x+t) - x - 2;
    build(1, 0, k);
    for (int i=0, j=t-1; i<j; ++i) {
        add(1, 0, k, s[i].l, s[i].r, s[i].v);
        ans -= c[1] * (s[i+1].h - s[i].h);
    }
}

void solve() {
    ans = 0; t = n << 1;
    for (int i=0; i<n; ++i) cin >> x1[i] >> y1[i] >> x2[i] >> y2[i], --x1[i], --y1[i];
    if (w >= m) {
        ans = (w-m+1)*h;
        if (t) {
            for (int i=0, y = w-m+1; i<n; ++i) {
                x[i] = max(x1[i]-m+1, 0); x[i+n] = min(x2[i], y);
                s[i] = node(x[i], x[i+n], 1, y1[i]); s[i+n] = node(x[i], x[i+n], -1, y2[i]);
            }
            calc();
        }
    }
    if (h >= m && m > 1) {
        ans += (h-m+1)*w;
        if (t) {
            for (int i=0, y = h-m+1; i<n; ++i) {
                x[i] = max(y1[i]-m+1, 0); x[i+n] = min(y2[i], y);
                s[i] = node(x[i], x[i+n], 1, x1[i]); s[i+n] = node(x[i], x[i+n], -1, x2[i]);
            }
            calc();
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> w >> h >> n >> m) solve();
    return 0;
}