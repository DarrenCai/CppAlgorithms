/**
 * UVa1292/LA2038
 * 战略游戏
 * SEERC 2000
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1520
int d[N][2], g[N][N], c[N], n; bool vis[N];

void dfs(int u) {
    vis[u] = true; d[u][0] = 0; d[u][1] = 1;
    for (int i=0, v; i<c[u]; ++i) if (!vis[v = g[u][i]]) {
        dfs(v);
        d[u][0] += d[v][1];
        d[u][1] += min(d[v][0], d[v][1]);
    }
}

int solve() {
    memset(c, 0, sizeof(c)); memset(vis, 0, sizeof(vis));
    for (int i=0; i<n; ++i) {
        int u, t; char _; cin >> u >> _ >> _ >> t >> _;
        while (t--) {
            int v; cin >> v; g[u][c[u]++] = v; g[v][c[v]++] = u;
        }
    }
    dfs(0);
    return min(d[0][0], d[0][1]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n) cout << solve() << endl;
    return 0;
}