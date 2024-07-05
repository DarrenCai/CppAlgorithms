/**
 * UVa1504/LA5834
 * Fuzhou 2011
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 3002
struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w < rhs.w;
    }
} e[N*N>>1];
int c[N][N], f[N], s[N], m, n; bool use[N*N>>1];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

double solve () {
    for (int i=0, u, v, w; i<m; ++i) cin >> e[i].u >> e[i].v >> e[i].w, use[i] = false;
    sort(e, e+m);
    for (int i=0; i<n; ++i) f[i] = i;
    int cc = 0;
    for (int i=0, k=1; i<m; ++i) {
        int x = find(e[i].u), y = find(e[i].v);
        c[e[i].u][e[i].v] = c[e[i].v][e[i].u] = i;
        if (x == y) continue;
        f[x] = y; use[i] = true; cc += e[i].w; s[k++] = i;
    }
    double ans = 0.; int q; cin >> q;
    for (int i=0; i<q; ++i) {
        int u, v, w, j; cin >> u >> v >> w;
        if (use[j = c[u][v]]) {
            for (int k=0; k<n; ++k) f[k] = k;
            for (int k=1; k<n; ++k) if (s[k] != j) f[find(e[s[k]].u)] = find(e[s[k]].v);
            int c1 = cc - e[j].w + w;
            for (int k = lower_bound(e, e+m, e[j]) - e; k < m && e[k].w < w; ++k)
            if (k != j && find(e[k].u) != find(e[k].v)) {
                c1 = cc - e[j].w + e[k].w; break;
            }
            ans += c1;
        } else ans += cc;
    }
    return ans / q;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(4);
    while (cin >> n >> m && n) cout << solve() << endl;
    return 0;
}