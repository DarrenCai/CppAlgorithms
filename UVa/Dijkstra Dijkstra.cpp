/**
 * UVa10806
 * 最短往返路
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define N 100
struct edge {int u, v, cap, flow, cost;} e[N*N<<1];
int g[N][N], q[N*N*N<<1], cnt[N], a[N], d[N], p[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

void solve() {
    cin >> m; memset(cnt, c = 0, sizeof(cnt));
    while (m--) {
        int u, v, w; cin >> u >> v >> w; --u; --v; add_edge(u, v, 1, w); add_edge(v, u, 1, w);
    }
    int s = 0, t = n-1, f = 2, cc = 0;
    while (f > 0) {
        memset(d, 127, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = 1;
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
        if (d[t] >= INF) {
            cout << "Back to jail" << endl;
            return;
        }
        --f; cc += d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    cout << cc << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}