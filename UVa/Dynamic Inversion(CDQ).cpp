/**
 * UVa11990
 * “动态”逆序对
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 200100
struct {int t, p, v;} e[N]; int a[N], p[N], c[N], f[N], m, n; long long s;

bool cmp(int i, int j) {
    return e[i].t < e[j].t;
}

void solve(int s, int t) {
    if (t - s == 1) return;
    int m = (s+t) / 2, h = m, q = t-1;
    solve(s, m); solve(m, t);
    for (int i=s; i<m; ++i) {
        while (h < t && e[a[h]].p < e[a[i]].p) for (int x=e[a[h++]].v; x; x -= x&-x) ++c[x];
        if (e[a[i]].t < ::m) for (int x=e[a[i]].v+1, j=e[a[i]].t; x<=n; x += x&-x) f[j] += c[x];
    }
    for (int i=m; i<h; ++i) for (int x=e[a[i]].v; x; x -= x&-x) --c[x];
    for (int i=m-1; i>=s; --i) {
        while (q >=m && e[a[q]].p > e[a[i]].p) for (int x=e[a[q--]].v; x<=n; x += x&-x) ++c[x];
        if (e[a[i]].t < ::m) for (int x=e[a[i]].v-1, j=e[a[i]].t; x; x -= x&-x) f[j] += c[x];
    }
    if (s == 0 && t == n) return;
    for (int i=t-1; i>q; --i) for (int x=e[a[i]].v; x<=n; x += x&-x) --c[x];
    for (int i=s; i<t; ++i) p[i] = a[i];
    for (int i=s, j=m, k=s; k<t; ++k) a[k] = i == m || (j < t && e[p[j]].p < e[p[i]].p) ? p[j++] : p[i++];
}

void solve() {
    memset(c, s = 0, sizeof(c));
    for (int i=0; i<n; ++i) {
        cin >> e[i].v; e[i].p = p[e[i].v] = i; e[i].t = m; a[i] = i;
        for (int x = e[i].v+1; x<=n; x += x&-x) s += c[x];
        for (int x = e[i].v; x; x -= x&-x) ++c[x];
    }
    for (int i=0, v; i<m; ++i) cin >> v, f[e[p[v]].t = i] = 0;
    sort(a, a+n, cmp); memset(c, 0, sizeof(c)); solve(0, n);
    for (int i=0; i<m; s -= f[i++]) cout << s << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}