/**
 * UVa1391/LA3713
 * 宇航员分组
 * CERC 2006
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 200020
int a[N>>1], s[N], sn[N], low[N], pre[N], clk, cc, m, n, p; vector<int> g[N];

bool dfs(int u) {
    low[u] = pre[u] = ++clk; s[p++] = u;
    for (int i=g[u].size()-1, v; i>=0; --i) if (!pre[v = g[u][i]]) {
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
    g[u].push_back(v^1); g[v].push_back(u^1);
}

void two_sat() {
    int t = 0;
    for (int i=0; i<n; ++i) cin >> a[i], t += a[i], g[i].clear(), g[i + n].clear();
    t = (t+n-1)/n;
    while (m--) {
        int i, j; cin >> i >> j; --i; --j;
        add_clause(i<<1, j<<1);
        if ((a[i]>=t && a[j]>=t) || (a[i]<t && a[j]<t)) add_clause(i<<1 | 1, j<<1 | 1);
    }
    memset(pre, clk = p = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
    for (int u=0, m=n<<1; u<m; ++u) if (!pre[u] && !dfs(u)) {
        cout << "No solution." << endl; return;
    }
    for (int i=0; i<n; ++i) cout << (sn[i<<1] < sn[i<<1 | 1] ? 'C' : (a[i]<t ? 'B' : 'A')) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) two_sat();
    return 0;
}