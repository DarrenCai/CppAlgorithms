/**
 * UVa1486/LA5095
 * 货物运输
 * Harbin 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define M 50000
#define N 101
struct edge {int u, v, cap, flow, cost;} e[M];
int g[N][M], q[M*N], a[N], d[N], p[N], cnt[N], c, m, n, k; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

int solve() {
    int s = 1, t = n, cc = 0; memset(cnt, c = 0, sizeof(cnt));
    while (m--) {
        int u, v, a, c; cin >> u >> v >> a >> c;
        for (int i=2*c-1; i>0; i-=2) add_edge(u, v, 1, a*i);
    }
    while (k > 0) {
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
        --k; cc += d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m >> k) cout << solve() << endl;
    return 0;
}