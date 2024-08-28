/**
 * UVa12433
 * 租车
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 600000
#define N 104
struct edge {int u, v, cap, flow, cost;} e[N*N];
int g[N][N], q[N*N*N], a[N], d[N], p[N], cnt[N], c; bool vis[N];
    
void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

void solve() {
    int n, C, R, f = 0, cc = 0; cin >> n >> C >> R;
    int s = 0, t = 2*n+2; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<n; ++i) add_edge(i, i+1, INF, 0);
    for (int i=1, r; i<=n; ++i) cin >> r, f += r, add_edge(t-1, i+n, INF, 0), add_edge(i+n, t, r, 0), add_edge(s, i, r, 0);
    for (int i=0, c, p; i<C; ++i) cin >> c >> p, add_edge(s, t-1, c, p);
    for (int i=0; i<R; ++i) {
        int d, s; cin >> d >> s; ++d;
        for (int j=1; j<n; ++j) if (j+d <= n) add_edge(j, j+d+n, INF, s);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = INF;
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
        if (d[t] >= INF) break;
        f -= a[t]; cc += d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    f ? cout << "impossible" << endl : cout << cc << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case " << k << ": ", solve();
    return 0;
}