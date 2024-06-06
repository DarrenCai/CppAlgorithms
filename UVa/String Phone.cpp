/**
 * UVa1466/LA4849
 * 有绳电话
 * Daejeon 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 3010
int dx[][2] = {{0, 1}, {0, 1}}, dy[][2] = {{0, 1}, {1, 0}}, d[N][N], g0[N][N], g[N<<1][N<<1], c0[N], 
    c[N<<1], f[N], x[N], y[N], color[N], s[N<<1], sn[N<<1], low[N<<1], pre[N<<1], clk, cc, p, m, n;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

bool bipartite(int u) {
    for (int i=0; i<c0[u]; ++i) {
        int v = g0[u][i], b = ((abs(x[u]-x[v]) + abs(y[u]-y[v])) ^ d[u][v] ^ color[u]) & 1;
        if (color[v] < 0) {
            color[v] = b;
            if (!bipartite(v)) return false;
        } else if (color[v] != b) return false;
    }
    return true;
}

void add_clause(int u, int v) {
    g[u][c[u]++] = v^1; g[v][c[v]++] = u^1;
}

bool dfs(int u) {
    low[u] = pre[u] = ++clk; s[p++] = u;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        if (!dfs(v)) return false;
        low[u] = min(low[u], low[v]);
    } else if (!sn[v]) low[u] = min(low[u], pre[v]);
    if (low[u] == pre[u]) {
        ++cc;
        while (true) {
            if (cc == sn[s[--p]^1]) return false;
            sn[s[p]] = cc;
            if (s[p] == u) break;
        }
    }
    return true;
}

bool check(int r, int b) {
    memset(color, -1, sizeof(color)); color[r] = b;
    if (!bipartite(r)) return false;
    memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    for (r=1; r<=n; ++r) if (color[r] >= 0) for (int i=0; i<c0[r]; ++i) for (int j=0, a=g0[r][i]; j<2; ++j) {
        int xu = x[r] + dx[color[r]][j], yu = y[r] + dy[color[r]][j], u = r<<1 | j;
        for (int k=0; k<2; ++k) {
            int xv = x[a] + dx[color[a]][k], yv = y[a] + dy[color[a]][k], v = a<<1 | k;
            if (abs(xu-xv)+abs(yu-yv) != d[r][a]) add_clause(u, v);
        }
    }
    for (int u=2, m=(n+1)<<1; u<m; ++u) if (!pre[u] && !dfs(u)) return false;
    return true;
}

void solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> x[i] >> y[i], c0[i] = 0, f[i] = i;
    cin >> m;
    while (m--) {
        int u, v; cin >> u >> v >> d[u][v];
        d[v][u] = d[u][v]; g0[u][c0[u]++] = v; g0[v][c0[v]++] = u; f[find(u)] = find(v);
    }
    bool ok  = true;
    for (int i=1; i<=n; ++i) if (find(i) == i && !check(i, 0) && !check(i, 1)) {
        ok = false; break;
    }
    cout << (ok ? "possible" : "impossible") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}