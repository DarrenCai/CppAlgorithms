/**
 * UVa12389/LA5821
 * SWERC 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define Q 50010
#define M 150020
int a[M], x[M], y[M], z[M], c1[M], c2[M], d[Q], n, q, t, kase = 0, INF = 0x7f7f7f7f;

bool cmp(int i, int j) {
    return x[i] < x[j];
}

void update(int x, int type, int v) {
    if (type) while (x > 0) c1[x] = max(c1[x], v), x -= x&-x;
    else while (x <= t) c2[x] = max(c2[x], v), x += x&-x;
}

void query(int x, int type, int v, int& r) {
    int s = -INF;
    if (type) while (x <= t) s = max(s, c1[x]), x += x&-x;
    else while (x > 0) s = max(s, c2[x]), x -= x&-x;
    if (s > -INF) r = min(r, v-s);
}

void solve() {
    if (kase++) cout << endl;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], z[i] = y[i], a[i] = i;
    cin >> q; q += n;
    for (int i=n; i<q; ++i) cin >> x[i] >> y[i], z[i] = y[i], a[i] = i, d[i-n] = INF;
    sort(a, a+q, cmp); sort(z, z+q); t = unique(z, z+q) - z;
    for (int i=1; i<=t; ++i) c1[i] = c2[i] = -INF;
    for (int i=0; i<q; ++i) {
        int p = upper_bound(z, z+t, y[a[i]]) - z;
        if (a[i] < n) update(p, 0, x[a[i]]+y[a[i]]), update(p, 1, x[a[i]]-y[a[i]]);
        else query(p, 0, x[a[i]]+y[a[i]], d[a[i]-n]), query(p, 1, x[a[i]]-y[a[i]], d[a[i]-n]);
    }
    for (int i=1; i<=t; ++i) c1[i] = c2[i] = -INF;
    for (int i=q-1; i>=0; --i) {
        int p = upper_bound(z, z+t, y[a[i]]) - z;
        if (a[i] < n) update(p, 0, y[a[i]]-x[a[i]]), update(p, 1, -x[a[i]]-y[a[i]]);
        else query(p, 0, y[a[i]]-x[a[i]], d[a[i]-n]), query(p, 1, -x[a[i]]-y[a[i]], d[a[i]-n]);
    }
    for (int i=0, j=q-n; i<j; ++i) cout << d[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n != -1) solve();
    return 0;
}