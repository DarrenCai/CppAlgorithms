/**
 * UVa10972
 * 道路修建
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
int g[N][N], c[N], c2[N], f[N], h[N], d[N], e[N], pre[N], bn[N], clk, m, n, t, cc; bool is_bridge[N][N];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

int dfs(int u, int fa) {
    int low = pre[u] = ++clk;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        int lowv = dfs(v, u); low = min(low, lowv);
        if (lowv > pre[u]) is_bridge[u][v] = is_bridge[v][u] = true;
    } else if (pre[v] < pre[u] && v != fa) low = min(low, pre[v]);
    return low;
}

void dfs(int u) {
    bn[u] = cc;
    for (int i=0, v; i<c[u]; ++i) if (!bn[v = g[u][i]] && !is_bridge[u][v]) dfs(v);
}

int solve() {
    memset(c, t = 0, sizeof(c)); memset(c2, 0, sizeof(c2)); memset(bn, cc = 0, sizeof(bn));
    memset(is_bridge, 0, sizeof(is_bridge)); memset(pre, clk = 0, sizeof(pre));
    for (int i=1; i<=n; ++i) f[i] = i;
    while (m--) {
        int u, v; cin >> u >> v;
        g[u][c[u]++] = v; g[v][c[v]++] = u;
        u = find(u); v = find(v); f[max(u, v)] = min(u, v);
    }
    for (int u=1; u<=n; ++u) {
        if (find(u) == u) d[e[u] = t++] = 0;
        if (!pre[u]) dfs(u, -1);
    }
    for (int u=1; u<=n; ++u) if (!bn[u]) h[++cc] = e[f[u]], dfs(u);
    if (cc == 1) return 0;
    for (int u=1; u<=n; ++u) for (int i=0, v; i<c[u]; ++i) if (bn[v = g[u][i]] != bn[u]) ++c2[bn[u]], ++c2[bn[v]];
    for (int i=1; i<=cc; ++i) if (c2[i] == 2) ++d[h[i]];
    cc = 0;
    for (int i=0; i<t; ++i) if (d[i] > 2) cc += d[i] - 2;
    return t + ((cc+1) >> 1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}