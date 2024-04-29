/**
 * UVa1108/LA5135
 * 井下矿工
 * Final 2011
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 50005
int e[N], pre[N], f[N], clk, cc, m, n, p, kase = 0; bool is_cut[N]; vector<int> g[N]; long long ans;

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk, child = 0;
    for (int i=g[u].size()-1, v; i>=0; --i) if (!pre[v = g[u][i]]) {
        int lowv = dfs(v, u); low = min(low, lowv); ++child;
        if (lowv >= pre[u]) is_cut[u] = 1;
    } else if (pre[v] < pre[u] && v != fa) low = min(low, pre[v]);
    if (fa < 0 && child == 1) is_cut[u] = 0;
    return low;
}

void dfs(int u, int &vet, int &cut, int c) {
    f[u] = c; ++vet;
    for (int i=g[u].size()-1, v; i>=0; --i) {
        if (is_cut[v = g[u][i]]) {
            if (f[v] != c) ++cut;
            f[v] = c;
        } else if (!f[v]) dfs(v, vet, cut, c);
    }
}

void solve() {
    memset(pre, clk = 0, sizeof(pre)); memset(is_cut, p = 0, sizeof(is_cut)); memset(f, n = 0, sizeof(f));
    while (m--) {
        int u, v; cin >> u >> v;
        if (!f[u]) g[u].clear(), f[u] = 1, e[n++] = u;
        if (!f[v]) g[v].clear(), f[v] = 1, e[n++] = v;
        g[u].push_back(v); g[v].push_back(u);
    }
    for (int i=0; i<n; ++i) if (!pre[e[i]]) dfs(e[i]);
    cc = 0; ans = 1; memset(f, 0, sizeof(f));
    for (int i=0, u; i<n; ++i) if (!is_cut[u = e[i]] && !f[u]) {
        int vet = 0, cut = 0;
        dfs(u, vet, cut, i+1);
        if (cut == 1) ++cc, ans *= vet;
        if (cut == 0) cc += 2, ans = ans*vet*(vet-1)/2;
    }
    cout << "Case " << ++kase << ": " << cc << ' ' << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> m && m) solve();
    return 0;
}