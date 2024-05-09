/**
 * UVa11354
 * 邦德
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define M 100100
#define N 50050
int anc[N][16], mx[N][16], f[N], w[N], d[N], m, n, q, kase = 0; vector<int> g[N];
struct edge {
    int u, v, w;
    bool operator< (const edge& rhs) const {
        return w < rhs.w;
    }
} e[M];

int find(int x) {
    return x==f[x] ? x : f[x] = find(f[x]);
}

void dfs(int u, int fa = 0) {
    for (int i=g[u].size()-1; i>=0; --i) {
        const edge& eg = e[g[u][i]]; int v = eg.u + eg.v - u;
        if (v == fa) continue;
        f[v] = u; w[v] = eg.w; d[v] = d[u]+1; dfs(v, u);
    }
}

int query() {
    int s, t, lv = 1, ans = 0; cin >> s >> t;
    if (d[s] < d[t]) s += t, t = s-t, s = s-t;
    while ((1<<lv) <= d[s]) ++lv; --lv;
    for (int i = lv; i>=0; --i) if (d[s] - (1<<i) >= d[t]) ans = max(ans, mx[s][i]), s = anc[s][i];
    if (s == t) return ans;
    for (int i = lv; i>=0; --i) if (anc[s][i] && anc[s][i] != anc[t][i])
        ans = max(ans, max(mx[s][i], mx[t][i])), s = anc[s][i], t = anc[t][i];
    return max(ans, max(w[s], w[t]));
}

void solve() {
    for (int i=0; i<m; ++i) cin >> e[i].u >> e[i].v >> e[i].w;
    for (int i=1; i<=n; ++i) f[i] = i, g[i].clear();
    sort(e, e+m);
    for (int i=0, t=0; i<m; ++i) {
        int u = e[i].u, v = e[i].v, x = find(u), y = find(v);
        if (x == y) continue;
        f[x] = y; g[u].push_back(i); g[v].push_back(i);
        if (++t == n-1) break;
    }
    d[1] = f[1] = w[1] = 0; dfs(1);
    for (int i=1; i<=n; ++i) {
        anc[i][0] = f[i]; mx[i][0] = w[i];
        for (int j=1; (1<<j) < n; ++j) anc[i][j] = 0;
    }
    for (int j=1; (1<<j) < n; ++j) for (int i=1; i<=n; ++i) if (anc[i][j-1] > 0) {
        int a = anc[i][j-1]; anc[i][j] = anc[a][j-1]; mx[i][j] = max(mx[i][j-1], mx[a][j-1]);
    }
    cin >> q;
    if (kase++) cout << endl;
    while (q--) cout << query() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}