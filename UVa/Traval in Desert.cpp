/**
 * UVa10816
 * 沙漠探险
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;

#define M 10020
#define N 105
int g[N][N], c[N], f[N], m, n, s, t; double d[N]; bool vis[N];
struct edge {
    int u, v; double r, d;
    bool operator< (const edge &rhs) const {
        return r < rhs.r;
    }
} e[M];

struct node {
    int u; double d;
    bool operator< (const node &rhs) const {
        return d > rhs.d;
    }
} h;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void path(int u) {
    if (u == s) {
        cout << s;
        return;
    }
    path(f[u]);
    cout << ' ' << u;
}

void solve () {
    cin >> s >> t;
    for (int i=0; i<m; ++i) cin >> e[i].u >> e[i].v >> e[i].r >> e[i].d;
    sort(e, e+m);
    for (int i=1; i<=n; ++i) f[i] = i, c[i] = 0;
    double ans = 0.;
    for (int i=0, cc=0; i<m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        f[u] = v; ans = max(ans, e[i].r);
        if (--cc == 1 || find(s) == find(t)) break;
    }
    for (int i=1; i<=n; ++i) vis[i] = false, d[i] = 500000.;
    priority_queue<node> q; q.push({s, d[s] = 0.});
    for (int i=0; i<m; ++i) {
        if (e[i].r > ans) break;
        g[e[i].u][c[e[i].u]++] = g[e[i].v][c[e[i].v]++] = i;
    }
    while (!q.empty()) {
        h = q.top(); q.pop(); int u = h.u; double d0 = h.d;
        if (u == t) break;
        if (vis[u]) continue;
        vis[u] = true;
        for (int i=0; i<c[u]; ++i) {
            const edge &ee = e[g[u][i]]; int v = ee.u + ee.v - u; double d1 = d0 + ee.d;
            if (d1 < d[v]) f[v] = u, q.push({v, d[v] = d1});
        }
    }
    path(t);
    cout << endl << d[t] << ' ' << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(1);
    while (cin >> n >> m) solve();
}