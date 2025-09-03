/**
 * P3810 【模板】三维偏序（陌上花开）
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 100010
struct {int a, b, c;} p[N]; int a[N], b[N], c[N<<1], d[N], f[N], v[N], n, k, t;

bool cmp(int i, int j) {
    return p[i].a < p[j].a || (p[i].a == p[j].a && p[i].b < p[j].b)
        || (p[i].a == p[j].a && p[i].b == p[j].b && p[i].c < p[j].c);
}

bool eq(int i, int j) {
    return p[i].a == p[j].a && p[i].b == p[j].b && p[i].c == p[j].c;
}

void solve(int s, int e) {
    if (e - s == 1) return;
    int m = (s+e) / 2, h = s;
    solve(s, m); solve(m, e);
    for (int i=m; i<e; ++i) {
        while (h < m && p[b[h]].b <= p[b[i]].b) for (int x = p[b[h]].c, y = v[b[h++]]; x <= k; x += x&-x) c[x] += y;
        for (int x = p[b[i]].c; x; x -= x&-x) f[b[i]] += c[x];
    }
    if (s == 0 && e == t) return;
    for (int i=s; i<h; ++i) for (int x = p[b[i]].c; x <= k; x += x&-x) c[x] -= v[b[i]];
    for (int i=s; i<e; ++i) d[i] = b[i];
    for (int i=s, j=m, k=s; k<e; ++k) b[k] = i == m || (j < e && p[d[j]].b < p[d[i]].b) ? d[j++] : d[i++];
}

void solve() {
    cin >> n >> k;
    for (int i=0; i<n; ++i) cin >> p[i].a >> p[i].b >> p[i].c, a[i] = i, f[i] = 0;
    sort(a, a+n, cmp); memset(c, 0, sizeof(c));
    for (int i=t=0; i<n; ++i) i && eq(a[i], a[i-1]) ? ++v[b[t-1]] : v[b[t++] = a[i]] = 1;
    solve(0, t); memset(a, 0, sizeof(a));
    for (int i=0; i<t; ++i) a[f[b[i]] + v[b[i]]-1] += v[b[i]];
    for (int i=0; i<n; ++i) cout << a[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}