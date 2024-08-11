/**
 * poj2396
 * http://poj.org/problem?id=2396
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define M 201
#define N 21
#define T 222
struct edge {int u, v, cap, flow;} e[M*N<<1];
int g[T][M], l[M][N], u[M][N], q[T], p[T], d[T], cur[T], num[T], cnt[T], x[M], y[N], c, m, n; bool vis[T];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
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

bool upd(char s, int v, int r, int c) {
    if (s == '=') {
        if (l[r][c] > v || u[r][c] < v) return false;
        l[r][c] = u[r][c] = v;
    } else if (s == '>') {
        if (u[r][c] < ++v) return false;
        l[r][c] = max(l[r][c], v);
    } else {
        if (l[r][c] > --v) return false;
        u[r][c] = min(u[r][c], v);
    }
    return true;
}

bool check_lu() {
    int k; bool ok = true; cin >> k;
    while (k--) {
        int r, c, v; char s; cin >> r >> c >> s >> v;
        if (r) {
            if (c) {
                if (!upd(s, v, r, c)) ok = false;
            } else for (c=1; c<=n; ++c) if (!upd(s, v, r, c)) {
                ok = false; break;
            }
        } else if (c) {
            for (r=1; r<=m; ++r) if (!upd(s, v, r, c)) {
                ok = false; break;
            }
        } else for (r=1; r<=m; ++r) for (c=1; c<=n; ++c) if (!upd(s, v, r, c)) {
            ok = false; break;
        }
    }
    for (int r=1; r<=m; ++r) for (int c=1; c<=n; ++c) {
        if ((x[r] -= l[r][c]) < 0) return false;
        if ((y[c] -= l[r][c]) < 0) return false;
        u[r][c] -= l[r][c];
    }
    return ok;
}

void solve() {
    cin >> m >> n; memset(l, 0, sizeof(l)); memset(u, 127, sizeof(u));
    for (int i=1; i<=m; ++i) cin >> x[i];
    for (int i=1; i<=n; ++i) cin >> y[i];
    if (!check_lu()) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    int s = 0, t = m+n+1, f = 0; memset(cnt, c = 0, sizeof(cnt));
    for (int r=1; r<=m; ++r) if (x[r]) {
        f += x[r]; add_edge(s, r, x[r]);
        for (int c=1; c<=n; ++c) if (y[c] && u[r][c]) add_edge(r, m+c, u[r][c]);
    }
    for (int c=1; c<=n; ++c) if (y[c]) add_edge(m+c, t, y[c]);
    if (!bfs(s, t)) {
        if (f) cout << "IMPOSSIBLE" << endl;
        else for (int r=1; r<=m; ++r) for (int c=1; c<=n; ++c) cout << l[r][c], cout << (c<n ? ' ' : '\n');
        return;
    }
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    for (int u = s; d[s] <= t;) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            f -= a; u = s;
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
    if (!f) {
        for (int i=1; i<=m; ++i) for (int j=0; j<cnt[i]; ++j) {
            const edge& ee = e[g[i][j]];
            if (ee.v > m) l[i][ee.v-m] += ee.flow;
        }
        for (int r=1; r<=m; ++r) for (int c=1; c<=n; ++c) cout << l[r][c], cout << (c<n ? ' ' : '\n');
    } else cout << "IMPOSSIBLE" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
        if (t) cout << endl;
    }
    return 0;
}