/**
 * UVa10816
 * 沙漠探险
 */

#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

#define M 10020
#define N 105
int g[N][M], c[N], p[N], m, n, s, t; bool f[N]; double d[N];
struct edge {int u, v; double r, d;} e[M];
struct node {
    int u; double d;
    bool operator< (const node &rhs) const {
        return d > rhs.d;
    }
} h;

void path(int u) {
    if (u == s) {
        cout << s;
        return;
    }
    path(p[u]);
    cout << ' ' << u;
}

void solve () {
    cin >> s >> t;
    for (int i=1; i<=n; ++i) f[i] = c[i] = 0, d[i] = 60.;
    for (int i=0, u, v; i<m; ++i)
        cin >> u >> v >> e[i].r >> e[i].d, g[u][c[u]++] = g[v][c[v]++] = i, e[i].u = u, e[i].v = v;
    priority_queue<node> q; q.push({s, d[s] = 0.});
    while (!q.empty()) {
        h = q.top(); q.pop(); int u = h.u; double d0 = h.d;
        if (u == t) break;
        if (f[u]) continue;
        f[u] = true;
        for (int i=0; i<c[u]; ++i) {
            const edge &ee = e[g[u][i]]; int v = ee.u + ee.v - u; double d1 = max(d0, ee.r);
            if (d1 < d[v]) q.push({v, d[v] = d1});
        }
    }
    double ans = d[t];
    for (int i=1; i<=n; ++i) f[i] = c[i] = 0, d[i] = 500000.;
    for (int i=0; i<m; ++i) if (e[i].r <= ans) g[e[i].u][c[e[i].u]++] = g[e[i].v][c[e[i].v]++] = i;
    q = priority_queue<node>(); q.push({s, d[s] = 0.});
    while (!q.empty()) {
        h = q.top(); q.pop(); int u = h.u; double d0 = h.d;
        if (u == t) break;
        if (f[u]) continue;
        f[u] = true;
        for (int i=0; i<c[u]; ++i) {
            const edge &ee = e[g[u][i]]; int v = ee.u + ee.v - u; double d1 = d0 + ee.d;
            if (d1 < d[v]) p[v] = u, q.push({v, d[v] = d1});
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