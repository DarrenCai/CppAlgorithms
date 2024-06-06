/**
 * UVa1464/LA4839
 * Hangzhou 2010
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define M 110010
#define N 10010
#define L 17
int anc[M][L], pre[N], s[M], bn[M], x[M], y[M], fa[M], lv[M], clk, cc, m, n, p;
bool is_cut[N], vis[M]; vector<int> g[N], h[M];

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk, child = 0;
    for (int i=g[u].size()-1; i>=0; --i) {
        int e = g[u][i], v = x[e] + y[e] - u;
        if (vis[e]) continue;
        vis[e] = true; s[p++] = e;
        if (!pre[v]) {
            int lowv = dfs(v, u); low = min(low, lowv); ++child;
            if (lowv >= pre[u]) {
                is_cut[u] = true; ++cc;
                while (true) {
                    bn[s[--p]] = cc;
                    if (s[p] == e) break;
                }
            }
        } else if (pre[v] < pre[u] && v != fa) low = min(low, pre[v]);
    }
    if (fa < 0 && child == 1) is_cut[u] = false;
    return low;
}

void dfs2(int u, int f = 0) {
    lv[u] = lv[f]+1; fa[u] = f;
    for (int i=h[u].size()-1, v; i>=0; --i) if (lv[v = h[u][i]] < 0) dfs2(v, u);
}

int query() {
    int s, t; cin >> s >> t;
    s = bn[s]; t = bn[t];
    if (lv[t] > lv[s]) s += t, t = s - t, s = s - t;
    int k = lv[s] - lv[t], i = 1, ans = (lv[s] + lv[t]) >> 1;
    while ((1<<i) <= k) ++i;
    while (i-- && k) if ((1<<i) <= k) s = anc[s][i], k -= 1<<i;
    if (s == t) return ans - lv[s];
    for (i=1; (1<<i) <= lv[s]; ++i);
    while (i--) if ((1<<i) <= lv[s] && anc[s][i] != anc[t][i]) s = anc[s][i], t = anc[t][i];
    return ans - lv[fa[s]];
}

void solve() {
    for (int i=1; i<=n; ++i) g[i].clear();
    for (int i=1; i<=m; ++i) cin >> x[i] >> y[i], g[x[i]].push_back(i), g[y[i]].push_back(i);
    memset(pre, clk = 0, sizeof(pre)); memset(bn, cc = p = 0, sizeof(bn));
    memset(is_cut, 0, sizeof(is_cut)); memset(vis, 0, sizeof(vis));
    for (int u=1; u<=n; ++u) if (!pre[u]) dfs(u);
    for (int i=0; i<=cc; ++i) h[i].clear(), lv[i] = -1, x[i] = 0;
    for (int u=1; u<=n; ++u) if (is_cut[u]) {
        h[++cc].clear(); lv[cc] = -1;
        for (int i=g[u].size()-1, e; i>=0; --i) if (x[e = bn[g[u][i]]] != cc)
            h[e].push_back(cc), h[cc].push_back(e), x[e] = cc;
    }
    for (int i=1; i<=cc; ++i) {
        if (lv[i] < 0) dfs2(i);
        anc[i][0] = fa[i];
    }
    for (int i=1; i<L; ++i) for (int j=1; j<=cc; ++j) if ((1<<i) <= lv[j]) anc[j][i] = anc[anc[j][i-1]][i-1];
    int q; cin >> q;
    while (q--) cout << query() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) solve();
    return 0;
}