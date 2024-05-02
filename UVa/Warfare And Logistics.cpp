/**
 * UVa1416/LA4080
 * 战争和物流
 * Changchun 2007
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define INF 100000000
#define M 1010
#define N 102
int g[N][N], id[N][N], c[N], w1[M], w2[M], d[N], f[N], p[N], m, n, l, t; long long e[M];
struct node {
    int d, u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

long long dijkstra(int s) {
    memset(d, 0x1f, sizeof(d)); memset(f, d[s] = 0, sizeof(f)); memset(p, 0, sizeof(p));
    priority_queue<node> q; q.push({0, s});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (f[u]) continue;
        f[u] = 1;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i], j = id[u][v];
            if (d[v] > d[u] + w1[j]) d[v] = d[u] + w1[j], p[v] = u, q.push({d[v], v});
        }
    }
    long long t = 0;
    for (int i=1; i<=n; ++i) t += d[i]>=INF ? l : d[i];
    return t;
}

long long dijkstra(int s, int x) {
    memset(d, 0x1f, sizeof(d)); memset(f, d[s] = 0, sizeof(f)); priority_queue<node> q; q.push({0, s});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (f[u]) continue;
        f[u] = 1;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i], j = id[u][v], w = j==x ? w2[j] : w1[j];
            if (d[v] > d[u] + w) d[v] = d[u] + w, q.push({d[v], v});
        }
    }
    long long t = 0;
    for (int i=1; i<=n; ++i) t += d[i]>=INF ? l : d[i];
    return t;
}

void solve() {
    memset(c, 0, sizeof(c)); memset(id, e[0] = 0, sizeof(id));
    for (int i=t=0; i<m; ++i) {
        int u, v, w; cin >> u >> v >> w; int j = id[u][v];
        if (!j) g[u][c[u]++] = v, g[v][c[v]++] = u, e[id[u][v] = id[v][u] = ++t] = 0, w1[t] = w, w2[t] = INF;
        else if (w < w1[j]) w2[j] = w1[j], w1[j] = w;
        else if (w < w2[j]) w2[j] = w;
    }
    for (int i=1; i<=n; ++i) {
        long long s = dijkstra(i);
        for (int j=0; j<=t; ++j) e[j] += s;
        for (int u=1; u<=n; ++u) if (p[u]) {
            int x = id[u][p[u]];
            e[x] += dijkstra(i, x) - s;
        }
    }
    long long cc = 0;
    for (int j=1; j<=t; ++j) cc = max(cc, e[j]);
    cout << e[0] << ' ' << cc << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> l) solve();
    return 0;
}