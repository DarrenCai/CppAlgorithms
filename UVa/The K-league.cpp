/**
 * UVa1306/LA2531
 * 足球联赛
 * Taejon 2002
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 26
#define M 326
struct edge {int u, v, cap, flow;} e[6*M];
int g[M][M], q[M], p[M], d[M], cur[M], num[M], cnt[M], w0[N], w[N], c, n, t; bool vis[M], f[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

bool bfs() {
    memset(vis, 0, sizeof(vis)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<cnt[v]; ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[0];
}

void max_flow() {
    if (!bfs()) return;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    int u = 0;
    while (d[0] <= t) {
        if (u == t) {
            int a = 101*M;
            for (int v=t; v!=0; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=0; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            u = 0;
        }
        int ok = 0;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = 1; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                break;
            }
        }
        if (!ok) {
            int m = t;
            for (int i=0; i<cnt[u]; i++) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != 0) u = e[p[u]].u;
        }
    }
}

void solve() {
    cin >> n; t = n; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1, _; i<=n; ++i) cin >> w0[i] >> _, w[i] = 0;
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
        int a; cin >> a; w[i] += a;
        if (i < j && a) add_edge(0, ++t, a), add_edge(t, i, a), add_edge(t, j, a);
    }
    memset(f, 0, sizeof(f)); ++t;
    for (int i=1; i<=n; ++i) add_edge(i, t, 0);
    for (int i=1; i<=n; ++i) if (!f[i]) {
        for (int j=0; j<c; ++j) e[j].flow = 0;
        bool ok = true;
        for (int j=0, cc=w0[i] + w[i]; j<cnt[t]; ++j) {
            edge &ee = e[g[t][j]^1]; ee.cap = ee.u==i ? w[i] : cc - w0[ee.u];
            if (ee.cap < 0) {
                ok = false; break;
            }
        }
        if (!ok) continue;
        max_flow();
        int cc = 0;
        for (int j=0; j<cnt[0]; ++j) if (e[g[0][j]].flow == e[g[0][j]].cap) ++cc;
        if (cc == cnt[0]) {
            f[i] = true;
            for (int j=0; j<cnt[t]; ++j) {
                edge &ee = e[g[t][j]^1];
                if (ee.cap == ee.flow) f[ee.u] = 1;
            }
        }
    }
    for (int i=1, j=0; i<=n; ++i) if (f[i]) {
        if (j++) cout << ' ';
        cout << i;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}