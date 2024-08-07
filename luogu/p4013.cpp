/**
 * P4013 数字梯形问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1182
struct edge {int u, v, cap, flow, cost;} e[3*N]; 
int g[N][N>>1], q[3*N*N], a[N], d[N], p[N], cnt[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int mcmf(int s, int t) {
    int cc = 0, f = 0;
    while (f < m) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = m;
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
        f += a[t]; cc -= d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

void solve() {
    int s = 0, q = m*n+n*(n-1)/2, t = 2*q+1; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1, x; i<=m; ++i) cin >> x, add_edge(s, i+q, 1, -x);
    for (int i=t-m-n+1; i<t; ++i) add_edge(i, t, m, 0);
    for (int i=1, u=m+1; i<n; ++i) for (int j=0, k=m+i; j<k; ++j, ++u) {
        int x; cin >> x; add_edge(u, u+q, 1, 0);
        if (j) add_edge(u-k+q, u, 1, -x);
        if (j+1 < k) add_edge(u-k+1+q, u, 1, -x);
    }
    cout << mcmf(s, t) << endl;
    for (int i=0; i<c; ++i) {
        e[i].flow = 0;
        if (e[i].u != s && e[i].v !=t && e[i].v == e[i].u + q) e[i].cap = m;
    }
    cout << mcmf(s, t) << endl;
    for (int i=0; i<c; ++i) {
        e[i].flow = 0;
        if (e[i].u != s && ~i&1) e[i].cap = m;
    }
    cout << mcmf(s, t) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) solve();
    return 0;
}