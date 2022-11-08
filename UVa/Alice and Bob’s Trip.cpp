/**
 * UVa1484/LA5088
 * Harbin 2010
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 500100
struct node {int v, c;} t; vector<node> g[N]; int d[N], n, l, r;

void dfs(int u = 0,  int t = 0, bool b = true) {
    int s = g[u].size();
    d[u] = s ? -1 : 0;
    for (int i=0; i<s; ++i) {
        int v = g[u][i].v, tt = t + g[u][i].c;
        dfs(v, tt, !b);
        int x = tt + d[v];
        if (d[v]<0 || x<l || x>r) continue;
        x = g[u][i].c + d[v];
        d[u] = b ? max(d[u], x) : (d[u]<0 ? x : min(d[u], x));
    }
}

void solve() {
    for (int i=0; i<n; ++i) g[i].clear();
    for (int i=1; i<n; ++i) {
        int u; cin >> u >> t.v >> t.c;
        g[u].push_back(t);
    }
    dfs();
    d[0] < 0 ? cout << "Oh, my god!" << endl : cout << d[0] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n >> l >> r) solve();
    return 0;
}