/**
 * poj2396
 * http://poj.org/problem?id=2396
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define M 202
#define N 22
#define T 224
struct edge {int u, v, cap, flow;} e[M*N<<1];
int g[T][M], l[M][N], u[M][N], q[T], p[T], d[T], cur[T], num[T], cnt[T], cs[T], ct[T], c, m, n; bool vis[T];

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
    return ok;
}

void solve() {
    cin >> m >> n; memset(l, 0, sizeof(l)); memset(u, 127, sizeof(u)); memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = m+n+1, f = 0, f2 = 0; memset(cs, 0, sizeof(cs)); memset(ct, 0, sizeof(ct));
    for (int i=1, x; i<=m; ++i) cin >> x, f += x, add_edge(s, i, x);
    for (int i=1, x; i<=n; ++i) cin >> x, f2 += x, add_edge(m+i, t, x);
    if (!check_lu() || f != f2) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    add_edge(t+1, s, f); add_edge(t, t+2, f); s = t+1; t = s+1;
    for (int r=1; r<=m; ++r) for (int c=1; c<=n; ++c) {
        f += l[r][c]; cs[m+c] += l[r][c]; ct[r] += l[r][c];
        if (u[r][c] > l[r][c]) add_edge(r, m+c, u[r][c] - l[r][c]);
    }
    for (int r=1; r<=m; ++r) if (ct[r]) add_edge(r, t, ct[r]);
    for (int c=1; c<=n; ++c) if (cs[m+c]) add_edge(s, m+c, cs[m+c]);
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
            if (ee.v > m && ee.v <= m+n) l[i][ee.v-m] += ee.flow;
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