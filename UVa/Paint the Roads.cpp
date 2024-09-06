/**
 * UVa12092/LA2197
 * 粉刷道路
 * Dhaka 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define M 4100
#define N 82
struct edge {int u, v, cap, flow, cost;} e[M];
int g[N][N], q[M*N], a[N], d[N], p[N], cnt[N], c, m, n, k; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

int solve() {
    cin >> n >> m >> k; memset(cnt, c = 0, sizeof(cnt));
    int s = n<<1, t = s+1, f = n*k, cc = 0;
    for (int i=0; i<n; ++i) add_edge(s, i+n, k, 0), add_edge(i, t, k, 0);
    while (m--) {
        int u, v, w; cin >> u >> v >> w; add_edge(u+n, v, 1, w);
    }
    while (f > 0) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = 1;
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
        if (d[t] >= INF) return -1;
        --f; cc += d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}