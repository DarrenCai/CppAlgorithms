/**
 * UVa1146/LA3211
 * 飞机调度
 * SWERC 2004
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 4006
int t[N>>1][2], g[N][N], c[N], s[N], sn[N], low[N], pre[N], clk, cc, m, n, p;

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

void add_clause(int u, int v) {
    g[u][c[u]++] = v^1; g[v][c[v]++] = u^1;
}

bool two_sat(int d) {
    memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    for (int i=0; i<n; ++i) for (int a=0; a<2; ++a) for (int j=i+1; j<n; ++j) for (int b=0; b<2; ++b)
        if (abs(t[i][a]-t[j][b]) < d) add_clause(i<<1 | a, j<<1 | b);
    for (int u=0; u<m; ++u) if (!pre[u] && !dfs(u)) return false;
    return true;
}

int solve() {
    int l = 0, r = 0; m = n<<1;
    for (int i=0; i<n; ++i) cin >> t[i][0] >> t[i][1], r = max(r, t[i][1]);
    while (l < r) {
        int d = (l+r+1)>>1;
        two_sat(d) ? l = d : r = d-1;
    }
    return l;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) cout << solve() << endl;
    return 0;
}