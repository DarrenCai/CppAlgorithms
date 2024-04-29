/**
 * UVa11324
 * 最大团
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1005
int g[N][N], scc[N][N], c[N], t[N], s[N], sn[N], pre[N], f[N], clk, cc, m, n, p;

int dfs(int u) {
    int low = pre[u] = ++clk; s[p++] = u;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        low = min(low, dfs(v));
    } else if (!sn[v]) low = min(low, pre[v]);
    if (low == pre[u]) {
        t[++cc] = 0; f[cc] = 0;
        while (true) {
            sn[scc[cc][t[cc]++] = s[--p]] = cc;
            if (s[p] == u) break;
        }
    }
    return low;
}

int dfs2(int i) {
    if (f[i]) return f[i];
    int &r = f[i] = t[i], mx = 0;
    for (int j=0; j<t[i]; ++j) for (int k=0, u=scc[i][j], v; k<c[u]; ++k)
        if (sn[v = g[u][k]] != i) mx = max(mx, dfs2(sn[v]));
    return r += mx;
}

int solve() {
    cin >> n >> m;
    memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    while (m--) {
        int u, v; cin >> u >> v; g[u][c[u]++] = v;
    }
    for (int u=1; u<=n; ++u) if(!pre[u]) dfs(u);
    if (cc == 1) return n;
    int ans = 0;
    for (int i=1; i<=cc; ++i) ans = max(ans, dfs2(i));
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}