/**
 * UVa1669
 * 交换房子
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 100010
int u[N], v[N], w[N], n; bool vis[N]; long long cc; vector<int> g[N];

int dfs(int x) {
    vis[x] = true; int c = 1;
    for (int i=g[x].size()-1; i>=0; --i) {
        int j = g[x][i], y = u[j] + v[j] - x, cy;
        if (!vis[y]) cy = dfs(y), cc += min(cy, n-cy)*(long long)w[j], c += cy;
    }
    return c;
}

long long solve() {
    cin >> n; cc = 0;
    for (int i=1; i<=n; ++i) vis[i] = 0, g[i].clear();
    for (int i=1; i<n; ++i) cin >> u[i] >> v[i] >> w[i], g[u[i]].push_back(i), g[v[i]].push_back(i);
    dfs(1);
    return cc << 1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}