/**
 * P2766 最长不降子序列问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1006
struct edge {int u, v, cap, flow, cost;} e[N*N>>2];
int g[N][N], q[N*N*N>>2], a[N], d[N], p[N], cnt[N], x[N], c, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int mcmf(int s, int t, int flow, int cost) {
    int f = 0;
    while (true) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = 1;
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
        if (flow == 1) return d[t];
        if (d[t] > cost) return f;
        ++f;
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return f;
}

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=n; ++i) cin >> x[i];
    int s = 0, t = 2*n+1;
    for (int i=1; i<=n; ++i) {
        add_edge(s, i, n, 0); add_edge(i, i+n, 1, -1);
        for (int j=i+1; j<=n; ++j) if (x[i] <= x[j]) add_edge(i+n, j, 1, 0);
        add_edge(i+n, t, n, 0);
    }
    int cc = mcmf(s, t, 1, 0);
    cout << -cc << endl;
    for (int i=0; i<c; ++i) e[i].flow = 0;
    if (cc < -1) {
        cout << mcmf(s, t, 0, cc) << endl;
        for (int i=0; i<c; ++i) e[i].flow = 0;
        e[g[1][1]].cap = e[g[n][cnt[n]-1]].cap = n;
        cout << mcmf(s, t, 0, cc) << endl;
    } else cout << n << endl << n << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) solve();
    return 0;
}