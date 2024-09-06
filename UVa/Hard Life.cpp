/**
 * UVa1389/LA3709
 * 生活的艰辛
 * NEERC 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 2440
#define N 110
struct edge {int u, v; double cap, flow;} e[M];
int g[N][M>>1], q[N], p[N], d[N], cur[N], num[N+1], cnt[N], deg[N], c, m, n, kase = 0; bool vis[N];

void add_edge(int u, int v, double cap, double cc = 0.) {
    e[c] = {u, v, cap, 0}; g[u][cnt[u]++] = c++; e[c] = {v, u, cc, 0}; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<cnt[v]; ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[s];
}

double max_flow(int s, int t, double x) {
    double flow = 0.;
    for (int i=0; i<c; ++i) e[i].flow = 0.;
    for (int i=0; i<cnt[t]; ++i) {
        edge &ee = e[g[t][i]^1];
        ee.cap = 2.*x + m - deg[ee.u];
    }
    for (int i=0; i<=t; ++i) d[i] = t+1;
    if (!bfs(s, t)) return 0.;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    for (int u=s; d[s] <= t;) {
        if (u == t) {
            double a = 1e30;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
        }
        bool ok = false;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = true; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                break;
            }
        }
        if (!ok) {
            int m = t;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    return flow;
}

void solve() {
    if (kase++) cout << endl;
    int s = 0, t = n+1, cc = 0; memset(cnt, c = 0, sizeof(cnt)); memset(deg, 0, sizeof(deg));
    for (int i=0; i<m; ++i) {
        int u, v; cin >> u >> v; ++deg[u]; ++deg[v]; add_edge(u, v, 1, 1);
    }
    for (int i=1; i<=n; ++i) add_edge(s, i, m), add_edge(i, t, m);
    double l = 0., r = m, eps = 1./n/n, f = m*n;
    while (l+eps < r) {
        double x = .5*(l+r);
        max_flow(s, t, x) < f ? l = x : r = x;
    }
    max_flow(s, t, l);
    bfs(s, t);
    for (int i=1; i<=n; ++i) if (!vis[i]) ++cc;
    cout << cc << endl;
    for (int i=1; i<=n; ++i) if (!vis[i]) {
        cout << i << endl;
        if (--cc == 0) return;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) solve();
    return 0;
}