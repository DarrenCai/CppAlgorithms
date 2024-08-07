/**
 * UVa1751/LA8041
 * World Finals 2017
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 202
struct edge {int u, v, cap, flow, cost;} e[N*N>>1];
int g[N][N>>1], q[N*N*N>>1], a[N], d[N], p[N], cnt[N], c, m, n; bool vis[N], r[N>>1][N>>1];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

long long solve() {
    long long cc = 0; int s = 0, t = m+n+1;
    memset(cnt, c = 0, sizeof(cnt)); memset(d, 0, sizeof(d));
    for (int i=1, x; i<=m; ++i) for (int j=1; j<=n; ++j)
        cin >> x, r[i][j] = x--, d[i] = max(d[i], x), d[m+j] = max(d[m+j], x), cc += max(x, 0);
    for (int i=1; i<=m; ++i) add_edge(s, i, 1, 0), cc -= d[i];
    for (int i=1; i<=n; ++i) add_edge(m+i, t, 1, 0), cc -= d[m+i];
    for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) if (r[i][j] && d[i] == d[m+j]) add_edge(i, m+j, 1, -d[i]);
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = 1;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++]; vis[u] = false;
            for (short i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= 0) return cc;
        cc -= d[t];
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> m >> n) cout << solve() << endl;
    return 0;
}