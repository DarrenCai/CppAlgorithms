/**
 * P2050 [NOI2012] 美食节
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 900000
#define N 42
#define M 102
#define P 1002
struct edge {int u, v, cap, flow, cost, c;} e[N*P<<1];
int g[P][P], x[N][M], y[M], q[N*P*P<<1], a[P], d[P], p[P], cnt[P], c, m, n; bool vis[P];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = n+1, b = t, f, cc = 0;
    for (int i=1, c; i<=n; ++i) cin >> c, add_edge(0, i, c, 0);
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j)
        cin >> x[i][j], add_edge(i, b+j, 1, x[i][j]);
    for (int i=1; i<=m; ++i) y[i] = 1, e[c].c = i, add_edge(++b, t, 1, 0);
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = INF;
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
        if (d[t] >= INF) return cc;
        cc += d[t];
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
            if (e[p[u]].v == t && e[p[u]].flow) f = e[p[u]].c;
        }
        ++y[f]; e[c].c = f; add_edge(++b, t, 1, 0);
        for (int i=1; i<=n; ++i) add_edge(i, b, 1, y[f]*x[i][f]);
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}