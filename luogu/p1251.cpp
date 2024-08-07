/**
 * P1251 餐巾计划问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 30000000000
#define N 4004
struct edge {int u, v, cost; long long cap, flow;} e[6*N];
int g[N][N], q[6*N*N], d[N], p[N], cnt[N], r[N], c, n; long long a[N]; bool vis[N];

void add_edge(int u, int v, long long cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

long long solve() {
    memset(cnt, 0, sizeof(cnt));
    long long cc = 0; int s = 0, t = 2*n+1;
    for (int i=1; i<=n; ++i) cin >> r[i];
    int _p, _m, _f, _n, _s; cin >> _p >> _m >> _f >> _n >> _s;
    for (int i=1; i<=n; ++i) {
        add_edge(s, i, r[i], 0); add_edge(i+n, t, r[i], 0); add_edge(0, i+n, INF, _p);
        if (i < n) add_edge(i, i+1, INF, 0);
        if (_m+i <= n) add_edge(i, _m+i+n, INF, _f);
        if (_n+i <= n) add_edge(i, _n+i+n, INF, _s);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = INF;
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
        if (d[t] >= 20000) return cc;
        cc += d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) cout << solve() << endl;
    return 0;
}