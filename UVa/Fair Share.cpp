/**
 * LA3231
 * Seoul 2004
 * UVALive现在无法提交
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 11020
struct edge {int u, v, cap, flow;} e[6*N];
int g[N][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n, s, t; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
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

int max_flow() {
    int flow = 0;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    int u = s;
    while (d[s] <= t) {
        if (u == t) {
            int a = m;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
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
            if (u != s) u = e[p[u]].u;
        }
    }
    return flow;
}

int solve () {
    cin >> n >> m; memset(cnt, c = 0, sizeof(cnt)); s = 0; t = m+n+1;
    int l = 1, r = n-1;
    for (int i=1, a, b; i<=m; ++i) cin >> a >> b, add_edge(0, i, 1), add_edge(i, m+a, 1), add_edge(i, m+b, 1);
    for (int i=1; i<=n; ++i) add_edge(m+i, t, 1);
    while (l < r) {
        int x = (l+r) >> 1;
        for (int i=0; i<c; ++i) e[i].flow = 0;
        for (int i=0; i<cnt[t]; ++i) e[g[t][i]^1].cap = x;
        max_flow() < m ? l = x+1 : r = x;
    }
    return r;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}