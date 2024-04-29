/**
 * UVa1364/LA3523
 * 圆桌骑士
 * CERC 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
int s[N*N][2], bcc[N][N], g[N][N], c[N], t[N], pre[N], bn[N], color[N], clk, cc, m, n, p; bool off[N][N], ex[N];

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        s[p][0] = u; s[p++][1] = v;
        int lowv = dfs(v, u); low = min(low, lowv);
        if (lowv >= pre[u]) {
            t[++cc] = 0;
            while (true) {
                int x = s[--p][0], y = s[p][1];
                if (bn[x] != cc) bcc[cc][t[cc]++] = x, bn[x] = cc;
                if (bn[y] != cc) bcc[cc][t[cc]++] = y, bn[y] = cc;
                if (x == u && y == v) break;
            }
        }
    } else if (pre[v] < pre[u] && v != fa) {
        s[p][0] = u; s[p++][1] = v; low = min(low, pre[v]);
    }
    return low;
}

bool bipartite(int u, int b) {
    for (int i=0, v; i<c[u]; ++i) if (bn[v = g[u][i]] == b) {
        if (color[v] == color[u]) return false;
        if (!color[v]) {
            color[v] = 3-color[u];
            if (!bipartite(v, b)) return false;
        }
    }
    return true;
}

int solve() {
    memset(off, 0, sizeof(off)); memset(c, p = 0, sizeof(c)); memset(ex, 1, sizeof(ex));
    memset(pre, clk = 0, sizeof(pre)); memset(bn, cc = 0, sizeof(bn));
    while (m--) {
        int u, v; cin >> u >> v;
        off[u][v] = off[v][u] = 1;
    }
    for (int u=1; u<=n; ++u) for (int v=u+1; v<=n; ++v) if (!off[u][v]) g[u][c[u]++] = v, g[v][c[v]++] = u;
    for (int u=1; u<=n; ++u) if (!pre[u]) dfs(u);
    for (int i=1; i<=cc; ++i) {
        for (int j=0; j<t[i]; ++j) bn[bcc[i][j]] = i, color[bcc[i][j]] = 0;
        int u = bcc[i][0]; color[u] = 1;
        if (!bipartite(u, i)) for (int j=0; j<t[i]; ++j) ex[bcc[i][j]] = 0;
    }
    int ans = 0;
    for (int i=1; i<=n; ++i) if (ex[i]) ++ans;
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) cout << solve() << endl;
    return 0;
}