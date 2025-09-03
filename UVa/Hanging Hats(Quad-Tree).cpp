/**
 * UVa1472/LA4980
 * 魔法师的帽子
 * CERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
long long x[N], y[N], *px, *py; int a[N], rm[N], n, c; bool w[N];

bool cmpx(int i, int j) {
    return px[i] < px[j];
}

bool cmpy(int i, int j) {
    return py[i] < py[j];
}

struct {
    long long x[N], y[N]; int l1[N], l2[N], r1[N], r2[N], f[N], s[N], v[N], p[N], q[N], t;
    void build(int& o, int l, int r) {
        if (!o) o = ++t, l1[o] = l2[o] = r1[o] = r2[o] = f[o] = s[o] = v[o] = 0;
        if (l+1 < r) {
            sort(a+l, a+r, cmpx);
            int m = lower_bound(a+l, a+r, a[(l+r)>>1], cmpx) - a;
            sort(a+l, a+m, cmpy);
            int c = lower_bound(a+l, a+m, a[m], cmpy) - a;
            if (l < c) build(l1[o], l, c);
            if (c < m) build(l2[o], c, m);
            if (m+1 < r) {
                sort(a+m+1, a+r, cmpy);
                c = lower_bound(a+m+1, a+r, a[m], cmpy) - a;
                if (m+1 < c) build(r1[o], m+1, c);
                if (c < r) build(r2[o], c, r);
            }
            p[q[a[m]] = o] = a[m]; f[l1[o]] = f[l2[o]] = f[r1[o]] = f[r2[o]] = o;
        } else p[q[a[l]] = o] = a[l];
    }
    void build() {
        l1[0] = l2[0] = r1[0] = r2[0] = s[0] = v[0] = t = c = 0; px = x; py = y; build(c, 0, n);
    }
    bool query(int o, int i) {
        if (s[o] == 0) return false;
        if (x[i] <= x[p[o]]) {
            if (y[i] > y[p[o]]) return query(r2[o], i) || query(l2[o], i);
            return s[o] - s[l1[o]] - s[l2[o]] - s[r1[o]] > 0 || query(r1[o], i) || query(l2[o], i) || query(l1[o], i);
        } else if (y[i] > y[p[o]]) return query(r2[o], i);
        return query(r2[o], i) || query(r1[o], i);
    }
    void rem(int o) {
        if (v[o] - v[l1[o]] - v[l2[o]] - v[r1[o]] - v[r2[o]] > 0) rm[c++] = p[o];
        if (v[l1[o]] > 0) rem(l1[o]);
        if (v[l2[o]] > 0) rem(l2[o]);
        if (v[r1[o]] > 0) rem(r1[o]);
        if (v[r2[o]] > 0) rem(r2[o]);
    }
    void qrm(int o, int i) {
        if (v[o] == 0) return;
        if (x[i] >= x[p[o]]) {
            if (y[i] >= y[p[o]]) {
                if (v[o] - v[l1[o]] - v[l2[o]] - v[r1[o]] - v[r2[o]] > 0) rm[c++] = p[o];
                rem(l1[o]); qrm(l2[o], i); qrm(r1[o], i); qrm(r2[o], i);
            } else qrm(l1[o], i), qrm(r1[o], i);
        } else if (y[i] >= y[p[o]]) qrm(l1[o], i), qrm(l2[o], i);
        else qrm(l1[o], i);
    }
    void add(int i, int d) {
        if (d) c = 0, qrm(1, i);
        for (int o = q[i]; o; o = f[o]) ++v[o], s[o] += d;
    }
    void remove(int i) {
        for (int o = q[i]; o; o = f[o]) --v[o];
    }
} t1, t2;

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) {
        char c; cin >> x[i] >> y[i] >> c; w[i] = c == 'W'; a[i] = i;
        t1.x[i] = y[i]-x[i]; t1.y[i] = y[i]+x[i]; t2.x[i] = y[i]-2*x[i]; t2.y[i] = y[i]+2*x[i];
    }
    t1.build(); t2.build();
    for (int i=0; i<n; ++i)
        if (t1.query(1, i) || t2.query(1, i)) {
            cout << "FAIL" << endl;
        } else {
            t1.add(i, w[i]); t2.add(i, !w[i]);
            while (c--) t1.remove(rm[c]), t2.remove(rm[c]);
            cout << t1.v[1] << endl;
        }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}