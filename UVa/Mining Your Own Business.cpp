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
int s[N][2], e[N], pre[N], bn[N], clk, cc, m, n, p, kase = 0; bool is_cut[N], f[N]; vector<int> bcc[N], g[N];

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk, child = 0;
    for (int i=g[u].size()-1, v; i>=0; --i) if (!pre[v = g[u][i]]) {
        s[p][0] = u; s[p++][1] = v; ++child;
        int lowv = dfs(v, u); low = min(low, lowv);
        if (lowv >= pre[u]) {
            bcc[++cc].clear(); is_cut[u] = 1;
            while (true) {
                int x = s[--p][0], y = s[p][1];
                if (bn[x] != cc) bcc[cc].push_back(x), bn[x] = cc;
                if (bn[y] != cc) bcc[cc].push_back(y), bn[y] = cc;
                if (x == u && y == v) break;
            }
        }
    } else if (pre[v] < pre[u] && v != fa) {
        s[p][0] = u; s[p++][1] = v; low = min(low, pre[v]);
    }
    if (fa < 0 && child == 1) is_cut[u] = 0;
    return low;
}

void solve() {
    memset(pre, clk = 0, sizeof(pre)); memset(bn, cc = 0, sizeof(bn));
    memset(is_cut, p = 0, sizeof(is_cut)); memset(f, n = 0, sizeof(f));
    while (m--) {
        int u, v; cin >> u >> v;
        if (!f[u]) g[u].clear(), f[u] = 1, e[n++] = u;
        if (!f[v]) g[v].clear(), f[v] = 1, e[n++] = v;
        g[u].push_back(v); g[v].push_back(u);
    }
    for (int i=0; i<n; ++i) if (!pre[e[i]]) dfs(e[i]);
    int cnt = 0; long long ans = 1;
    for (int i=1, t1=0, t2=0; i<=cc; ++i, t1=0, t2=0) {
        for (int j=bcc[i].size()-1; j>=0; --j) is_cut[bcc[i][j]] ? ++t1 : ++t2;
        if (t1 == 1) ++cnt, ans *= t2;
        if (t1 == 0) cnt += 2, ans = ans*t2*(t2-1)/2;
    }
    cout << "Case " << ++kase << ": " << cnt << ' ' << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> m && m) solve();
    return 0;
}