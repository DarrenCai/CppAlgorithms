/**
 * UVa12223/LA4614
 * 移居到纽伦堡
 * NWERC 2009
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 50050
long long d[N], f[N], ans, tf; struct edge {int a, b, t;} e[N]; vector<int> g[N];

long long dfs(int u = 1, int fa = 0) {
    long long c = 0;
    for (int i=g[u].size()-1; i>=0; --i) {
        const edge& p = e[g[u][i]]; int v = p.a + p.b - u;
        if (v != fa) c += dfs(v, u) + f[v]*p.t, f[u] += f[v];
    }
    return c;
}

void dfs2(int u = 1, int fa = 0) {
    for (int i=g[u].size()-1; i>=0; --i) {
        const edge& p = e[g[u][i]]; int v = p.a + p.b - u;
        if (v != fa) ans = min(ans, d[v] = d[u] + (tf - (f[v]<<1)) * p.t), dfs2(v, u);
    }
}

void solve() {
    int n, m, a; cin >> n;
    for (int i=1; i<=n; ++i) g[i].clear(), f[i] = 0;
    for (int i=n-2; i>=0; --i) {
        cin >> e[i].a >> e[i].b >> e[i].t;
        g[e[i].a].push_back(i); g[e[i].b].push_back(i);
    }
    tf = 0; cin >> m;
    while (m--) cin >> a >> f[a], tf += f[a];
    ans = d[1] = dfs();
    dfs2();
    cout << (ans<<1) << endl;
    for (int i=1, c=0; i<=n; ++i) if (d[i] == ans) {
        if (c++) cout << ' ';
        cout << i;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short c; cin >> c;
    while (c--) solve();
    return 0;
}