/**
 * UVa12167/LA4287
 * 等价性证明
 * NWERC 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20005
int g[N][N], c[N], s[N], sn[N], pre[N], in[N], out[N], clk, cc, m, n, p;

int dfs(int u) {
    int low = pre[u] = ++clk; s[p++] = u;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        low = min(low, dfs(v));
    } else if (!sn[v]) low = min(low, pre[v]);
    if (low == pre[u]) {
        in[++cc] = 0; out[cc] = 0;
        while (true) {
            sn[s[--p]] = cc;
            if (s[p] == u) break;
        }
    }
    return low;
}

int solve() {
    cin >> n >> m;
    memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    while (m--) {
        int u, v; cin >> u >> v; g[u][c[u]++] = v;
    }
    for (int u=1; u<=n; ++u) if(!pre[u]) dfs(u);
    if (cc == 1) return 0;
    for (int u=1; u<=n; ++u) for (int i=0, v; i<c[u]; ++i) if (sn[u] != sn[v = g[u][i]]) ++in[sn[v]], ++out[sn[u]];
    int a = 0, b = 0;
    for (int i=1; i<=cc; ++i) {
        if (in[i] == 0) ++a;
        if (out[i] == 0) ++b;
    }
    return max(a, b);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}