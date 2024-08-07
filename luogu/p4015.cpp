/**
 * P4015 运输问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 202
struct edge {int u, v; int cap, flow, cost;} e[N*N>>1];
int g[N][N>>1], q[N*N*N>>1], p[N], cnt[N], m, n, c; int d[N], a[N], x; bool vis[N];

void addEdge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int mcmf(int t) {
    int cc = 0;
    while (true) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[0] = 0; q[0] = 0; a[0] = x;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++]; vis[u] = false;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= 0x7f7f7f7f) return cc;
        cc += a[t]*d[t];
        for (int u=t; u!=0; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) {
        int s = 0, t = m+n+1, v; memset(cnt, x = c = 0, sizeof(cnt));
        for (int i=1; i<=m; ++i) cin >> v, x = max(x, v), addEdge(s, i, v, 0);
        for (int i=1; i<=n; ++i) cin >> v, addEdge(m+i, t, v, 0);
        for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) cin >> v, addEdge(i, m+j, x, v);
        cout << mcmf(t) << endl;
        for (int i=0; i<c; ++i) e[i].cost *= -1, e[i].flow = 0;
        cout << -mcmf(t) << endl;
    }
    return 0;
}