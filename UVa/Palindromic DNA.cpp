/**
 * UVa12273/LA4958
 * SWERC 2010
 */

#include <iostream>
using namespace std;

#define w(c) c=='A' ? 1 : (c=='G' ? 2 : (c=='T' ? 4 : 8))
#define M 20020
int g[M][M>>1], f[M>>1], h[M>>1], v[M>>1], c[M], s[M], sn[M], low[M], pre[M], cc, clk, n, p, t; char d[M>>1];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
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

bool solve() {
    cin >> d;
    for (int i=0; i<n; ++i) f[i] = i, h[i] = 0;
    while (t--) {
        int l, h; char _; cin >> l >> _; h = ++l >> 1;
        for (int i=1; i<l; ++i) {
            cin >> v[i];
            if (i > h) f[find(v[i])] = find(v[l-i]);
        }
    }
    t = n<<1;
    for (int u=0; u<t; ++u) c[u] = pre[u] = sn[u] = cc = p = clk = 0;
    for (int i=0; i<n; ++i) h[find(i)] |= w(d[i]);
    for (int i=0; i<n; ++i) {
        int j = f[i], v = h[j];
        if (v == 15) return false;
        if (i > 0) add_clause((i-1) << 1, i << 1);
        if ((v&5) == 5) {
            if (d[i]=='A' || d[i]=='T') j=i<<1 | 1, g[j][c[j]++] = j^1;
        } else if ((v&10) == 10) {
            if (d[i]=='G' || d[i]=='C') j=i<<1 | 1, g[j][c[j]++] = j^1;
        } else if (i != j && (v==3 || v==6 || v==9 || v==12)) {
            bool e = d[i] == d[j];
            add_clause(i<<1, e ? j<<1 | 1 : j<<1); add_clause(i<<1 | 1, e ? j<<1 : j<<1 | 1);
        }
    }
    for (int u=0; u<t; ++u) if (!pre[u] && !dfs(u)) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> t && n) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}