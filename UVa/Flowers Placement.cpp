/**
 * UVa1459/LA4748
 * Shanghai 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 205
int g[N][N], f[N][N], c[N], px[N], py[N], vis[N], ans[N], p1[N], p2[N], m, n, k, clk; bool use[N];

bool dfs(int u, int pos = -1) {
    if (u <= pos) return false;
    vis[u] = clk;
    for (int i=0, v; i<c[u]; ++i) if (py[v = g[u][i]] < 0 || (vis[py[v]]!=clk && dfs(py[v], pos))) {
        px[u] = v; py[v] = u;
        return true;
    }
    return false;
}

int max_match() {
    memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
    int cc = 0;
    for (int i=1; i<=n; ++i) if (px[i] < 0 && dfs(clk = i)) ++cc;
    return cc;
}

bool ok(int u, int v) {
    if (px[u] == v) return true;
    int x = 0;
    for (int i=1; i<=n; ++i) {
        p1[i] = px[i]; p2[i] = py[i];
        if (px[i] == v) if ((x = i) < u) return false;
    }
    px[x] = py[px[u]] = -1; px[u] = v; py[v] = u; ++clk;
    if (dfs(x, u)) return true;
    for (int i=1; i<=n; ++i) px[i] = p1[i], py[i] = p2[i];
    return false;
}

bool find(int u) {
    if (u > n) return ++m == k;
    for (int i=0, v; i<c[u]; ++i) if (!use[v = g[u][i]] && ok(u, v)) {
        use[v] = true; ans[u] = v;
        if (find(u+1)) return true;
        use[v] = false;
    }
    return false;
}

void solve () {
    cin >> n >> m >> k;
    for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) cin >> f[i][j];
    for (int i=1; i<=n; ++i) {
        memset(vis, c[i] = 0, sizeof(vis));
        for (int j=1; j<=m; ++j) vis[f[j][i]] = true;
        for (int j=1; j<=n; ++j) if (!vis[j]) g[i][c[i]++] = j;
    }
    if (max_match() != n) {
        cout << " -1" << endl;
        return;
    }
    memset(use, m = 0, sizeof(use)); memset(vis, clk = 0, sizeof(vis));
    if (find(1)) {
        for (int i=1; i<=n; ++i) cout << ' ' << ans[i];
        cout << endl;
    } else cout << " -1" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ':', solve();
    return 0;
}