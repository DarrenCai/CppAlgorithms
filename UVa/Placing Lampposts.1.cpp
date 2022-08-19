/**
 * UVa10859
 * 放置街灯
 */

#include <iostream>
using namespace std;

#define N 1020
int g[N][N], c[N], d[N][2], m, n; bool vis[N];

int dfs(int u) {
    vis[u] = true;
    d[u][0] = 0; d[u][1] = N;
    for (int i=0; i<c[u]; ++i) {
        int v = g[u][i];
        if (!vis[v]) {
            dfs(v);
            d[u][0] += 1 + d[v][1];
            d[u][1] += min(1+d[v][0], d[v][1]);
        }
    }
    return min(d[u][0], d[u][1]);
}

void solve() {
    cin >> n >> m;
    for (int i=0; i<n; ++i) vis[i] = c[i] = 0;
    for (int i=0; i<m; ++i) {
        int a, b; cin >> a >> b;
        g[a][c[a]++] = b;
        g[b][c[b]++] = a;
    }
    int ans = 0;
    for (int i=0; i<n; ++i) if (!vis[i]) ans += dfs(i);
    cout << ans/N << ' ' << m - ans%N << ' ' << ans%N << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}