/**
 * UVa11294
 * 婚宴
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 70
int g[N][N], c[N], s[N], sn[N], low[N], pre[N], clk, cc, m, n, p;

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

void solve() {
    memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    while (m--) {
        int u, v; char cu, cv; cin >> u >> cu >> v >> cv;
        if (cu == 'h' && cv == 'h') add_clause(u<<1, v<<1);
        else if (cu == 'h' && cv == 'w') add_clause(u<<1, v<<1 | 1);
        else if (cu == 'w' && cv == 'h') add_clause(v<<1, u<<1 | 1);
        else add_clause(u<<1 | 1, v<<1 | 1);
    }
    m = 2*n;
    for (int u=0; u<m; ++u) if (!pre[u] && !dfs(u)) {
        cout << "bad luck" << endl; return;
    }
    if (sn[0] > sn[1]) {
        cout << "bad luck" << endl; return;
    }
    for (int i=1; i<n; ++i) {
        if (i > 1) cout << ' ';
        cout << i << (sn[i<<1] < sn[i<<1 | 1] ? 'w' : 'h');
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) solve();
    return 0;
}