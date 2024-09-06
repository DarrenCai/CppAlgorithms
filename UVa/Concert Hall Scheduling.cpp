/**
 * UVa1317/LA2796
 * 音乐厅调度
 * Aizu 2003
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1002
#define N 368
struct edge {int u, v, cap, flow, cost;} e[(M+N)<<1];
int g[N][M], q[(M+N)*N<<1], a[N], d[N], p[N], cnt[N], c, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

int solve() {
    int s = N, t = 0, cc = 0; memset(cnt, c = 0, sizeof(cnt));
    while (n--) {
        int u, v, w; cin >> u >> v >> w; s = min(s, u); t = max(t, ++v + 1); add_edge(u, v, 1, -w);
    }
    for (int i=s; i<t; ++i) add_edge(i, i+1, 2, 0);
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = 1;
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
        if (d[t] >= 0) return cc;
        cc -= d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) cout << solve() << endl;
    return 0;
}