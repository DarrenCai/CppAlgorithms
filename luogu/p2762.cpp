/**
 * P2762 太空飞行计划问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define N 102
struct edge {int u, v, cap, flow;} e[5200];
int g[N][N>>1], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n; bool vis[N];

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

void solve() {
    int s = 0, t = m+n+1, cc = 0, u = s; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=m; ++i) {
        int x; cin >> x; cc += x; add_edge(s, i, x);
        while (cin.get() == ' ') cin >> x, add_edge(i, x+m, INF);
    }
    for (int i=1, x; i<=n; ++i) cin >> x, add_edge(i+m, t, x);
    bfs(s, t); memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc -= a; u = s;
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
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    bfs(s, t);
    for (int i=0, k=0; i<cnt[s]; ++i) {
        const edge &ee = e[g[s][i]];
        if (!vis[ee.v]) {
            if (k++) cout << ' ';
            cout << ee.v;
        }
    }
    cout << endl;
    for (int i=0, k=0; i<cnt[t]; ++i) {
        const edge &ee = e[g[t][i]^1];
        if (!vis[ee.u]) {
            if (k++) cout << ' ';
            cout << ee.u-m;
        }
    }
    cout << endl << cc << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) solve();
    return 0;
}