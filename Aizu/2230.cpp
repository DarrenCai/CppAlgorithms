/**
 * Aizu-2230
 * https://vjudge.net/problem/Aizu-2230
 * How to Create a Good Game
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define M 1002
#define N 102
struct edge {int u, v, cap, flow, cost;} e[(M+N)<<1];
int g[N][N], q[N*(M+N)<<1], cnt[N], a[N], d[N], p[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

int mcmf(int s, int t, int f) {
    int cc = 0;
    while (f > 0) {
        memset(d, 127, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = f;
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
        f -= a[t]; cc += d[t]*a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int solve() {
    int cc = 0, s = n, t = n+1, f = 0;
    memset(a, 0, sizeof(a)); memset(cnt, c=0, sizeof(cnt));
    while (m--) {
        int u, v, w; cin >> u >> v >> w; cc -= w; --a[u]; ++a[v]; add_edge(u, v, INF, -w);
    }
    for (int i=0; i<n; ++i) {
        if (a[i] > 0) f += a[i], add_edge(s, i, a[i], 0);
        else if (a[i] < 0) add_edge(i, t, -a[i], 0);
    }
    add_edge(n-1, 0, INF, -mcmf(0, n-1, 1));
    return cc + mcmf(s, t, f);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}