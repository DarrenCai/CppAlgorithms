/**
 * UVa11613
 * 生产销售规划
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 200000000
#define M 105
#define T 210
struct edge {int u, v, cap, flow, cost;} e[M*T];
int g[T][M], q[M*T*T], a[T], d[T], p[T], cnt[T], c, m, b, t; bool vis[T];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

long long solve() {
    cin >> m >> b; t = 2*m+1;
    memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=m; ++i) {
        int a, n, p, s, e; cin >> a >> n >> p >> s >> e;
        add_edge(0, i, n, a); add_edge(i+m, t, s, -p);
        for (int j=min(i+e, m); j>=i; --j) add_edge(i, j+m, n, b*(j-i));
    }
    long long ans = 0;
    while (true) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[0] = 0; q[0] = 0; a[0] = INF;
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
        if (d[t] >= 0) break;
        ans -= d[t]*(long long)a[t];
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case " << k << ": " << solve() << endl;
    return 0;
}