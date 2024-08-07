/**
 * P2770 航空路线问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 202
struct edge {int u, v, cap, flow, cost;} e[N*N>>2]; char x[N>>1][16], y[16];
int g[N][N], q[N*N*N>>2], a[N], d[N], p[N], cnt[N], c, n, m; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int read() {
    cin >> y;
    for (int i=0; i<n; ++i) if (strcmp(x[i], y) == 0) return i;
    return n;
}

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = 2*n-1, f = 0, cc = 0;
    for (int i=0; i<n; ++i) cin >> x[i], add_edge(i, i+n, i==0 || i==n-1 ? 2 : 1, i==0 || i==n-1 ? 0 : -1);
    while (m--) {
        int u = read(), v = read();
        if (v < u) u += v, v = u - v, u = u - v;
        add_edge(u+n, v, 2, 0);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
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
        if (d[t] >= n) break;
        ++f; cc -= d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    if (f == 2) {
        cout << cc + 2 << endl << x[s] << endl;
        for (int u=s; u!=t;) for (int i=0; i<cnt[u]; ++i) {
            edge &ee = e[g[u][i]];
            if (ee.flow > 0) {
                --ee.flow; u = ee.v;
                if (u < n) cout << x[u] << endl;
                break;
            }
        }
        for (int u=t; u!=s;) for (int i=0; i<cnt[u]; ++i) {
            edge &ee = e[g[u][i]^1];
            if (ee.flow > 0) {
                u = ee.u;
                if (ee.v != t && u < n) cout << x[u] << endl;
                break;
            }
        }
    } else cout << "No Solution!" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}