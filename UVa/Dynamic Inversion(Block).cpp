/**
 * UVa11990
 * “动态”逆序对
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define N 200100
#define M 634
int b[M][M], a[N], p[N], c[N], t[M], m, n, y, z; long long s; bool f[N];

inline int query(int v) {
    int s = 0, h = p[v] / z; f[p[v]] = true;
    for (int i=0; i<h; ++i) s += t[i] - (upper_bound(b[i], b[i]+t[i], v) - b[i]);
    for (int i=h+1; i<y; ++i) s += lower_bound(b[i], b[i]+t[i], v) - b[i];
    for (int i=z*h; i<p[v]; ++i) if (a[i] > v && !f[i]) ++s;
    for (int i=p[v]+1, j=min(z*h+z, n); i<j; ++i) if (a[i] < v && !f[i]) ++s;
    for (int i=lower_bound(b[h], b[h]+t[h], v) - b[h], j=--t[h]; i<j; ++i) b[h][i] = b[h][i+1];
    return s;
}

void solve() {
    memset(c, s = 0, sizeof(c)); z = n/sqrt(m)+1; y = (n + z-1) / z;
    for (int i=0; i<n; ++i) {
        cin >> a[i]; f[p[a[i]] = i] = false; b[i/z][i%z] = a[i];
        for (int x = a[i]+1; x<=n; x += x&-x) s += c[x];
        for (int x = a[i]; x; x -= x&-x) ++c[x];
    }
    for (int i=0; i<y; ++i) t[i] = i+1 < y ? z : n - (y-1)*z, sort(b[i], b[i] + t[i]);
    while (m--) {
        cout << s << endl;
        int v; cin >> v;
        if (m == 0) return;
        s -= query(v);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}