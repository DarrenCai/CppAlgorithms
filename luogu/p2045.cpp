/**
 * P2045 方格取数加强版
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 5010
struct edge {int u, v, cap, flow, cost;} e[N<<2];
int g[N][4], q[N*N<<2], a[N], d[N], p[N], cnt[N], c, n, f; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = 2*n*n, cc = 0;
    add_edge(s, 1, f, 0);
    for (int i=1, k=1, x=n*n; i<=n; ++i) for (int j=1; j<=n; ++j, ++k) {
        int a; cin >> a;
        add_edge(k, k+x, 1, -a); add_edge(k, k+x, f-1, 0);
        if (i < n) add_edge(k+x, k+n, f, 0);
        if (j < n) add_edge(k+x, k+1, f, 0);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = f;
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
        cc -= d[t] * a[t];
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> f) cout << solve() << endl;
    return 0;
}